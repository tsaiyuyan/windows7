#include <stdio.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

#include <winsock2.h>
#pragma comment(lib,"Ws2_32")

class test
{
public:
	test()
	{
		
		WSADATA	WSAData = { 0 };
		if (WSAStartup(MAKEWORD(2, 2), &WSAData) != 0)
		{
			// Tell the user that we could not find a usable WinSock DLL.
			if (LOBYTE(WSAData.wVersion) != LOBYTE(MAKEWORD(2, 2)) ||
				HIBYTE(WSAData.wVersion) != HIBYTE(MAKEWORD(2, 2)))
				printf("Incorrect winsock version\n");

			WSACleanup();
			//return false;
		}	
	}
	~test()
	{
		WSACleanup();
	}


};

int main(int argc,char *argv[])
{
	try	
	{
		//0. winsock initial
		char ermsg[1024]={0}; 
		WSADATA wsaData;
		int nRet; 
		nRet = WSAStartup(MAKEWORD(2, 2), &wsaData);	
		if(nRet)
		{	
			sprintf_s(ermsg,"WSAStartup() error : %d", nRet); 
			throw ermsg;
		}	

		//1. request OS to get socket 
		SOCKET sockfd = -1;
		sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		if (sockfd == INVALID_SOCKET) 
		{
			sprintf_s(ermsg,"socket() INVALID_SOCKET error : %d", WSAGetLastError()); 
			throw ermsg;
		}
		

		//2. set non-blocking socket
		unsigned long nNonBlocking = 1;
		if (ioctlsocket(sockfd, FIONBIO, &nNonBlocking) == SOCKET_ERROR)
		{
			sprintf_s(ermsg,"ioctlsocket() Unable to set nonblocking mode, error : %d", WSAGetLastError()); 
			closesocket(sockfd);
			throw ermsg;
		}
		// 3.Set linger
		linger oLinger;
		oLinger.l_onoff = 1;
		oLinger.l_linger = 3; // wait 3 seconds for TCP handshake
		if (setsockopt(sockfd, SOL_SOCKET, SO_LINGER, (char*)&oLinger, sizeof(oLinger)) == SOCKET_ERROR)
		{
			sprintf_s(ermsg,"setsockopt() set linger, error : %d", WSAGetLastError()); 			
			throw ermsg;
		}	
		
		// 4. set dest_addr
		string dest_ip = "172.16.161.4";
		u_short dest_port = 59998;
		sockaddr_in dest_addr={0}; 
		dest_addr.sin_family = AF_INET;
		dest_addr.sin_addr.s_addr = inet_addr(dest_ip.c_str());
		dest_addr.sin_port = htons(dest_port);

		//5. nonblocking connect
		const int TIMEOUT = 1000;		
		struct timeval TimeOut;
		TimeOut.tv_sec = TIMEOUT / 1000;
		TimeOut.tv_usec = TIMEOUT;
		fd_set oRead, oWrite;
		FD_ZERO(&oRead);
		FD_ZERO(&oWrite);
		int nResult, nError;
		int nLen;
		nResult = connect(sockfd, (const sockaddr*)&dest_addr, sizeof(dest_addr));
		if (nResult == SOCKET_ERROR)
		{
			if (WSAGetLastError() != WSAEWOULDBLOCK)
			{
				sprintf_s(ermsg,"Connection failed, ec:%d\n", WSAGetLastError());
				closesocket(sockfd);
				throw ermsg;
			}
			else // need select
			{
				
				FD_SET(sockfd, &oRead);
				oWrite = oRead;
				int retry_count = 30; //30 secnonds
CONNECT_RETRY:
				nResult = select(sockfd + 1, &oRead, &oWrite, 0, &TimeOut);
				if (nResult == 0)
				{
					if(retry_count-- > 0)
					{
						goto CONNECT_RETRY;
					}

					closesocket(sockfd);

					throw "Connection failed, 30s timeout\n";
				}
				if (FD_ISSET(sockfd, &oRead) || FD_ISSET(sockfd, &oWrite))
				{
					nLen = sizeof(nError);
					if (getsockopt(sockfd, SOL_SOCKET, SO_ERROR, (char*)&nError, &nLen) < 0)
					{
						closesocket(sockfd);
						sprintf_s(ermsg,"Connect error %d\n", nError);
						throw ermsg;
					}else
					{
						//connect success	
						cout<<"connect success with WSAEWOULDBLOCK"<<endl;
					}
				}
				else
				{
					closesocket(sockfd);
					throw "Connection failed\n";
				}
			}
		}else // else connected immediately
		{
			//connect success
			cout<<"connect success immediately"<<endl;
		}		
		printf("Connect succes \n");
		closesocket(sockfd);
	}
	catch(const char* message)	
	{
		std::cout << message << std::endl;	
	}
	WSACleanup();
	system("pause");
	return 0;
}

/*
SO_LINGER:當TCP連接的一段主動close（）連接時，一般情況下，系統會馬上返回，
但是當有數據殘留在發送緩衝區時，系統會現將這些數據發送出去再返回，這樣可以優雅地關閉掉連接。
這就可能使close（）阻塞在系統調用中。

這種情況下，我們可以使用套接字選項SO_LINGER來改變這種默認設置。該選項會在用戶空間與內核間傳遞如下結構體：

struct linger{
	int l_onoff; //on:打開緩衝發送的開關，允許系統將殘留在發送緩衝區中的數據發送出去
	int l_linger; //允許的阻塞時間（即允許系統將殘留在發送緩衝區中的數據發送出去的最大等待時間，時間一到，無論如何都會關閉套接字的一端）
}

SO_REUSEADDR: 有四個不同的功能

   1、在一個服務端口被子進程佔用的情況下，允許重啟服務，並且在父進程中再次綁定(bind函數)端口成功

   2、允許在同一個端口啟動同一個服務的多個實例。前提是bing的IP地址不同。
*/