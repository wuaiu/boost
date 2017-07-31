#include<iostream>
#include <boost/lexical_cast.hpp>
#include<boost/format.hpp>
using std::cout;
using std::string;
using std::endl;
using boost::lexical_cast;
using boost::format;
int main()
{
	
	int x = lexical_cast<int> ("100");
	long y = lexical_cast<int>("2000");
	float pai = lexical_cast<float>("3.14159e5");
	double e = lexical_cast<double>("2.71828");
	cout << x << y << pai << e << endl;
	string str = lexical_cast<string>(456);
	cout << str << endl;
	cout << lexical_cast<string> (0.618) << endl;
	cout << lexical_cast<string> (0x10) << endl;
	//lexical_cast利用了输入输出流，转换起点对象是可流输出的，即定义了operator<<;
	//转化终点对象是可流输入的，即定义了opreator>>;终点对象必须是可缺省构造和可拷贝的。

	//format；与printf非常类似 
	//%05d 输出宽度为5的整数，不足用0填充；
	//%-8.3f输出左对齐，总宽度为8，小数位3位的浮点数
	//% 10s输出10位的字符串，不足位用空格填充
	//%05X输出宽度为5的大写16进制整数，不足位用0填充

	format fmt("%05d\n%-8.3f\n% 10s\n%05X\n");
	cout << fmt % 62 % 2.236%"123456789" % 48;
	string str1 = fmt.str();                //返回格式化后的字符串
	fmt.clear();                            //清空缓存
	fmt % 62 % 2.236%"123456789" % 48;
	string str2 = fmt.str();        
	fmt.parse("%05d\n%-8.3f\n% 10s\n%05d\n");//换用另一个格式字符串
	fmt % 62 % 2.236%"123456789" % 48;
	string str3 = fmt.str();    

	format fmt1("%|05d|\n%|-8.3f|\n%| 10s|\n%|05X|\n"); //%|spec|形式，功能与fmt一样，可更清晰

	format fmt2("(%1% + %2%)* %2% = %3%\n");          //%N%可以代指第N个参数；
	fmt2 % 2 % 5;
	fmt2 % ((2 + 5) * 5);
	cout << fmt2.str();

	getchar();
	return 0;
}
