#include <boost/algorithm/string.hpp>
#include<boost/format.hpp>
using namespace  boost;
using namespace std;
int main()
{
	//前缀i：表示大小写不敏感，
	//后缀_copy表示算法不改变输入，返回处理结果的拷贝，否则算法原地处理
	//后缀_if表示算法需要一个判断式函数对象，否则使用默认判断准则

	//大小写转换;没有i和_if版本
	std::string str1("I Don't Know.\n");
	to_upper_copy(str1);
	cout << str1<<endl;
	to_lower(str1);
	cout << str1<< endl;

	//判断式  ;除了all都有i前缀版本
	//starts_with
	//end_with
	//contains
	//equals
	//lexicographical_compare
	//all    判断字符串中每个字符是否满足某一条件
	string str2("Power Bomb");
	assert(iends_with(str2, "bomb"));
	assert(!ends_with(str2, "bomb")); 
	assert(starts_with(str2, "Pow"));
	assert(contains(str2, "er"));
	string str3 = to_lower_copy(str2);
	assert(iequals(str2, str3));
	string str4("power suit");
	assert(ilexicographical_compare(str2, str4));
	assert(all(str4.substr(0, 5), is_lower()));

	//分类，用于检测一个字符是否符合某种特性，主要用于搭配其他算法，比如刚刚的all算法
	//is_space,is_alnum,is_alpha,is_cntrl,is_digit,is_graph,
	//is_lower,is_print,is_punct,is_upper,is_xdigit,is_any_of,if_from_range;
	//这些都是工厂函数，返回相应函数对象，且函数对象可以用&&，||等运算符组成表达式

	//修剪算法，trim_left,trim_right,trim;分别是修剪开头、修剪末尾、修剪两端；有_if和_copy版本
	format fmt1("|%|s||\n");
	string str5 = " samus aran";
	cout << fmt1%trim_copy(str5);
	cout << fmt1%trim_left_copy(str5);

	trim_right(str5);
	cout << fmt1%str5;

	string str6 = "2010 Happy new Year!!!";
	cout << fmt1%trim_left_copy_if(str6, is_digit());
	cout << fmt1%trim_right_copy_if(str6, is_punct());
	cout << fmt1%trim_copy_if(str6, is_digit()||is_digit()||is_space());

	//查找算法，find_first查找字符串在输入中第一次出现位置，find_last查找字符串在输入中最后一次出现的位置；
	//find_nth查找字符串在输入中第n次出现的位置；find_head取字符串开头N个字符的子串
	//find_tail返回字符串末尾N个字符的子串；全都返回迭代器对pair<iterator,iterator>
	format fmt2("|%s|.pos = %d\n");
	string str7 = "Long long ago,there was a king.";
	iterator_range<string::iterator>  rge;                    //迭代器区间
	rge = find_first(str7, "long");                           //第一次出现
	cout <<( fmt2%rge % (rge.begin() - str7.begin()));

	rge = ifind_first(str7, "long");                          //第二次出现
	cout << (fmt2%rge % (rge.begin() - str7.begin()));
	rge = find_nth(str7, "ng", 2);                            //第三次出现，从0开始计数
	cout << (fmt2%rge % (rge.begin() - str7.begin()));
	rge = find_head(str7, 4);                                 //取前4个字符
	cout << (fmt2%rge % (rge.begin() -str7.begin()));

	rge = find_tail(str7, 5);                                 //取末尾5个字符
	cout << (fmt2%rge % (rge.begin() - str7.begin()));

	rge = find_first(str7, "samus");                          //找不到
	assert(rge.empty() && !rge);

	//替换与删除，replace/erase_first,替换/删除一个字符串在输入中的第一次出现replace/erase_last替换/删除一个字符串在输入中最后一次出现,
	//replace/erase_nth替换/删除一个字符串在输入中的第n次（从0开始）出现,replace/erase_all替换/删除一个字符串在输入中的每一个出现
	//,replace/erase_head替换/删除输入的开头
	//replace/erase_tail替换/删除输入的末尾
	string str8 = "Samus beat the monster.\n";
	cout << replace_first_copy(str8, "Samus", "samus");

	replace_last(str8, "beat", "kill");
	replace_tail(str8, 9, "ridley.\n");
	cout << str8;

	cout << ierase_all_copy(str8, "samus");
	cout << replace_nth_copy(str8, "1", 1, "L");
	cout << erase_tail_copy(str8, 8);
    
	//分割算法；find_all和split,可以使用策略将字符串分为若干部分，并将分割后的字符串拷贝存入指定的容器
	//容器元素类型必须是string或iterator_range<string::iterator>
	string str9 = "Samus,Link.Zelda::Mario-Luigi+zelda";
	deque<string> d;
	ifind_all(d, str9, "zELDA");//大小写无关分割字符串
	assert(d.size() == 2);
	for (auto pos = d.begin(); pos != d.end();++pos)
	{
		cout << "["<<*pos << "]";
	}
	cout << endl;

	list<iterator_range<string::iterator> >l;
	split(l, str9, boost::is_any_of(",.:-+"));  //第三个参数是一个函数对象，接受一个ch，返回bool为true时是一个分隔符
	
	for (auto pos = l.begin(); pos != l.end(); ++pos)
	{
		cout << "[" << *pos << "]";
	}
	cout << endl;

	l.clear();
	split(l, str9, is_any_of(".:-"), token_compress_on);
	                         //token_compress_on表示重复分割符相邻不会会产生空串
	                         //默认为token_compress_off表示重复分割符相邻会会产生空串
	for (auto pos = l.begin(); pos != l.end(); ++pos)
	{
		cout << "[" << *pos << "]";
	}
	cout << endl;

	//合并
	vector<string> vec = { "Samus", "Link", "Zelda", "Mario" };
	cout << join(vec, "+") << endl;

	cout << join_if(vec, "**", [](const string& x){return contains(x, "a"); });

	//查找分割迭代器；split_iterator可以用字符串作为分割符，而split只能用单个字符；
	cout << "查找分割" << endl;
	string str10("Samus||samus||mario||Link");
	typedef find_iterator<string::iterator> string_find_iterator;
	string_find_iterator pos, end;
	for (pos = make_find_iterator(str10, first_finder("samus", is_iequal()));
		pos != end;++pos)
	{
		cout << "[" << *pos << "]";
	}
	cout << endl;
	typedef split_iterator<string::iterator>string_split_iterator;
	string_split_iterator p, endp;
	for (p = make_split_iterator(str10, first_finder("||", is_iequal())); p != endp; ++p)
	{
		cout << "[" << *p << "]";
	}
	cout << endl;


	getchar();
	return 0;
}