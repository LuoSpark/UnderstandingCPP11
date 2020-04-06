#include<iostream>
using namespace std;
// 强类型枚举,匿名的强类型可能什么都做不了
enum class Type:int {General, Light, Medium, Heavy};
enum class Category {General =1,Pistol, MachineGun,Cannon};
void testStrongEnum() {
	cout << "强类型枚举成员名称不会输出到其父作用域空间\n"
		"强类型枚举成员的值不会与整型隐式地互相转换\n"
		"强类型枚举可以指定底层类型\n" << endl;
	Type t = Type::Light;
	//t = General;
	if (t > Type::General)
	{
		cout << "General Weapon" << endl;
	}
	//if (t > 0)
	//{
	//	cout << "Not General Weapon" << endl;
	//}
	if ((int)t > 0) {
		cout << "Not General Weapon" << endl;
	}
	cout << is_pod<Type>::value << endl;
	cout << is_pod<Category>::value << endl;
}


// 智能指针与垃圾回收
// shared_ptr unique_ptr weak_ptr


int main(int argc, char* argv[])
{
	testStrongEnum();
}