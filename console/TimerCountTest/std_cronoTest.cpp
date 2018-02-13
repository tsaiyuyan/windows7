#include <thread>
#include <chrono>
#include <iostream>
#include <mutex>

using namespace std;
 
int std_cronoTest()
{
#ifdef _MSC_VER >= 1900
	std::mutex www;
	using namespace std::chrono_literals;
    std::cout << "Hello waiter" << std::endl; // flush is intentional
    auto start = std::chrono::high_resolution_clock::now();
    std::this_thread::sleep_for(1000us);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::micro> elapsed = end-start;
    std::cout << "Waited " << elapsed.count() << " us\n";
#endif
	return 0;
}

/*
duration
duration 是 chrono 裡面，用來記錄時間長度的類別，他基本上是一個 template class，
可以自行定義他的意義；chrono 也有提供一些比較常見的時間類別，可以直接拿來使用，
下面就是內建的 duration 的型別：

typedef duration<long long, nano> nanoseconds;
typedef duration<long long, micro> microseconds;
typedef duration<long long, milli> milliseconds;
typedef duration<long long> seconds;
typedef duration<int, ratio<60> > minutes;
typedef duration<int, ratio<3600> > hours;

*/
