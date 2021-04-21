/**
 * 弹出一个消息框
 */
#include <windows.h>

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    MessageBox(NULL, "hello,world", "TIPS", 0);

    return 0;
}