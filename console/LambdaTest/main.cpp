#include <stdio.h>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc,char *argv [])
{
	std::vector<int> some_list;
	int total = 0;
	for (int i=0;i<5;++i) 
		some_list.push_back(i);
	std::for_each(begin(some_list), end(some_list), [&total](int x) {total += x;} );
	return 0;
}

/*
Lamd
for_each ­ì«¬
template<typename InputIterator, typename Function>
Function for_each(InputIterator beg, InputIterator end, Function f) 
{
  while(beg != end) 
    f(*beg++);
}

*/