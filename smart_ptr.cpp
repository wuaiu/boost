#include<boost/smart_ptr.hpp>
#include <boost/make_shared.hpp>
#include<iostream>
#include <cstdio>
using namespace std;
using namespace boost;

class Abstract{
public:
	virtual void f() = 0;
	virtual void g() = 0;
protected:
	virtual ~Abstract(){};

};
class Impl :public Abstract
{
public:
	virtual void f()
	{
		cout << "Class Impl f" << endl;
	}
	virtual void g()
	{
		cout << "Class Impl g" << endl;
	}
};
class socket_t{};
socket_t * open_socket()
{
	cout << "open_socket" << endl;
	return new socket_t;
}
void close_socket(socket_t *s)
{
	cout << "close_sokect" << endl;
}
int main()
{
	//weak_ptr,是配合shared_ptr引入的一种智能指针，没有重载operator*和->。
	//不共享资源，所以不影响智能指针的引用次数，只是一个静静的观察者，只能通过lock()从被观测的shared_ptr获得一个可用shared_ptr

	boost::shared_ptr<int> sp(new int(10));
	assert(sp.use_count() == 1);
	boost::weak_ptr<int> wp(sp);
	assert(wp.use_count() == 1);

	if (!wp.expired())
	{
		boost::shared_ptr<int> sp2 = wp.lock();
		*sp2 = 100;
		assert(wp.use_count() == 2);
	}
	assert(wp.use_count() == 1);
	sp.reset();
	assert(wp.expired());
	
	//shared_ptr;一般使用
	boost::shared_ptr<int> sp3(new int(10));
	boost::shared_ptr<int> sp4 = make_shared<int>(11);
	cout << sp3.use_count() << endl;  //引用数目
	assert(sp3.unique());     //是否是独占
	sp3.swap(sp4);            //交换指针
	int * ptr1 = sp3.get();   //返回内部指针
	cout << sp3.use_count() << endl;

	//shared_ptr与继承层次一起使用
	boost::shared_ptr<Abstract> sp5 = make_shared<Impl>();
	sp5->f();
	sp5->g();
	cout << sp5.use_count() << endl;  //对象本身的成员函数用.访问，对象封装的指针的函数用->访问；

	//shared_ptr；定制删除器，删除器是一个函数，接受一个参数，
	//boost::shared_ptr<FILE> fp(fopen("./1.txt", "r"), fclose);
	socket_t *ptr2 = open_socket();
	boost::shared_ptr<socket_t> sp6(ptr2, close_socket);

	//scoped_ptr;拷贝构造函数和赋值函数都是私有的，拒绝指针所有权的转让
	auto_ptr<int>ap(new int(10));
	scoped_ptr<int> sp7(ap);
	//scoped_ptr<int> sp8 = sp7;  //不可访问

	//auto_ptr是C++标准早期的智能指针，会转移指针所有权

	getchar();
	return 0;

}