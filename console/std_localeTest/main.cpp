#include <iostream>
using namespace std;

//project->General->Character Set = > "Use Unicode Character Set"

int main (int argc,char *argv[])
{
	locale::global(locale(""));// ������ܰ��D  
	wcout.imbue(locale(""));

	wcout << L"wcout << abcdefg" << endl;
	wcout << L"wcout << ���դ���:�@�G�T�|" << endl;

	//�ϥΧ����ɭn�I�s�U����� ,�~���|�� memory leak���D   <===���n
	locale::global(std::locale("C"));
	wcout.imbue(std::locale("C"));


	//===== �L�ϥ� std::locale �|�o�Ͳ׺ݾ����L�ɥd��
	wcout << L"wcout << abcdefg" << endl;
	wcout << L"wcout << ���դ���:�@�G�T�|" << endl;  //"���դ���:�@�G�T�|" can't printf

	int x; cin >> x;
	return 0;
}