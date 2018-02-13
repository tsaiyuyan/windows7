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

	dwRet = GetIfTable(pIfTable, &dwSize,TRUE);   //dwsize��o���f�Ӽ�
	if(dwRet == ERROR_INSUFFICIENT_BUFFER)  
	{  
		pIfTable = (MIB_IFTABLE *)  new  char[dwSize];     
		if(pIfTable !=  NULL  )  
		{  
			dwRet = GetIfTable(pIfTable,&dwSize,TRUE);   //��o�u�걵�f�H��
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
						
						//�u�O�ddwtype��6�O���d�H���A�����o�e�F�ƾڡC�q�{�A�Ⱦ��u��Τ@�Ӻ��d�A
						printf("table[%1d].dwIndex   =   %u\n", i, (pIfTable->table[i]).dwIndex);       
						printf("\t dwType    =   %u\n", (pIfTable->table[i]).dwType);       
						printf("\t dwSpeed   =   %u\n",  (pIfTable->table[i]).dwSpeed);  
						//added (pIfTable->table[i]).dwInOctets=0;    
						printf("\t received data is %u\n",(pIfTable->table[i]).dwInOctets); //���f�����`�ƾ�
						printf("\t send data is %u\n",(pIfTable->table[i]).dwOutOctets); // ���f�o�e�`�ƾ�

						speed=(pIfTable->table[i]).dwSpeed; //��o���d�ƾ������A10M or100M
						retotal=(pIfTable->table[i]).dwInOctets; //���d�����쪺�`���ƾڦr�`
						sendtotal=(pIfTable->table[i]).dwOutOctets; //���d�o�e��
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

�ϥ�GetIfTable()����U�Ӻݤf�H�����ɭԥΨ쪺 _MIB_IFTABLE���c:

typedef struct _MIB_IFTABLE {
  DWORD dwNumEntries; //�o�쪺�ݤf�Ӽ�
  MIB_IFROW table[ANY_SIZE]; //�o�쪺�U�Ӻݤf���H��,�o�ӵ��c�~�O���I
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


wzsName:�]�t�F�ӱ��f���W�r(�h�r�`��),����]�����D���N��,�N�O�@��Ʀr,�������M�ڻ��@�U
dwIndex:�ӱ��f�����ޭ�,��p���h�Ӻ��d���ɭ�,�C�Ӻ��d�����@�ӯ��ޭ�,�O�|�H�ۺ��d���b�Q�ϥΪ��Ӽ��ܤƪ�
dwType:�ӱ��f������,�o�������O�QIANA(�O�Ӥ����|�a)�w�q��,���H�U�X��:
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



�䤤24�O�����j�������d(�ڦۤv�O�o�˥s��),�N�O127.0.0.1����,���ӬO�C�Ӿ��l�������a
�@��ڭ̥Ϊ��O6.
dwMtu:�ʫפ@�UMTU�N���D�F,�N�O�ӱ��f���̤j�ǿ�椸,�z�Ѭ��ӳq�H��ĳ���Y�@�h�W����q�L���̤j���ƾڥ]���j�p(�H�r�`�����)
dwSpeed:�ӱ��f�̤j���ǿ�t�v,�i�O�ݦ��O�o�ӱ��f�C��̦h�Ǧh�j���ƾڪ��@�ӳW��,�ڭ�}�l���ɭԥH���o�O�ӱ��f���Y�ɶǿ�t�שO,�{�e
dwPhysAddrLen: bPhysAddr���V���a�}������
bPhysAddr:���V�ӱ��f�a�}�����w
dwAdminStatus:�ӱ��f���޲z���A,���ڪ��z�ѴN�O�H���]�w�����Ӫ��A:�ҥ�/�T��
dwOperStatus:�ӱ��f���ާ@���A,���i�H���H�U����,�ݤF�U�����ȴN���D�O����N��F
0 MIB_IF_OPER_STATUS_NON_OPERATIONAL �����A�t���Q�T����A;
1 MIB_IF_OPER_STATUS_UNREACHABLE �S���s�������A;
2 MIB_IF_OPER_STATUS_DISCONNECTED �q�l���s�������A;
3 MIB_IF_OPER_STATUS_CONNECTING �s����A�t���s���������A;
4 MIB_IF_OPER_STATUS_CONNECTED �s����A�t���s���W���{�ﵥ�I�����A;
5 MIB_IF_OPER_STATUS_OPERATIONAL ������A�t���q�{���s�����A;

dwLastChange: �A�t�����A�̫�@�����ܪ��ɶ�;
dwInOctets: �ӱ��f�`�����쪺�ƾڤj�p;
dwInUcastPkts As Long '�`�@����(unicast�])
dwInNUcastPkts As Long '�`�@����(non-unicast�])�A�]�A�s���]�M�h�I�ǰe�]dwInDiscards As Long '�������]�`�ơ]�Y�ϨS�����~�^
dwInErrors As Long '����X���]�`��
dwInUnknownProtos As Long '�����]��ĳ�����ӥ�󪺥]�`��
dwOutOctets As Long '�`�@�o�e(�r�`)
dwOutUcastPkts As Long '�`�@�o�e(unicast�])
dwOutNUcastPkts As Long '�`�@�o�e(non-unicast�])�A�]�A�s���]�M�h�I�ǰe�]
dwOutDiscards As Long '�o�e���]�`�ơ]�Y�ϨS�����~�^
dwOutErrors As Long '�o�e�X���]�`��
dwOutQLen As Long '�o�e���C����
dwDescrLen As Long ' bDescr�������Ī���
bDescr(0 To 255) As Byte '���f�y�z �]�N�O�b�]�ƺ޲z���W�ݪ���W�r

�Τ@�����e��o�쪺dwInOctets�ƾڬ۴�,�N�O�o�@���ӱ��f���y�q,�γo�Ӥ�k�N�i�H�p����l���Y�ɬy�q�F

*/