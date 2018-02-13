#include "stdafx.h"
#include <threadpool\ThreadPool.h>
#include <iostream>
using namespace std;

class Obj
{
public:
	Obj(){};
	~Obj(){};
	int m_num;
	string str;
	int time_out;
};

CThreadPool m_pool1;
DWORD WINAPI MyThreadFunc1(LPVOID param)
{
	UserPoolData* poolData = (UserPoolData*)param;
	Obj *p = (Obj *)(poolData->pData);	

	cout << p ->str.c_str()<<endl;
		Sleep(1000);
	
	
	return 0;
}


int main(int argc,char *argv[])
{
	Obj obj;
	obj.str = "1234565789";
	m_pool1.SetPoolSize(8);
	m_pool1.Create();


	m_pool1.Run(MyThreadFunc1, &obj, Low);

	int x; cin >>x;
	
	m_pool1.Destroy();
	return 0;
}