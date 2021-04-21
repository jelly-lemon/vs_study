/*
unicode 与 ANSI 字符串问题
*/
#include <iostream>
#include <Windows.h>
using namespace std;


/*
字符数组保存中文，然后输出。

个人理解：
本文件用 ANSI 编码保存时（也就是 GB2312），
打印输出用 char 数组保存的中文字节串，一切 OK
我认为是控制台解码方式也为 GB2312，所以才不会出现问题
*/
void test_0() {
	char s[10] = "你好";		// 这是一个 GB2312 字节串
	cout << s << endl;
	cout << "byte size: " << strlen(s) << endl;
}

/*
同 test_0，只是字符串输入方式变成了转义字符
*/
void test_1() {
	// 这也是一个 GB2312 字节串。
	// \u4f60\u597d 就等同于字符串 "你好"，然后保存文件时就保存为了 GB2312 的字节串
	char s[10] = "\u4f60\u597d";	
	cout << s << endl;
	cout << "byte size: " << strlen(s) << endl;
}

/*
输出 unicode 字符串

个人理解：
控制台把 unicode 字符编号用 GB2312 来解析，不出错才怪
*/
void test_2() {
	// 字符串前面加 L，表示将字符串转成对应的 Unicode 编号，因为有些编号比较大，超过了 2^9 - 1，
	// 也就是超过了一个字节可以表示的范围，所以需要两个字节来存编号。
	// 数组里面存的都是 unicode 字符编号。
	wchar_t s[10] = L"你好";	 
	cout << s << endl;
	// wcslen 中，两个字节才算长度为 1
	cout << "byte size: " << wcslen(s) << endl;
}

/*
Unicode 到 GB2312 的转换
*/
void UnicodeToGB2312(const wchar_t* unicode_s, char* gb2312_s, int size) {
	UINT nCodePage = 936; // GB2312 代号

	// 该函数我的叫法：Unicode 编号串转字节串
	// -1 表示一直转换到字符串结尾
	WideCharToMultiByte(nCodePage, 0, unicode_s, -1, gb2312_s, size, NULL, NULL);
}

void test_3() {
	wchar_t s[10] = L"你好";

	char s_new[20];

	UnicodeToGB2312(s, s_new, 20);

	cout << s_new << endl;;
}
 
int main() {
	test_3();
}