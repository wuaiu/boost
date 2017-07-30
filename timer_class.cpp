#include<iostream>
#include<boost/timer.hpp>
using namespace std;
using boost::timer;
int main() {
	timer t;
	//输出最大时间跨度，时间精度，从构造实例开始经过的时间
	cout << "max timespan:" << t.elapsed_max() / 3600 << "h" << endl;
	cout << "min timespan:" << t.elapsed_min() << "s" << endl;
	cout << "now time elapased :" << t.elapsed() << "s" << endl;
	//重置计时器
	t.restart();

	getchar();
	return 0;
}