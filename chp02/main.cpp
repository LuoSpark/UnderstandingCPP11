#include <iostream>
#include <map>
#include <vector>
using namespace std;

// c++11 与c99兼容的宏
#define PM(name)  cout << #name<<":" << name << endl;
void printMacroC99() {
	PM(__STDC_HOSTED__);
	//PM(__STDC__);
	//PM(__STDC_VERSION__);
	//PM(__STDC_ISO_10646__);

}

// __func__
struct AWithName {
	AWithName() {cout << __func__ << endl; }
};
class BWithName {
public:
	BWithName() { cout << __func__ << endl; }
};
void getFunctionName() {
	AWithName an;
	BWithName bn;
	cout << __func__ << endl;
}

// #pragma 与c++11的_Pragma操作符

// __VA_ARGS__
#define LOG(...) {cout<<__FILE__<<":"<<__func__<<":"<<__VA_ARGS__<<endl;}

//char wchar_t
void dealCharToWchar_t() {
	//const char* pc = "abcde";
	//const wchar_t* pwc = "我们";
}

// long long
void printLongLong() {
	long long a = 43ll;
	unsigned long long b = 40ll;
	cout << sizeof(a) << " " << a << endl;
	cout << sizeof(b) << ":" <<b << endl;
}

//__cplusplus宏
#if __cplusplus > 201103L
#pragma message("support cpp11")
#endif

// 静态断言（编译时断言） assert（运行时断言） #error(预处理是断言)
void checkParamWithStaticAssert(int age) {
	// static_assert第一个参数必须是常量表达式，使用变量不行
	//static_assert((age < 0), "年龄不能少于0");
	cout << sizeof(double) << endl;
	static_assert( (5 != 4), "wrong");
}

//noexcept 
// noexcept有两种，一种说明符，一种是操作符
// noexcept 虽然不是函数类型的一部分，但是它还是会影响函数指针和虚函数的
void funcNoexcept() noexcept(noexcept(BWithName())) {
	cout << "如果类型BWithName 会抛出异常，那么我也会抛出一样，"
		"如果它不抛出，我也不会" << endl;
}

void testRvalue() {
	string s1, s2;
	s1 + s2 = "hello";	//这个其实违反了右值
	cout << s1 << endl;
}


// 就地初始化成员，快速初始化成员变量,初始化列表后作用与就地初始化，初始化列表优先
struct LocalInit {
	int a = 0;
	double b{ 1.0 };
	LocalInit() {};
	LocalInit(double d) :b(d) {}
	//const static char c = 'c';
};
//const  char LocalInit::c;

// sizeof 作用于类的非静态成员变量，而不需要定义一个该类的对象
void testSizeofClassMember() {
	cout << sizeof(LocalInit::b) << endl;	//c++ 11之前会报错，对于非静态成员c++11之前只能用对象来访问
	// 或者用 sizeof( ((Type*)0)->member ) 

}

void localInitTest() {
	LocalInit li;
	LocalInit li2(3.5);
	cout << "li.a:" << li.a << " li.b:" << li.b << endl;
	cout << "li.a:" << li2.a << " li.b:" << li2.b << endl;
}

// friend ,扩展的friend
// 要实现如下的功能，只能特例化
//template <typename T1>
//class Temp {
//public:
//	//typedef TType typename T1;
//	friend class MyT;
//	int getValue() { return a; }
//private:
//	int a;
//};
//class MyT {
//public:
//  这里特例化了一个Temp，不用特例化不行
//	bool setValue( Temp<MyT>& t, int v) {
//		t.a = v;
//		return true;
//	}
//};
//template 
//void testTemplateFriend() {
//	Temp<MyT> t;
//	MyT mt;
//	mt.setValue(t, 80);
//	cout << t.getValue() << endl;
//}
// 使用扩展的friend可以简单地实现
template <typename T1>
class Temp {
public:
	friend  T1;	//c++11 扩展后的friend
	int getValue() { return a; }
private:
	int a;
};
class MyT {
public:
	bool setValue( Temp<MyT>& t, int v) {
		t.a = v;
		return true;
	}
};
void testTemplateFriend() {
	Temp<MyT> t;
	MyT mt;
	mt.setValue(t, 80);
	cout << t.getValue() << endl;
}

// final/override
class BaseWithVirtual {
public:
	virtual ~BaseWithVirtual() {}
	virtual void fun1(int a) final{ cout << "BaseWithVirtual:" << __func__ << "通过final我不想派生类重载我了"<<endl; }
	virtual void fun2(int a)  { cout << "BaseWithVirtual:" << __func__ << endl; }
};
class Derived :public BaseWithVirtual {
public:
	//virtual void fun1(int a) { cout << "I want to override fun1" << endl; }
	virtual void fun2(int a) override { cout << "I override fun2 ,通过override不怕写错名字和参数,也不怕重写了非虚函数" << endl; }
};
void testFinalOverride() {
	Derived d;
	d.fun1(1);
	d.fun2(2);
}

// 默认函数模板参数，在c++11之前，是会导致编译错误的，不支持，类模板默认参数之前已经支持了
// c++11默认函数模板参数，跟类模板默认参数不一样的一个点事，函数默认模板参数默认参数可以在非默认参数之前
template<typename T1=int, typename T2>
void defaultTemplatePara(T1 a, T2 b) {
	cout << a << " " << b << endl;
}


//外部模板声明,主要用于减少编译局编译模板用的时间，避免了重复实例化一样的函数，然后再删除保留一份
// 1 先实例化
// 2 外部声明
extern template void defaultTemplatePara<int, int>(int, int);	// 外部声明
template void defaultTemplatePara<int, int>(int, int);//	实例化

//局部和匿名类型做模板参数，在c++11之前是不行的
template <typename T> class X {};
template <typename T> void TempFucn(T a) {};
struct A {} a;
struct { int a; }b;	// 匿名类型变量
typedef struct { int b; } B;	//匿名类型
void func() {
	struct C {} c;	// C 是局部类型
	// 下面的除了x1,a能在c++98标准下编译通过外，其他的都不能，不过所有的都可以在c++11下比编译通过。
	X<A> x1;
	X<B> x2;
	X<C> x3;

	TempFucn(a);
	TempFucn(b);
	TempFucn(c);
}
//
int main(int argc, char* argv[]) {
	printMacroC99();
	getFunctionName();
	//map<int, vector<int>> mv;
	LOG(3);
	printLongLong();
	checkParamWithStaticAssert(10);
	//checkParamWithStaticAssert(-1);
	funcNoexcept();
	testRvalue();
	localInitTest();
	testSizeofClassMember();
	//testTemplateFriend();
	testFinalOverride();
	defaultTemplatePara(1, "fdadsa");
	defaultTemplatePara("fdafda", 4.5);
}