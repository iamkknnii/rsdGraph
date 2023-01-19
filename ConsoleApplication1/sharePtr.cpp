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
	cout << *p << endl;//!�뿪������ʱ��p���õĶ������١�
}
std::shared_ptr<string> return_share_ptr()
{
	std::shared_ptr<string> p = factory("helloworld");
	cout << *p << endl;
	return p; //!����pʱ�����ü��������˵��������� 
} //!p�뿪�������򣬵���ָ����ڴ治�ᱻ�ͷŵ��� 


////���Թ���ָ��
	//// ���ʹ��make_shared��������ָ�룬
void test();

void test()
{
	std::shared_ptr<int> p1 = make_shared<int>();//make_shared �����ն���
	*p1 = 10;
	cout << "p1 = " << *p1 << endl; // ���10

	// ��ӡ���ø�����1
	cout << "p1 count = " << p1.use_count() << endl;

	// ��2�� shared_ptr ����ָ��ͬһ��ָ��
	std::shared_ptr<int> p2(p1);

	// ���2
	cout << "p2 count = " << p2.use_count() << endl;
	cout << "p1 count = " << p1.use_count() << endl;
	// �Ƚ�����ָ�룬p1 ���� p2
	if (p1 == p2) {
		std::cout << "p1 and p2 are pointing to same pointer\n";
	}

	p1.reset();// �޲�������reset���޹���ָ�룬���ø���Ϊ0
	cout << "p1 Count = " << p1.use_count() << endl;

	p1.reset(new int(11));// ����������reset�����ø���Ϊ1
	cout << "p1 Count = " << p1.use_count() << endl;

	use_factory();
	auto p = return_share_ptr();
	cout << p.use_count() << endl;
	system("pause");
	return ;
}
	