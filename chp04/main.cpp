
// �Ҽ����ŵĸĽ�>>
#include<vector>
using namespace std;
void testRightSys() {
	vector<vector<int>> m;
}

// auto�����Ƶ���auto�Ƶ��ı������뱻��ʼ���Ա����Ƶ����ͣ���ǰ���÷���c++11�в�������
// auto���ܴ���cv
// �������ֻ���Ե�һ�����Ƶ����ͣ���������Ӧ�õ�����ı�����auto a=1,b,c;
// auto�������ں�������
// auto�������ڷǾ�̬��Ա����
// auto������ģ��ʵ����
float getFloat() { return float(3.2); }
void testAutoType() {
	auto a = 5;
	double b = 0;
	auto c = b;
	auto d = getFloat();
}
/* //����ʾ��
void fun1(auto x = 1){}
struct str{auto str=10};
char x[3];
auto z[3] = x;
vector<auto> v = {1};
*/

// decltype �����Ƶ���ģ��ǳ����ã���Ȼ����ģ��Ҳ����
/* 
����: decltype(e)
1 ���e��һ��û�д����ŵı�Ƿ����ʽ�������Ա���ʱ��ʽ����ôdecltype(e)����e��������ʵ�����͡�
�������e��һ�������صĺ�����ᵼ�±���ʱ����
2 ���򣬼���e��������T�����e��һ������ֵ����ôdecltype(e)ΪT&
3 ���򣬼���e��������T,���e��һ����ֵ����decltype(e)ΪT&
4 ���򣬼���e��������T,��decltype(e)ΪT
decltype���Դ���cv����
*/
#include<iostream>
using namespace std;
template<typename T1, typename T2> 
void sum(const T1& t1, const T2& t2, decltype(t1 + t2)& result) {
	result = t1 + t2;
}
struct DC {
	int i;
};
void testDecltype() {
	int i = 0;
	decltype(i) a = 5.6;
	float b = 3.9;
	double c = 9.3;
	decltype(b + c) e;
	sum(b, c, e);
	cout << e << endl;

	const int f = 0;
	volatile int g = 1;
	
	const DC sa = { 0 };
	volatile DC sb;
	cout << is_const<decltype(f)>::value << endl;
	cout << is_volatile<decltype(g)>::value << endl;
	cout << is_const<decltype(sa)>::value << endl;
	cout << is_volatile<decltype(sb)>::value << endl;

}

// ׷�ٷ�������
template<typename T1, typename T2>
auto SumAuto(const T1& t1, const T2& t2) ->decltype(t1 + t2) {
	return t1 + t2;
}
void testReturnType() {
	auto b = SumAuto(1, 2);
	cout << b << endl;
	auto c = SumAuto(2.3, 7.8);
	cout << c << endl;
}

// ���ڷ�Χ��for,��������С��ȷ���Ͳ���ʹ�����������ʵ�������飩
void testForRange() {
	int arry[5] = { 1,32,7,23,9 };
	for (auto i: arry)
	{
		cout << i << endl;
	}
}

int main() {
	testRightSys();
	testDecltype();
	testReturnType();
	testForRange();
}