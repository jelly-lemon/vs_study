/*
unicode 即是字符集，也可以看作编码集，因为规定了每个字符的码位，码位占两个字节。
所以有 unicode 字符串这种类型。
*/

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