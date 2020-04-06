#include<iostream>
using namespace std;

//常量表达式
//const int GetConst() {
//	int a = 5;
//	return a;
//}
constexpr int GetConstexpr(){
	// 常量表达式函数，可以递归
	// 函数只有单一的return返回语句
	// 函数必须返回值
	// 在使用前必须已有定义
	// return 返回语句表达式中不能使用非常量表达式的函数，全局数据，且必须是一个常量表达式
	return 5;
}

class ConstexprType {
public:
	constexpr ConstexprType(int i) :m_i(i) {}	//函数体必须为空，且初始化列表只能是有常量表达式赋值
	//constexpr virtual void Fun1() {};
	void print() const { cout << m_i << endl; }
private:
	int m_i;
};

class NoConstType {
public:
	NoConstType() {}
};
template<typename T> 
constexpr T ConstExp(T t) {	//实例化是如果T没有constexpr，则会忽略constexpr而生产一个没有constexpr的版本
	return t;
}

void testConstexpr() {
	//int arr1[GetConst()] = { 1,2,4, };
	const int arrsize = 10;
	int arr2[arrsize];
	int array[GetConstexpr()] = {1,2,36,7,};
	cout << array[1] << endl;

	ConstexprType ct{ 10 };
	ct.print();
	constexpr ConstexprType cct{ 20 };
	cct.print();

	NoConstType nct1;
	NoConstType nct2 = ConstExp(nct1);
	//constexpr NoConstType nct3 = ConstExp(nct1);
}

// 变长模板
// 模板类型参数包，模板非类型参数包，解包
// sizeof...(args)
// 可以展开参数包的位置：
/*
1 表达式
2 初始化列表
3 基类描述列表
4 类成员初始化列表
5 模板参数列表
6 通用属性列
7 lambda函数捕捉列表
*/
template <long... nums>struct Multiply ;

template<long first, long ...last>
struct Multiply<first, last...> {
	static const long val = first * Multiply<last...>::val;
};

template <>
struct Multiply<> {
	static const long val = 1;
};

void testVariadicTemplate() {
	cout << Multiply<>::val << endl;
	cout << Multiply<2, 3, 4, 5>::val << endl;
	cout << Multiply<2, 3, 4, 5,6>::val << endl;
}

// 原子类型与原子操作 
// 原子操作不会被打断，锁可以被打断，内存模型（指令顺序，编译器不改，cpu不改）
#include<atomic>
#include<thread>
#include<iostream>
using namespace std;

atomic_llong total{ 0 };

void func(int) {
	for (long long i = 0; i < 10000000LL; i++) {
		total += i;
	}
}

void testThread() {
	thread t1(func, 0);
	thread t2(func, 0);

	t1.join();
	t2.join();
	cout << total << endl;
}
// 内存模型
#include<atomic>
#include<iostream>
#include<thread>

using namespace std;
atomic<int> a{ 0 };
atomic<int> b{ 0 };

int thread_local errorCode = 0;	// 线程局部存储
int Thread1(int) {
	int t = 1;
	errorCode = 3;
	a.store(t, memory_order_relaxed);
	b.store(2, memory_order_release);	// 本原子操作前，所有的写原子操作必须完成
	cout <<"errorCode:"<< errorCode << endl;
	return 0;
}

int Thread2(int) {
	while (b.load(memory_order_acquire) != 2);	// 自旋
	cout << a.load(memory_order_relaxed);
	errorCode = 4;
	cout << "errorCode:" << errorCode << endl;
	return 0;
}

void testMemoryOrder() {
	thread t1(Thread1, 0);
	thread t2(Thread2, 0);
	t1.join();
	t2.join();
}

// 快速退出
// 正常退出和异常退出的区别
// 怎么在正常退出时，又不执行析构呢，应为进程结束后系统会回收资源。
struct A { ~A() { cout << "Destruct A" << endl; } };
void CloseDevice() { cout << "device is closed." << endl; }

void testQuickExit() {
	A a;
	at_quick_exit(CloseDevice);
	quick_exit(0);
}


//其他无关测试
class Base1 {
public:
	char a;
};
class Decrived1:public Base1 {
public:
	int b;
};

void testPrint() {
	//Decrived1 d;
	cout << offsetof(Decrived1, a) << endl;;
	cout << offsetof(Decrived1, b) << endl;;
}
int main(int argc, char* argv[]) {
	//
	cout << "errorCode:" << errorCode << endl;
	testConstexpr();
	testVariadicTemplate();
	testPrint();
	testThread();
	testMemoryOrder();
	cout << "errorCode:" << errorCode << endl;
	testQuickExit();
}