#include <stdio.h>
#include <windows.h>
#include  <iphlpapi.h>
#include  <ipexport.h>
#include  <iptypes.h>
#pragma comment(lib, "iphlpapi.lib" )


int GetNetSpeed(DWORD &speed,DWORD &sendtotal ,DWORD &retotal)
{
	MIB_IFTABLE *pIfTable = NULL;  
	ULONG  dwSize = 0;    
	DWORD  dwRet;    

	dwRet = GetIfTable(pIfTable, &dwSize,TRUE);   //dwsize獲得接口個數
	if(dwRet == ERROR_INSUFFICIENT_BUFFER)  
	{  
		pIfTable = (MIB_IFTABLE *)  new  char[dwSize];     
		if(pIfTable !=  NULL  )  
		{  
			dwRet = GetIfTable(pIfTable,&dwSize,TRUE);   //獲得真實接口信息
			if(dwRet ==   NO_ERROR)  
			{  
				printf("dwNumEntries   =   %u\n",pIfTable->dwNumEntries);       
				for(int i=0;i<pIfTable->dwNumEntries;i++)  
				{  
					if((pIfTable->table[i]).dwType == IF_TYPE_ETHERNET_CSMACD && (pIfTable->table[i]).dwInOctets>0 && (pIfTable->table[i]).dwOutOctets>0 )
					{   
						wprintf(L"wszName : %s\n",(pIfTable->table[i]).wszName);
						printf("bDescr :%s \n",(pIfTable->table[i]).bDescr);

						printf("dwLastChange :%u \n",(pIfTable->table[i]).dwLastChange);
						
						//只保留dwtype為6是網卡信息，接受發送了數據。默認服務器只能用一個網卡，
						printf("table[%1d].dwIndex   =   %u\n", i, (pIfTable->table[i]).dwIndex);       
						printf("\t dwType    =   %u\n", (pIfTable->table[i]).dwType);       
						printf("\t dwSpeed   =   %u\n",  (pIfTable->table[i]).dwSpeed);  
						//added (pIfTable->table[i]).dwInOctets=0;    
						printf("\t received data is %u\n",(pIfTable->table[i]).dwInOctets); //接口接受總數據
						printf("\t send data is %u\n",(pIfTable->table[i]).dwOutOctets); // 接口發送總數據

						speed=(pIfTable->table[i]).dwSpeed; //獲得網卡數據類型，10M or100M
						retotal=(pIfTable->table[i]).dwInOctets; //網卡接受到的總的數據字節
						sendtotal=(pIfTable->table[i]).dwOutOctets; //網卡發送的
						break;
					}
				}  
			}  
			else
			{    
				printf("Some   error   occured in netspeed!/n");  
			}  
		}  
		else   
		{  
			printf("Memory allocate failue/n");  
		}  
	}  
	else   
	{     
		printf("Some error  occured  in netspeed!/n");  
	}     
	return   0;    
}
#include "limits.h"
int main(int argc,char *argv[])
{
	DWORD oldspeed,oldsendtotal,oldretotal;
	DWORD speed,sendtotal,retotal;

	GetNetSpeed(oldspeed,oldsendtotal,oldretotal);
	Sleep(1000);
	GetNetSpeed(speed,sendtotal,retotal);

	

	DWORD upload = 0,download = 0;
	upload = (sendtotal >= oldsendtotal )? sendtotal - oldsendtotal:   ULONG_MAX - oldsendtotal + sendtotal;
	download = (retotal >= oldretotal )? retotal - oldretotal:   ULONG_MAX - oldretotal + retotal;

	printf("current download: %u ",upload);
	printf("current upload : %u \n",download);
	return 0;
}



