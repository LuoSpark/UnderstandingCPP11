
// 右尖括号的改进>>
#include<vector>
using namespace std;
void testRightSys() {
	vector<vector<int>> m;
}

// auto类型推导，auto推导的变量必须被初始化以便于推导类型，以前的用法在c++11中不能用了
// auto不能带走cv
// 多个变量只会以第一个来推导类型，并把类型应用到后面的变量，auto a=1,b,c;
// auto不能用于函数参数
// auto不能用于非静态成员变量
// auto不能用模板实例化
float getFloat() { return float(3.2); }
void testAutoType() {
	auto a = 5;
	double b = 0;
	auto c = b;
	auto d = getFloat();
}
/* //错误示范
void fun1(auto x = 1){}
struct str{auto str=10};
char x[3];
auto z[3] = x;
vector<auto> v = {1};
*/

// decltype 类型推导，模板非常有用，当然不是模板也有用
/* 
规则: decltype(e)
1 如果e是一个没有带括号的标记符表达式或者类成员访问表达式，那么decltype(e)就是e所命名的实体类型。
此外如果e是一个被重载的函数则会导致编译时错误
2 否则，假设e的类型是T，如个e是一个将亡值，那么decltype(e)为T&
3 否则，假设e的类型是T,如果e是一个左值，则decltype(e)为T&
4 否则，假设e的类型是T,则decltype(e)为T
decltype可以带走cv属性
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

// 追踪返回类型
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

// 基于范围的for,如果数组大小不确定就不能使用这个（函数实参是数组）
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