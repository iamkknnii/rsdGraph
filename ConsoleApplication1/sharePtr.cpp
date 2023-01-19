#include <boost/graph/directed_graph.hpp> // A subclass to provide reasonable arguments to adjacency_list for a typical directed graph
#include <boost//graph/graph_traits.hpp>
#include <vector>
#include <string.h>
#include <iostream>
#include <boost/graph/graph_utility.hpp>

#include <memory>
#include "boost/graph/random.hpp"
#include <random>

using namespace boost;
using namespace std;

void use_factory();
std::shared_ptr<string> return_share_ptr();
std::shared_ptr<string> factory(const char* p);


std::shared_ptr<string> factory(const char* p)
{
	std::shared_ptr<string> p1 = make_shared<string>(p);
	return p1;
}

void use_factory()
{
	std::shared_ptr<string> p = factory("helloworld");
	int num1 = p.use_count();
	cout << *p << endl;//!离开作用域时，p引用的对象被销毁。
}
std::shared_ptr<string> return_share_ptr()
{
	std::shared_ptr<string> p = factory("helloworld");
	cout << *p << endl;
	return p; //!返回p时，引用计数进行了递增操作。 
} //!p离开了作用域，但他指向的内存不会被释放掉。 


////测试共享指针
	//// 最好使用make_shared创建共享指针，
void test();

void test()
{
	std::shared_ptr<int> p1 = make_shared<int>();//make_shared 创建空对象，
	*p1 = 10;
	cout << "p1 = " << *p1 << endl; // 输出10

	// 打印引用个数：1
	cout << "p1 count = " << p1.use_count() << endl;

	// 第2个 shared_ptr 对象指向同一个指针
	std::shared_ptr<int> p2(p1);

	// 输出2
	cout << "p2 count = " << p2.use_count() << endl;
	cout << "p1 count = " << p1.use_count() << endl;
	// 比较智能指针，p1 等于 p2
	if (p1 == p2) {
		std::cout << "p1 and p2 are pointing to same pointer\n";
	}

	p1.reset();// 无参数调用reset，无关联指针，引用个数为0
	cout << "p1 Count = " << p1.use_count() << endl;

	p1.reset(new int(11));// 带参数调用reset，引用个数为1
	cout << "p1 Count = " << p1.use_count() << endl;

	use_factory();
	auto p = return_share_ptr();
	cout << p.use_count() << endl;
	system("pause");
	return ;
}
	