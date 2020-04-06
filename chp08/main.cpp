#include<iostream>
using namespace std;

// ����

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

// ͨ������  [[attr1]]  [[noreturn]] [[carries_dependency]]


// unicode֧��
void testUnicode() {
	char p[] = u8"����һ����";
	char16_t pu16[] = u"�����ϰ���";
	char32_t pu32[] = U"������ձ�������";
	cout << p << endl;
	cout << pu16 << endl;
	cout << pu32 << endl;
	cout << sizeof(p) << endl;
	cout << sizeof(pu16) << endl;
	cout << sizeof(pu32) << endl;
}

// ԭ���ַ�
void testRowUnicode() {
	char16_t pu16[] = uR"(�����ϰ��� \n abc)";
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