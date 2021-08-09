#include <windows.h>
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <shellapi.h> // CommandLineToArgvW
#include <stdio.h>


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow) {
    int argc = 0;

    //
    // ��ȡ Unicode �����в���
    //
    LPWSTR* argv = CommandLineToArgvW(GetCommandLineW(), &argc);

    //
    // ����ת��
    //
    char** newArgv = (char**)malloc(argc * sizeof(char*));
    for (int i = 0; i < argc; ++i) {
        LPWSTR cmd = argv[i];
        //
        // Unicode ת utf-8
        //
        int len = WideCharToMultiByte(CP_UTF8, NULL, cmd, wcslen(cmd), NULL, 0, NULL, NULL);
        char* strUTF8 = (char*)malloc((len + 1) * sizeof(char));
        ZeroMemory(strUTF8, len + 1);
        WideCharToMultiByte(CP_UTF8, NULL, cmd, wcslen(cmd), strUTF8, len, NULL, NULL);
        newArgv[i] = strUTF8;
        printf("argv[%d]:%s\n", i, newArgv[i]);
    }
    system("pause");

    return 0;
}






