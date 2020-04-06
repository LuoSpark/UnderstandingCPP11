#include <iostream>
using namespace std;


// �̳й��캯����using  ���ڻ��๹�캯����˽�еģ�������̳л����ǲ���ʹ�ü̳й��캯����
class BaseWithManyCtr {
public:
	BaseWithManyCtr(int v, string desc) {
		cout << __func__ << "v:" << v << " desc:" << desc << endl;
	}
	BaseWithManyCtr(int v) {
		cout << __func__ << "v:" << v  << endl;
	}
	BaseWithManyCtr(string desc) {
		cout << __func__ <<  "desc:" << desc << endl;
	}
};

class DerivedWithFunc:public BaseWithManyCtr{
public:
	using BaseWithManyCtr::BaseWithManyCtr;
	void externFunc1() {
		cout << __func__ << endl;
	}
};
void testDerivedCtr() {
	DerivedWithFunc df1(1,"hello world");
	DerivedWithFunc df2(2);
	DerivedWithFunc df("Hi money");
}

// ί�ɹ��캯��,ʹ����ί�ɹ��캯���Ͳ�����ʹ�ó�ʼ���б�������Ҫע�ⲻ���γ�һ��ί�ɻ�
class DeleCtr {
public:
	DeleCtr(int i) :DeleCtr(i,0){}
	DeleCtr(double d):DeleCtr(0,d) {}

private:
	DeleCtr(int i, double d) :m_i(i), m_d(d) { cout << "ί�ɹ��캯��"<<endl; }
	int m_i;
	double m_d;
};
void testDeleCtr() {
	DeleCtr dc(11);
}

// ��ֵ����,�ƶ����幹�캯��������ת���������۵�
void RunCode(int&& m) { cout << "rvalue ref" << endl; }
void RunCode(int& m) { cout << "lvalue ref" << endl; }
void RunCode(const int&& m) { cout << "const rvalue ref" << endl; }
void RunCode(const int& m) { cout << "const lvalue ref" << endl; }

template <typename T>
void PerfectForward(T&& t) {
	RunCode(forward<T>(t));
}
void testPerctForward() {
	int a = 2;
	int b = 3;
	const int c = 1;
	const int d = 0;

	PerfectForward(a);
	PerfectForward(move(b));
	PerfectForward(c);
	PerfectForward(move(d));
}

// ��ʾת��������
class CoverTo {
public:
	CoverTo(int i):m_value(i){

	}
	explicit operator bool() {
		return m_value != 0;
	}
private:
	int m_value;
};


// �б��ʼ��, ��������Ϊ��ʼ���б��������س�ʼ���б��Զ����๹�캯��ʹ�ó�ʼ���б�
// �����Է�ֹ������խ
#include <initializer_list>
#include <vector>
class CtrWithInitlist {
public:
	CtrWithInitlist(initializer_list<int> l) {
		cout << __func__ << " initlist" << endl;
		auto iter = l.begin();
		for (; iter != l.end(); iter++)
		{
			m_v.push_back(*iter);
		}
	}

	vector<int> getValueFromInitList() {
		return { 1, 2,3,5 };
	}
	void dealInitListParm(initializer_list<int> l) {
		for (auto iter : l)
		{
			cout << iter << endl;
		}
	}
private:
	vector<int> m_v;	//
};
void testInitList() {
	CtrWithInitlist cilist({ 1,24,7,99,6 });
	vector<int> mv = cilist.getValueFromInitList();
	cilist.dealInitListParm({ 43,4,7647,41 });
}

// POD���� plain old data
// c++11��ƽ���ĺͱ�׼����
struct NoTrivia1 {
	NoTrivia1() {}
};
struct NoTrivia2 :public NoTrivia1 {

};

struct NoTrivia3 {
	virtual void fun1() {}
};
struct NoTrivia4 {
	int b;
	static int a;
};
class NoTrivia5 {	//������������˵�Ĳ�һ�������Ӧ��Ҳ�ǲ�ƽ���ģ���Ϊ����Ȩ�޲�һ��
public:
	int a;
private:
	int b;
};
void testPOD() {
	cout << "is_trivial:" << std::is_trivial<NoTrivia1>::value << endl;
	cout << "is_trivial:" << std::is_trivial<NoTrivia2>::value << endl;
	cout << "is_trivial:" << std::is_trivial<NoTrivia3>::value << endl;
	cout << "is_trivial:" << std::is_trivial<NoTrivia4>::value << endl;
	cout << "is_trivial:" << std::is_trivial<NoTrivia5>::value << endl;
	cout <<"is_trivial:" << std::is_trivial<CtrWithInitlist>::value << endl;
}


// �����������壬c++11֮ǰ���ṹ���������Ϊ�������Ա
// ���з��������ͣ���������Ϊ�������Ա
struct SInt {
	int a;
};
union  MyUnion
{
	struct SInt a;		//c++11֮ǰ�ǲ��е�
	int b;
};
void testUnion(){
	MyUnion mun;
	mun.a.a = 1;
	mun.a = SInt();
}

// �û��Զ���������,ͨ���Զ����׺����
// ���ƣ�
// 1 ���������Ϊ���ͣ���ô����������������ֻ���Խ���unsigned long long����const char *Ϊ�������
// ��unsigned long long �޷�������ֵ��ʱ�򣬻��Զ�ת��Ϊ�ԡ�\0��Ϊ��β���ַ�����������const char *Ϊ
// �����İ汾
// 2 ���������Ϊ�������������������������ɽ���long double ����const char * Ϊ���������ù���ͬ1
// 3 ���������Ϊ�ַ�����������������������ֻ�ɽ���const char*,size_tΪ����
// 4 ���������Ϊ�ַ�������ֻ����char��Ϊ����
struct Watt { unsigned int v; };
Watt operator "" _w(unsigned long long v) {//_w��""֮������пո�
	return { (unsigned int)v };
}

void testUserDefineStr(){
	Watt capacity = 1024_w;
	cout << "Watt:" << capacity.v << endl;;
}

// �������ֿռ�
namespace InlineName {
	
	inline namespace SubName {
		template<typename T>
		struct SA {};
	};
	namespace SubName2 {
	};
};
namespace InlineName {
	template<> class SA<int> {};	// ��һ������дclass���±������
};

// ģ�������using��typedef����ͨ�÷���û��������ģ���ʹ�����棬using��typedef�����
#include <map>
template<typename T> using MapStr = map<T, string>;
void testTemplateAlias() {
	MapStr<int> im;
	im.insert(std::pair<int, string>(3, "hello world"));
	auto iter = im.begin();
	cout << iter->second << endl;
}

// SFINEA ,ƥ��ʧ�ܲ��Ǵ���
struct TestType {
	typedef int foo;
};
template<typename T>
void fwithtype(typename T::foo a) { cout << a << endl; }
template<typename T>
void fwithtype(T a) { cout << a << endl; }

void testSFINEA() {
	fwithtype<TestType>(10);
	fwithtype<int>(10);	//	intû��foo��ƥ��ʧ�ܣ������Ҹ����ʵ�ƥ��
}

int main(int argc, char* argv[]) {
	testDerivedCtr();
	testDeleCtr();
	testPerctForward();
	testInitList();
	testPOD();
	testUnion();
	testUserDefineStr();
	testTemplateAlias();
}