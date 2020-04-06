#include <iostream>

using namespace std;

#if __cplusplus > 190011L
#pragma message("greate")
#endif
// 验证__cplusplus宏,vs默认都是199711,需要修改项目属性才能正确输出
void printCPPValue() {
	cout << "__cplusplus:" << __cplusplus << endl;
}

int main(int argc, char* argv[]) {
	printCPPValue();
}