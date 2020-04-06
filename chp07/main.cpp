#include<iostream>
using namespace std;

// nullptr
void f(char* p) {
	cout << "invoke f(char*)" << endl;
}
void f(int) {
	cout << "invoke f(int)" << endl;
}

template<typename T>
void g(T* t) {
}
template<typename T>
void h(T t) {
}
void testNullptr() {
	nullptr_t np=nullptr;
	const nullptr_t&& dealfut_npt = nullptr;
	cout << "nullptr_t np :%x" << &np << endl;
	cout << "nullptr_t dealfut_npt :%x" << &dealfut_npt << endl;
	f(np);
	f(nullptr);
	f(0);
	//nullptr_t npt;
	//if (npt == nullptr) {
	//	cout << "nullptr_t == nullptr" << endl;
	//} else {
	//	cout << "nullptr_t != nullptr" << endl;
	//}
	if (nullptr == 0) {
		cout << "nullptr == 0" << endl;
	}
	//int a = nullptr;
	int b = reinterpret_cast<int>(nullptr);
	cout << sizeof(nullptr) << endl;
	//g(nullptr);
	g((int*)nullptr);
	h(nullptr);
	h(0);
	h((float*)nullptr);
}

class CWithPtr {
public:
	CWithPtr() { 
		m_ptr = new char[10]; 
		memset(m_ptr, 0, 10);
		memcpy(m_ptr, "hello", 5);
	}
	CWithPtr(const CWithPtr&) = delete;
	CWithPtr(CWithPtr&&) = default;
	void print() {
		if (m_ptr) {
			cout << m_ptr << endl;
		} else {
			cout << "NULL" << endl;
		}
	}
	~CWithPtr() {
		if (m_ptr) {
			cout << &m_ptr << endl;
			delete[]m_ptr;
		}
	}
private:
	char* m_ptr;
};
void testDefaultMoveCtr() {
	CWithPtr cp1;
	CWithPtr cp2(move(cp1));
	cp1.print();
	//cp2.print();//默认移动构造函数不会重置对象重指针为null

}

// lambda函数
void testLambda() {
	int x{ 0 };
	//下面的体现了mutalbe的作用
	auto f1 = [=]() mutable { x = 42; };
	//auto f2 = [=]() {x = 42; };
}


#include<functional>
int main() {
	testNullptr();
	testDefaultMoveCtr();
	testLambda();
	std::bind
	return 0;
}