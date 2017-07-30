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
	//pos_infin             正无穷
	//neg_infin              负无穷
	//not_a_date_time        无效时间
	//min_date_time          最小日期
	//max_date_time          最大日期

	date d1;                 //无效时间
	date d2(2010, 1, 1);     //
	date d3(2000, Jan, 1);   //用英文月份初始化
	date d4(d2);

	assert(d1 == date(not_a_date_time));     //
	assert(d2 == d4);                        //
	assert(d3 < d4);

	date d5 = from_string("1999-12-31");
	date d6(from_string("2005/1/1"));
	date d7 = from_undelimited_string("19940709");

	cout << day_clock::local_day() << endl;
	cout << day_clock::universal_day() << endl;

	date d8(2016, 7, 30);
	assert(d8.year() == 2016);
	assert(d8.month() == 7);
	assert(d8.day() == 30);

	date::ymd_type ymd = d8.year_month_day();
	assert(ymd.year == 2016);
	assert(ymd.month == 7);
	assert(ymd.day == 30);

	assert(d8.day_of_week() == 6);     //星期几
	int day1=d8.day_of_year();
	date d9 = d8.end_of_month();    //本月最后一天
	int day2 = d9.day();

	cout << to_simple_string(d8) << endl;      //YYYY-mmm-DD,其中mmm是三字母英文月份
	cout << to_iso_string(d8) << endl;          //YYYYMMDD
	cout << to_iso_extended_string(d8) << endl; //YYYY-MM-DD

	//cin >> d8;                                 //输入输出格式默认是YYYY-mmm-DD
	cout << d8;

	//可以与tm互相转换，其中时分秒被忽略
	tm d10 = to_tm(d8);
	date d11 = date_from_tm(d10);

	getchar();
	return 0;
}