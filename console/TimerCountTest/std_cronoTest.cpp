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
duration �O chrono �̭��A�ΨӰO���ɶ����ת����O�A�L�򥻤W�O�@�� template class�A
�i�H�ۦ�w�q�L���N�q�Fchrono �]�����Ѥ@�Ǥ���`�����ɶ����O�A�i�H�������ӨϥΡA
�U���N�O���ت� duration �����O�G

typedef duration<long long, nano> nanoseconds;
typedef duration<long long, micro> microseconds;
typedef duration<long long, milli> milliseconds;
typedef duration<long long> seconds;
typedef duration<int, ratio<60> > minutes;
typedef duration<int, ratio<3600> > hours;

*/