// reference http://blog.csdn.net/zhangzq86/article/details/8089962
/*
#include <iphlpapi.h>
#pragma comment ( lib, "iphlpapi.lib")

使用GetIfTable()獲取各個端口信息的時候用到的 _MIB_IFTABLE結構:

typedef struct _MIB_IFTABLE {
  DWORD dwNumEntries; //得到的端口個數
  MIB_IFROW table[ANY_SIZE]; //得到的各個端口的信息,這個結構才是重點
} MIB_IFTABLE, *PMIB_IFTABLE;

typedef struct _MIB_IFROW {
  WCHAR wszName[MAX_INTERFACE_NAME_LEN];
  DWORD dwIndex;
  DWORD dwType;
  DWORD dwMtu;
  DWORD dwSpeed;
  DWORD dwPhysAddrLen;
  BYTE bPhysAddr[MAXLEN_PHYSADDR];
  DWORD dwAdminStatus;
  DWORD dwOperStatus;
  DWORD dwLastChange;
  DWORD dwInOctets;
  DWORD dwInUcastPkts;
  DWORD dwInNUcastPkts;
  DWORD dwInDiscards;
  DWORD dwInErrors;
  DWORD dwInUnknownProtos;
  DWORD dwOutOctets;
  DWORD dwOutUcastPkts;
  DWORD dwOutNUcastPkts;
  DWORD dwOutDiscards;
  DWORD dwOutErrors;
  DWORD dwOutQLen;
  DWORD dwDescrLen;
  BYTE bDescr[MAXLEN_IFDESCR];
} MIB_IFROW, *PMIB_IFROW


wzsName:包含了該接口的名字(多字節的),具體也不知道哈意思,就是一串數字,有懂的和我說一下
dwIndex:該接口的索引值,比如有多個網卡的時候,每個網卡都有一個索引值,是會隨著網卡正在被使用的個數變化的
dwType:該接口的類型,這個類型是被IANA(是個什麼協會吧)定義的,有以下幾種:
Value						Meaning
IF_TYPE_OTHER
1							Some other type of network interface.
IF_TYPE_ETHERNET_CSMACD
6							An Ethernet network interface.
IF_TYPE_ISO88025_TOKENRING
9							A token ring network interface.
IF_TYPE_PPP
23							A PPP network interface.
IF_TYPE_SOFTWARE_LOOPBACK
24							A software loopback network interface.
IF_TYPE_ATM
37							An ATM network interface.
IF_TYPE_IEEE80211
71							An IEEE 802.11 wireless network interface.
IF_TYPE_TUNNEL
131							A tunnel type encapsulation network interface.
IF_TYPE_IEEE1394			
144							An IEEE 1394 (Firewire) high performance serial bus network interface.



其中24是網絡迴路的網卡(我自己是這樣叫的),就是127.0.0.1那個,應該是每個機子都有的吧
一般我們用的是6.
dwMtu:百度一下MTU就知道了,就是該接口的最大傳輸單元,理解為該通信協議的某一層上面能通過的最大的數據包的大小(以字節為單位)
dwSpeed:該接口最大的傳輸速率,可是看成是這個接口每秒最多傳多大的數據的一個規格,我剛開始的時候以為這是該接口的即時傳輸速度呢,鬱悶
dwPhysAddrLen: bPhysAddr指向的地址的長度
bPhysAddr:指向該接口地址的指針
dwAdminStatus:該接口的管理狀態,按我的理解就是人為設定的那個狀態:啟用/禁用
dwOperStatus:該接口的操作狀態,它可以取以下的值,看了下面的值就知道是什麼意思了
0 MIB_IF_OPER_STATUS_NON_OPERATIONAL 網絡適配器被禁止的狀態;
1 MIB_IF_OPER_STATUS_UNREACHABLE 沒有連接的狀態;
2 MIB_IF_OPER_STATUS_DISCONNECTED 電纜未連接的狀態;
3 MIB_IF_OPER_STATUS_CONNECTING 廣域網適配器連接中的狀態;
4 MIB_IF_OPER_STATUS_CONNECTED 廣域網適配器連接上遠程對等點的狀態;
5 MIB_IF_OPER_STATUS_OPERATIONAL 局域網適配器默認的連接狀態;

dwLastChange: 適配器狀態最後一次改變的時間;
dwInOctets: 該接口總的收到的數據大小;
dwInUcastPkts As Long '總共收到(unicast包)
dwInNUcastPkts As Long '總共收到(non-unicast包)，包括廣播包和多點傳送包dwInDiscards As Long '收到後丟棄包總數（即使沒有錯誤）
dwInErrors As Long '收到出錯包總數
dwInUnknownProtos As Long '收到後因協議不明而丟棄的包總數
dwOutOctets As Long '總共發送(字節)
dwOutUcastPkts As Long '總共發送(unicast包)
dwOutNUcastPkts As Long '總共發送(non-unicast包)，包括廣播包和多點傳送包
dwOutDiscards As Long '發送丟棄包總數（即使沒有錯誤）
dwOutErrors As Long '發送出錯包總數
dwOutQLen As Long '發送隊列長度
dwDescrLen As Long ' bDescr部分有效長度
bDescr(0 To 255) As Byte '接口描述 也就是在設備管理器上看的到名字

用一秒鐘前後得到的dwInOctets數據相減,就是這一秒中該接口的流量,用這個方法就可以計算機子的即時流量了

*/