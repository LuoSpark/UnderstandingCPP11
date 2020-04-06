#include<iostream>
using namespace std;

//�������ʽ
//const int GetConst() {
//	int a = 5;
//	return a;
//}
constexpr int GetConstexpr(){
	// �������ʽ���������Եݹ�
	// ����ֻ�е�һ��return�������
	// �������뷵��ֵ
	// ��ʹ��ǰ�������ж���
	// return ���������ʽ�в���ʹ�÷ǳ������ʽ�ĺ�����ȫ�����ݣ��ұ�����һ���������ʽ
	return 5;
}

class ConstexprType {
public:
	constexpr ConstexprType(int i) :m_i(i) {}	//���������Ϊ�գ��ҳ�ʼ���б�ֻ�����г������ʽ��ֵ
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
constexpr T ConstExp(T t) {	//ʵ���������Tû��constexpr��������constexpr������һ��û��constexpr�İ汾
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

// �䳤ģ��
// ģ�����Ͳ�������ģ������Ͳ����������
// sizeof...(args)
// ����չ����������λ�ã�
/*
1 ���ʽ
2 ��ʼ���б�
3 ���������б�
4 ���Ա��ʼ���б�
5 ģ������б�
6 ͨ��������
7 lambda������׽�б�
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

// ԭ��������ԭ�Ӳ��� 
// ԭ�Ӳ������ᱻ��ϣ������Ա���ϣ��ڴ�ģ�ͣ�ָ��˳�򣬱��������ģ�cpu���ģ�
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
// �ڴ�ģ��
#include<atomic>
#include<iostream>
#include<thread>

using namespace std;
atomic<int> a{ 0 };
atomic<int> b{ 0 };

int thread_local errorCode = 0;	// �ֲ߳̾��洢
int Thread1(int) {
	int t = 1;
	errorCode = 3;
	a.store(t, memory_order_relaxed);
	b.store(2, memory_order_release);	// ��ԭ�Ӳ���ǰ�����е�дԭ�Ӳ����������
	cout <<"errorCode:"<< errorCode << endl;
	return 0;
}

int Thread2(int) {
	while (b.load(memory_order_acquire) != 2);	// ����
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

// �����˳�
// �����˳����쳣�˳�������
// ��ô�������˳�ʱ���ֲ�ִ�������أ�ӦΪ���̽�����ϵͳ�������Դ��
struct A { ~A() { cout << "Destruct A" << endl; } };
void CloseDevice() { cout << "device is closed." << endl; }

void testQuickExit() {
	A a;
	at_quick_exit(CloseDevice);
	quick_exit(0);
}


//�����޹ز���
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