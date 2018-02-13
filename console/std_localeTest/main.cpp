#include <iostream>
using namespace std;

//project->General->Character Set = > "Use Unicode Character Set"

int main (int argc,char *argv[])
{
	locale::global(locale(""));// 中文顯示問題  
	wcout.imbue(locale(""));

	wcout << L"wcout << abcdefg" << endl;
	wcout << L"wcout << 測試中文:一二三四" << endl;

	//使用完畢時要呼叫下面兩行 ,才不會有 memory leak問題   <===重要
	locale::global(std::locale("C"));
	wcout.imbue(std::locale("C"));


	//===== 無使用 std::locale 會發生終端機打印時卡住
	wcout << L"wcout << abcdefg" << endl;
	wcout << L"wcout << 測試中文:一二三四" << endl;  //"測試中文:一二三四" can't printf

	int x; cin >> x;
	return 0;
}