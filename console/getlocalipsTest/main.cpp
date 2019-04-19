#include <winsock2.h>
#include <WS2tcpip.h>  
#include <iphlpapi.h>
#include <vector>
#include <iostream>
#include <cstdint>
#include <cstdio>
#include <cstdlib>

using namespace std;
// Link with Iphlpapi.lib
#pragma comment(lib, "Ws2_32.lib")
#pragma comment(lib, "IPHLPAPI.lib")

#if (_MSC_VER <= 1400) //MSVC++ 8.0  _MSC_VER == 1400 (Visual Studio 2005)   表示低於 VS2005 要補上此函式
const char *inet_ntop(int af, const void *src, char *dst, socklen_t size) //vs2005 need ,vs2008 plus not need
{
	struct sockaddr_storage ss;
	unsigned long s = size;

	ZeroMemory(&ss, sizeof(ss));
	ss.ss_family = af;

	switch(af) 
	{
	case AF_INET:
		((struct sockaddr_in *)&ss)->sin_addr = *(struct in_addr *)src;
		break;
	case AF_INET6:
		((struct sockaddr_in6 *)&ss)->sin6_addr = *(struct in6_addr *)src;
		break;
	default:
		return NULL;
	}
	/* cannot direclty use &size because of strict aliasing rules */
	return (WSAAddressToStringA((struct sockaddr *)&ss, sizeof(ss), NULL, dst, &s) == 0)?dst : NULL;
}
#endif

vector<string> get_local_ips(ULONG family = AF_UNSPEC,ULONG flags = NULL)
{
	vector<string> localIPs;
	PIP_ADAPTER_ADDRESSES pAddresses = NULL;   
	ULONG outBufLen = 0;  

	GetAdaptersAddresses(family, flags, NULL, pAddresses, &outBufLen);  

	pAddresses = (IP_ADAPTER_ADDRESSES*) malloc(outBufLen);  

	if (GetAdaptersAddresses(family, flags, NULL, pAddresses, &outBufLen) != NO_ERROR) 
	{
		free(pAddresses);  
		return localIPs;
	}

	char buff[100];  
	DWORD bufflen=100;  
	PIP_ADAPTER_ADDRESSES pCurrAddresses	= NULL;
	PIP_ADAPTER_UNICAST_ADDRESS pUnicast	= NULL;
	LPSOCKADDR addr							= NULL;

	pCurrAddresses = pAddresses;
	while (pCurrAddresses) 
	{
		if(pCurrAddresses->OperStatus != IfOperStatusUp)
		{
			pCurrAddresses = pCurrAddresses->Next;
			continue;
		}

		pUnicast = pCurrAddresses->FirstUnicastAddress;
		while (pUnicast)
		{				
			addr = pUnicast->Address.lpSockaddr;
			ZeroMemory(buff, bufflen);
			if (addr->sa_family == AF_INET6)  
			{
				sockaddr_in6 *sa_in6 = (sockaddr_in6 *)addr; 
				inet_ntop(AF_INET6, &(sa_in6->sin6_addr), buff, bufflen);
			}else
			{
				sockaddr_in  *sa_in = (sockaddr_in *)addr; 
				inet_ntop(AF_INET, &(sa_in->sin_addr), buff, bufflen);				
			}
			localIPs.push_back(buff); //just only get ipv4  ,by ezio
			pUnicast = pUnicast->Next;
		}
		pCurrAddresses = pCurrAddresses->Next;
	}
	free(pAddresses);  
	return localIPs;
}
vector<string> get_all_interfaces(ULONG family = AF_UNSPEC,ULONG flags = GAA_FLAG_INCLUDE_ALL_INTERFACES)
{
	vector<string> macs;
	ULONG outBufLen = sizeof(IP_ADAPTER_ADDRESSES);
	GetAdaptersAddresses(family, flags, NULL, NULL, &outBufLen);
	std::vector<uint8_t> bytes(outBufLen, 0);
	PIP_ADAPTER_ADDRESSES pCurrAddresses = (IP_ADAPTER_ADDRESSES *)bytes.data();
	DWORD dwRetVal = GetAdaptersAddresses(family, flags, NULL, pCurrAddresses, &outBufLen);
	if (dwRetVal == NO_ERROR) 
	{
		while (pCurrAddresses != NULL)
		{ 
			string str;
			for (size_t i = 0; i < (int) pCurrAddresses->PhysicalAddressLength; i++) 
			{
				char s1[10] = "";
				if (i == (pCurrAddresses->PhysicalAddressLength - 1))
				{
					sprintf_s(s1,"%.2X", (int) pCurrAddresses->PhysicalAddress[i]);
				}
				else
				{
					sprintf_s(s1,"%.2X-",(int) pCurrAddresses->PhysicalAddress[i]);
				}
				str +=s1;
			}
			//	if (pCurrAddresses->PhysicalAddressLength > 0)
			macs.push_back(str);
			pCurrAddresses = pCurrAddresses->Next;
		}
	}
	return macs;
}

int main(int argc,char *argv[])
{
	vector<string> ips = get_local_ips(AF_INET,0);
	vector<string> macs = get_all_interfaces();

	for (auto str : ips)
	{
		cout << str.c_str() << endl;
	}


	for (auto str : macs)
	{
		cout << str.c_str() << endl;
	}

	system("pause");
	return 0;
}