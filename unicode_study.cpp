#include<iostream>
#include<windows.h>

using namespace std;


int main() {
	system("chcp 65001"); // 控制台 utf-8

	wchar_t str_1[100] = L"你好";
	char str_2[100] = "你好";

	cout << str_1 << endl;
	cout << str_2 << endl;


	system("pause");
	return 0;
}