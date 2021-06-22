/*
unicode �� ANSI �ַ�������
*/
#include <iostream>
#include <Windows.h>
using namespace std;


/*
�ַ����鱣�����ģ�Ȼ�������

������⣺
���ļ��� ANSI ���뱣��ʱ��Ҳ���� GB2312����
��ӡ����� char ���鱣��������ֽڴ���һ�� OK
����Ϊ�ǿ���̨���뷽ʽҲΪ GB2312�����ԲŲ����������
*/
void test_0() {
	char s[10] = "���";		// ����һ�� GB2312 �ֽڴ�
	cout << s << endl;
	cout << "byte size: " << strlen(s) << endl;
}

/*
ͬ test_0��ֻ���ַ������뷽ʽ�����ת���ַ�
*/
void test_1() {
	// ��Ҳ��һ�� GB2312 �ֽڴ���
	// \u4f60\u597d �͵�ͬ���ַ��� "���"��Ȼ�󱣴��ļ�ʱ�ͱ���Ϊ�� GB2312 ���ֽڴ�
	char s[10] = "\u4f60\u597d";	
	cout << s << endl;
	cout << "byte size: " << strlen(s) << endl;
}

/*
��� unicode �ַ���

������⣺
����̨�� unicode �ַ������ GB2312 ��������������Ź�
*/
void test_2() {
	// �ַ���ǰ��� L����ʾ���ַ���ת�ɶ�Ӧ�� Unicode ��ţ���Ϊ��Щ��űȽϴ󣬳����� 2^9 - 1��
	// Ҳ���ǳ�����һ���ֽڿ��Ա�ʾ�ķ�Χ��������Ҫ�����ֽ������š�
	// ���������Ķ��� unicode �ַ���š�
	wchar_t s[10] = L"���";	 
	cout << s << endl;
	// wcslen �У������ֽڲ��㳤��Ϊ 1
	cout << "byte size: " << wcslen(s) << endl;
}

/*
Unicode �� GB2312 ��ת��
*/
void UnicodeToGB2312(const wchar_t* unicode_s, char* gb2312_s, int size) {
	UINT nCodePage = 936; // GB2312 ����

	// �ú����ҵĽз���Unicode ��Ŵ�ת�ֽڴ�
	// -1 ��ʾһֱת�����ַ�����β
	WideCharToMultiByte(nCodePage, 0, unicode_s, -1, gb2312_s, size, NULL, NULL);
}

void test_3() {
	wchar_t s[10] = L"���";

	char s_new[20];

	UnicodeToGB2312(s, s_new, 20);

	cout << s_new << endl;;
}
 
int main() {
	test_3();
}