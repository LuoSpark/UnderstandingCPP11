#include <iostream>
#include <map>
#include <vector>
using namespace std;

// c++11 ��c99���ݵĺ�
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

// #pragma ��c++11��_Pragma������

// __VA_ARGS__
#define LOG(...) {cout<<__FILE__<<":"<<__func__<<":"<<__VA_ARGS__<<endl;}

//char wchar_t
void dealCharToWchar_t() {
	//const char* pc = "abcde";
	//const wchar_t* pwc = "����";
}

// long long
void printLongLong() {
	long long a = 43ll;
	unsigned long long b = 40ll;
	cout << sizeof(a) << " " << a << endl;
	cout << sizeof(b) << ":" <<b << endl;
}

//__cplusplus��
#if __cplusplus > 201103L
#pragma message("support cpp11")
#endif

// ��̬���ԣ�����ʱ���ԣ� assert������ʱ���ԣ� #error(Ԥ�����Ƕ���)
void checkParamWithStaticAssert(int age) {
	// static_assert��һ�����������ǳ������ʽ��ʹ�ñ�������
	//static_assert((age < 0), "���䲻������0");
	cout << sizeof(double) << endl;
	static_assert( (5 != 4), "wrong");
}

//noexcept 
// noexcept�����֣�һ��˵������һ���ǲ�����
// noexcept ��Ȼ���Ǻ������͵�һ���֣����������ǻ�Ӱ�캯��ָ����麯����
void funcNoexcept() noexcept(noexcept(BWithName())) {
	cout << "�������BWithName ���׳��쳣����ô��Ҳ���׳�һ����"
		"��������׳�����Ҳ����" << endl;
}

void testRvalue() {
	string s1, s2;
	s1 + s2 = "hello";	//�����ʵΥ������ֵ
	cout << s1 << endl;
}


// �͵س�ʼ����Ա�����ٳ�ʼ����Ա����,��ʼ���б��������͵س�ʼ������ʼ���б�����
struct LocalInit {
	int a = 0;
	double b{ 1.0 };
	LocalInit() {};
	LocalInit(double d) :b(d) {}
	//const static char c = 'c';
};
//const  char LocalInit::c;

// sizeof ��������ķǾ�̬��Ա������������Ҫ����һ������Ķ���
void testSizeofClassMember() {
	cout << sizeof(LocalInit::b) << endl;	//c++ 11֮ǰ�ᱨ�����ڷǾ�̬��Աc++11֮ǰֻ���ö���������
	// ������ sizeof( ((Type*)0)->member ) 

}

void localInitTest() {
	LocalInit li;
	LocalInit li2(3.5);
	cout << "li.a:" << li.a << " li.b:" << li.b << endl;
	cout << "li.a:" << li2.a << " li.b:" << li2.b << endl;
}

// friend ,��չ��friend
// Ҫʵ�����µĹ��ܣ�ֻ��������
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
//  ������������һ��Temp����������������
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
// ʹ����չ��friend���Լ򵥵�ʵ��
template <typename T1>
class Temp {
public:
	friend  T1;	//c++11 ��չ���friend
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
	virtual void fun1(int a) final{ cout << "BaseWithVirtual:" << __func__ << "ͨ��final�Ҳ�����������������"<<endl; }
	virtual void fun2(int a)  { cout << "BaseWithVirtual:" << __func__ << endl; }
};
class Derived :public BaseWithVirtual {
public:
	//virtual void fun1(int a) { cout << "I want to override fun1" << endl; }
	virtual void fun2(int a) override { cout << "I override fun2 ,ͨ��override����д�����ֺͲ���,Ҳ������д�˷��麯��" << endl; }
};
void testFinalOverride() {
	Derived d;
	d.fun1(1);
	d.fun2(2);
}

// Ĭ�Ϻ���ģ���������c++11֮ǰ���ǻᵼ�±������ģ���֧�֣���ģ��Ĭ�ϲ���֮ǰ�Ѿ�֧����
// c++11Ĭ�Ϻ���ģ�����������ģ��Ĭ�ϲ�����һ����һ�����£�����Ĭ��ģ�����Ĭ�ϲ��������ڷ�Ĭ�ϲ���֮ǰ
template<typename T1=int, typename T2>
void defaultTemplatePara(T1 a, T2 b) {
	cout << a << " " << b << endl;
}


//�ⲿģ������,��Ҫ���ڼ��ٱ���ֱ���ģ���õ�ʱ�䣬�������ظ�ʵ����һ���ĺ�����Ȼ����ɾ������һ��
// 1 ��ʵ����
// 2 �ⲿ����
extern template void defaultTemplatePara<int, int>(int, int);	// �ⲿ����
template void defaultTemplatePara<int, int>(int, int);//	ʵ����

//�ֲ�������������ģ���������c++11֮ǰ�ǲ��е�
template <typename T> class X {};
template <typename T> void TempFucn(T a) {};
struct A {} a;
struct { int a; }b;	// �������ͱ���
typedef struct { int b; } B;	//��������
void func() {
	struct C {} c;	// C �Ǿֲ�����
	// ����ĳ���x1,a����c++98��׼�±���ͨ���⣬�����Ķ����ܣ��������еĶ�������c++11�±ȱ���ͨ����
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