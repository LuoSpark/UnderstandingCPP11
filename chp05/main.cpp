#include<iostream>
using namespace std;
// ǿ����ö��,������ǿ���Ϳ���ʲô��������
enum class Type:int {General, Light, Medium, Heavy};
enum class Category {General =1,Pistol, MachineGun,Cannon};
void testStrongEnum() {
	cout << "ǿ����ö�ٳ�Ա���Ʋ���������丸������ռ�\n"
		"ǿ����ö�ٳ�Ա��ֵ������������ʽ�ػ���ת��\n"
		"ǿ����ö�ٿ���ָ���ײ�����\n" << endl;
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


// ����ָ������������
// shared_ptr unique_ptr weak_ptr


int main(int argc, char* argv[])
{
	testStrongEnum();
}