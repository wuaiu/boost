#define BOOST_DATE_TIME_SOURCE
#define BOOST_DATE_TIME_NO_LIB
#include<libs/date_time/src/gregorian/greg_names.hpp>
#include<libs/date_time/src/gregorian/date_generators.cpp>
#include<libs/date_time/src/gregorian/greg_month.cpp>
#include<libs/date_time/src/gregorian/greg_weekday.cpp>
#include<libs/date_time/src/gregorian/gregorian_types.cpp>
#include<boost/date_time/gregorian/gregorian.hpp>
#include<boost/date_time/posix_time/posix_time.hpp>
#include <ctime>
using namespace boost::posix_time;
using namespace boost::gregorian;
using namespace std;
//using boost::timer;
using namespace boost::gregorian;

int main() {
	//time_duration;表示一个时间长度,默认时间精度是微妙，秒以下的时间度量都使用微妙
	time_duration td1(1, 10, 30, 1000); //构造函数指定时分秒，微妙来构造
	hours h(1);
	minutes m(10);
	seconds s(30);
	millisec ms(1);                       //毫秒
	microsec us(1);

	time_duration td2 = h + m + s + ms +us;
	time_duration td3 = hours(2) + seconds(10);

	//时间点ptime，相当于一个日期加上一个小于一天的时间长度，依赖于date和time_duration
	using namespace boost::gregorian;
	ptime p1(date(2016, 3, 5), hours(1));                 //2016年3月5日凌晨1时；
	ptime p2 = time_from_string("2016-3-5 01:00:00");
	ptime p3 = from_iso_string("20160305T010000");

	ptime p4 = second_clock::local_time();                //秒精度
	ptime p5 = microsec_clock::universal_time();          //微妙精度
	cout << p4 << endl;
	cout << p5 << endl;

	//ptime可以构造为特殊时间值，也有is_xxx()来检验特殊值
	ptime p6(not_a_date_time);                   //无效时间
	assert(p6.is_not_a_date_time());

	ptime p7(pos_infin);                         //正无限时间
	assert(p7.is_special() && p7.is_pos_infinity());

	//ptime相当于date+time_duration，对它的操作可以分解为两部分；date()和time_of_day()
	ptime p8(date(2016, 3, 20), hours(12) + minutes(30) + millisec(30));
	date d = p8.date();
	time_duration td4 = p8.time_of_day();

	ptime p9 = p8 + hours(3);
	ptime p10 = p9 + months(1);
	assert(p9 - p8 == hours(3));

	string str1 = to_simple_string(p9);       //YYYY-mmm-DD HH:MM:SS.fffffffff
	string str2 = to_iso_string(p9);          //YYYYMMDDTHHMMSS,fffffffff
	string str3 = to_iso_extended_string(p9); //YYYY-MM-DDTHH:MM:SS,fffffffff
	cout << str1 << endl;
	cout << str2 << endl;
	cout << str3 << endl;

	//time_period;时间区间，左闭右开区间；用ptime作为区间的两个端点；
	ptime p11(date(2016, 6, 6), hours(12));
	time_period tp1(p11, hours(8));                            //8个小时的区间
	time_period tp2(p11+hours(8), hours(1));                   //1个小时的区间

	//时间迭代器time_duration；构造时传入起始时间点ptime对象和一个步长time_duration对象；
	//解引用返回ptime对象,time_iterator也可直接与ptime比较，无需解引用
	ptime p12(date(2016, 6, 27), hours(10));
	for (time_iterator t_iter(p12, minutes(10)); t_iter < p12 + hours(1); ++t_iter)
	{
		cout << *t_iter<<endl;
	}

	//格式化时间日期
	date d2(2016, 6, 6);
	date_facet* dfacet = new date_facet("%Y年%m月%d日");
	cout.imbue(locale(cout.getloc(), dfacet));
	cout << d2 << endl;
	time_facet *tfacet = new time_facet("%Y年%m月%d日%H点%M分%S%F秒");
	cout.imbue(locale(cout.getloc(), tfacet));
	cout << ptime(d2, hours(21) + minutes(50) + millisec(100)) << endl;

	getchar();
	return 0;
}