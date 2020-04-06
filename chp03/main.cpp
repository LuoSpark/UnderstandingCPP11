#include <iostream>
using namespace std;


// 继承构造函数，using  对于基类构造函数是私有的，或者虚继承基类是不能使用继承构造函数的
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

// 委派构造函数,使用了委派构造函数就不能再使用初始化列表，另外需要注意不能形成一个委派环
class DeleCtr {
public:
	DeleCtr(int i) :DeleCtr(i,0){}
	DeleCtr(double d):DeleCtr(0,d) {}

private:
	DeleCtr(int i, double d) :m_i(i), m_d(d) { cout << "委派构造函数"<<endl; }
	int m_i;
	double m_d;
};
void testDeleCtr() {
	DeleCtr dc(11);
}

// 右值引用,移动语义构造函数，完美转发，引用折叠
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

// 显示转换操作符
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


// 列表初始化, 函数参数为初始化列表，函数返回初始化列表，自定义类构造函数使用初始化列表
// 还可以防止类型收窄
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

// POD类型 plain old data
// c++11：平凡的和标准布局
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
class NoTrivia5 {	//这个好像跟书上说的不一样，这个应该也是不平凡的，因为访问权限不一样
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


// 非受限联合体，c++11之前，结构体对象不能作为联合体成员
// 所有非引用类型，都可以作为联合体成员
struct SInt {
	int a;
};
union  MyUnion
{
	struct SInt a;		//c++11之前是不行的
	int b;
};
void testUnion(){
	MyUnion mun;
	mun.a.a = 1;
	mun.a = SInt();
}

// 用户自定义字面量,通过自定义后缀（）
// 限制：
// 1 如果字面量为整型，那么字面量操作符函数只可以接受unsigned long long或者const char *为其参数。
// 当unsigned long long 无法容纳其值的时候，会自动转换为以‘\0’为结尾的字符串，并调用const char *为
// 参数的版本
// 2 如果字面量为浮点型数，则字面量操作符可接受long double 或者const char * 为参数。调用规则同1
// 3 如果字面量为字符串，则字面量操作符函数只可接受const char*,size_t为参数
// 4 如果字面量为字符串，则只接受char型为参数
struct Watt { unsigned int v; };
Watt operator "" _w(unsigned long long v) {//_w和""之间必须有空格，
	return { (unsigned int)v };
}

void testUserDefineStr(){
	Watt capacity = 1024_w;
	cout << "Watt:" << capacity.v << endl;;
}

// 内联名字空间
namespace InlineName {
	
	inline namespace SubName {
		template<typename T>
		struct SA {};
	};
	namespace SubName2 {
	};
};
namespace InlineName {
	template<> class SA<int> {};	// 第一次忘记写class导致编译出错
};

// 模板别名，using和typedef在普通用法上没有区别，在模板的使用上面，using比typedef更灵活
#include <map>
template<typename T> using MapStr = map<T, string>;
void testTemplateAlias() {
	MapStr<int> im;
	im.insert(std::pair<int, string>(3, "hello world"));
	auto iter = im.begin();
	cout << iter->second << endl;
}

// SFINEA ,匹配失败不是错误
struct TestType {
	typedef int foo;
};
template<typename T>
void fwithtype(typename T::foo a) { cout << a << endl; }
template<typename T>
void fwithtype(T a) { cout << a << endl; }

void testSFINEA() {
	fwithtype<TestType>(10);
	fwithtype<int>(10);	//	int没有foo，匹配失败，会再找个合适的匹配
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