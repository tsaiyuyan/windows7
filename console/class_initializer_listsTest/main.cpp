#include <stdio.h>
#include <iostream>
#include <vector>
using namespace std;
class Foo
{	
public:	
	int a,i, j;	
	const int& r;
	vector<int> mVec;
	Foo(int i): r(a) // initializes X::r to refer to X::a
		,i(i) // initializes X::i to the value of the parameter i
		,j(this->i) // initializes X::j to the value of X::i
		, mVec(vector<int>(10))
	{

	}

};


int main(int argc,char *argv[])
{
	Foo foo(999);
	foo.a = 199;
	cout << foo.a<<endl;
	cout << foo.i<<endl;
	cout << foo.j<<endl;
	cout << foo.r<<endl;
	system("pause");
	return 0;
}