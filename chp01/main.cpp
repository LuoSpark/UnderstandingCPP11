#include <iostream>

using namespace std;

#if __cplusplus > 190011L
#pragma message("greate")
#endif
// ��֤__cplusplus��,vsĬ�϶���199711,��Ҫ�޸���Ŀ���Բ�����ȷ���
void printCPPValue() {
	cout << "__cplusplus:" << __cplusplus << endl;
}

int main(int argc, char* argv[]) {
	printCPPValue();
}