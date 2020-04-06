#include<iostream>
using namespace std;

// 对齐

class Double4 {
	double a;
	double b;
	double c;
	double d;
};


void testAlign() {
	alignas(double) int b = 4;
	cout << "b: " << alignof(int) << endl;
	cout << alignof(std::max_align_t) << endl;
	const int size = 100;
	size_t sz = 100;
	Double4* pd4 = new Double4[size];
	void* pt = pd4;
	cout << "pd4:" << alignof(Double4) << endl;

	std::align(sizeof(Double4) * 4, 100, pt, sz);
	cout << "pd4:" << alignof(Double4) << endl;

}

// 通用属性  [[attr1]]  [[noreturn]] [[carries_dependency]]


// unicode支持
void testUnicode() {
	char p[] = u8"我是一个兵";
	char16_t pu16[] = u"来自老百姓";
	char32_t pu32[] = U"打败了日本侵略者";
	cout << p << endl;
	cout << pu16 << endl;
	cout << pu32 << endl;
	cout << sizeof(p) << endl;
	cout << sizeof(pu16) << endl;
	cout << sizeof(pu32) << endl;
}

// 原生字符
void testRowUnicode() {
	char16_t pu16[] = uR"(来自老百姓 \n abc)";
	char p[] = R"(hello \n world)";
	cout << pu16 << endl;
	cout << p << endl;
}
int main() {
	testAlign();
	testUnicode();
	testRowUnicode();
	int null = 0, * p = nullptr;
	return 0;
	bind()
}