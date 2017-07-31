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
    //date_duration表示日期长度，天数；被typedef成days
	days dd1(10);
	date_duration dd2(-10);

	//日期长度还有weeks，months，years；

	//日期区间，date_period，左闭右开区间
	date_period dp1(date(2010, 1, 1), days(20));
	                         //与date_period dp1(date(2010, 1, 1), date(2010, 1, 21));等效
	date_period dp2(date(2010, 1, 1), date(2009, 1, 1));//无效
	date_period dp3(date(2010, 3, 1), days(-20));   //无效

	assert(!dp1.is_null());
	assert(dp1.begin().day()==1);
	assert(dp1.last().day()==20);
	assert(dp1.length().days()==20);

	date_period dp4(date(2010, 2, 19), days(10));
	cout << dp1 << endl;                   //默认输出格式是[YYYY-mmm-DD/YYYY-mmm-DD]
	assert(dp1 < dp4);
	
	//日期迭代器
	date d(2016, 11, 26);
	day_iterator d_iter(d,2);     //默认步长是1；
	assert(d_iter == d);
	++d_iter;
	assert(d_iter == date(2016, 11, 28));
	date d1 = *d_iter;
	cout << d1 << endl;

	//gregorian_calendar静态函数
	typedef gregorian_calendar gre_cal;
	cout << "Y2010 is " << (gre_cal::is_leap_year(2010) ? "" : "not")<<"a leap year"<<endl;

	assert(gre_cal::end_of_month_day(2010, 2) == 28);

	date d2(1994, 7, 9);
	date d18years = d + years(18);
	cout << d18years << "is" << d18years.day_of_week() << endl;

	int count = 0;
	for (day_iterator d_iter(date(d18years.year(),d18years.month(),1));d_iter!=d18years.end_of_month();++d_iter)
	{
		if (d_iter->day_of_week()==Sunday)
		{
			++count;
		}
	}
	cout << "total " << count << " Sundays." << endl;
	
	getchar();
	return 0;
}