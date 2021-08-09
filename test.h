#pragma once
#include<windows.h>

char* pin_code = NULL;  // 输入的 PIN 码


/**
 * 提示框
 *
 * @sInfo: 提示信息，如：L"密码错误"
 */
void showInfoBox(LPCWSTR sInfo) {
    if (sInfo != NULL) {
        MessageBox(NULL, sInfo, TEXT("提示"), MB_ICONINFORMATION);
    }
}

/**
 * unicode 转 UTF-8
 */
void UnicodeToUtf8(const wchar_t* unicode, char** utf8) {
    int len = WideCharToMultiByte(CP_UTF8, 0, unicode, -1, NULL, 0, NULL, NULL);
    *utf8 = (char*)malloc(len + 1);
    memset(*utf8, 0, len + 1);
    WideCharToMultiByte(CP_UTF8, 0, unicode, -1, *utf8, len, NULL, NULL);
}


/*
 * InputDialog 事件回调
 */
LRESULT CALLBACK InputPINCodeProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    int wmId, wmEvent;
    PAINTSTRUCT ps;
    HDC hdc;
    static HFONT hFont;  //逻辑字体
    static HWND hLabUsername;  //静态文本框--用户名
    static HWND hLabPassword;  //静态文本框--密码
    static HWND hEditUsername;  //单行文本输入框
    static HWND hEditPassword;  //密码输入框
    static HWND hBtnLogin;  //登录按钮

    //定义缓冲区
    TCHAR szPassword[100];

    switch (message) {
    case WM_CREATE:
        //创建逻辑字体
        hFont = CreateFont(-14, -7, 0, 0, 400,
            FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_CHARACTER_PRECIS,
            CLIP_CHARACTER_PRECIS, DEFAULT_QUALITY, FF_DONTCARE, TEXT("微软雅黑"));

        //创建静态文本框控件--密码
        hLabPassword = CreateWindow(TEXT("static"), L"PIN码：",
            WS_CHILD | WS_VISIBLE | SS_CENTERIMAGE /*垂直居中*/ | SS_RIGHT /*水平居右*/,
            0, 56, 70, 26,
            hWnd, (HMENU)2, NULL, NULL
        );

        //创建密码输入框
        hEditPassword = CreateWindow(TEXT("edit"), TEXT(""),
            WS_CHILD | WS_VISIBLE | WS_BORDER | ES_PASSWORD /*密码*/ |
            ES_AUTOHSCROLL /*水平滚动*/,
            80, 56, 200, 26,
            hWnd, (HMENU)4, NULL, NULL
        );
        //创建按钮控件
        hBtnLogin = CreateWindow(TEXT("button"), TEXT("确定"),
            WS_CHILD | WS_VISIBLE | WS_BORDER | BS_FLAT/*扁平样式*/,
            80, 92, 200, 30,
            hWnd, (HMENU)5, NULL, NULL
        );
        //依次设置控件的字体
        SendMessage(hLabPassword, WM_SETFONT, (WPARAM)hFont, NULL);
        SendMessage(hEditPassword, WM_SETFONT, (WPARAM)hFont, NULL);
        SendMessage(hBtnLogin, WM_SETFONT, (WPARAM)hFont, NULL);
        break;

    case WM_COMMAND:
        wmId = LOWORD(wParam);
        wmEvent = HIWORD(wParam);
        switch (wmId) {
        case 5:  //按钮的HMENU参数
            //
            // 获取密码
            //
            GetWindowText(hEditPassword, szPassword, 100);
            if (wcslen(szPassword) == 0) {
                showInfoBox(TEXT("密码不能为空"));
                break;
            }
            else {
                if (pin_code != NULL) {
                    free(pin_code);
                }
                UnicodeToUtf8(szPassword, &pin_code);
            }

            //
            // 退出窗口
            //
            DeleteObject(hFont);
            DestroyWindow(hWnd);
            PostQuitMessage(0);
            break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
        break;
    case WM_PAINT:
        hdc = BeginPaint(hWnd, &ps);
        // TODO:  在此添加任意绘图代码...
        EndPaint(hWnd, &ps);
        break;

    case WM_DESTROY:
        DeleteObject(hFont);
        PostQuitMessage(0);
        break;

    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }

    return 0;
}




/**
 * 显示 输入 PIN 码的窗口
 *
 * @return PIN 码
 */
const char* showPinDialog() {
    static TCHAR szClassName[] = TEXT("PinDialog");  //窗口类名
    HWND hPinDialog;  //窗口句柄
    WNDCLASS wndclass;  //窗口类

    // 注册窗口类
    wndclass.style = CS_HREDRAW | CS_VREDRAW;  //窗口风格
    wndclass.lpfnWndProc = InputPINCodeProc;  //窗口过程
    wndclass.cbClsExtra = 0;
    wndclass.cbWndExtra = 0;
    wndclass.hInstance = NULL;
    wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);  //窗口图标
    wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);  //鼠标样式
    wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);  //窗口背景画刷
    wndclass.lpszMenuName = NULL;  //窗口菜单
    wndclass.lpszClassName = szClassName;  //窗口类名
    RegisterClass(&wndclass);

    // 创建窗口
    hPinDialog = CreateWindow(
        szClassName,  //窗口类的名字
        TEXT("请输入 PIN 码 "),  //窗口标题（出现在标题栏）
        WS_OVERLAPPEDWINDOW,  //窗口风格
        CW_USEDEFAULT,  //初始化时x轴的位置
        CW_USEDEFAULT,  //初始化时y轴的位置
        350,  //窗口宽度
        200,  //窗口高度
        NULL,  //父窗口句柄
        NULL,  //窗口菜单句柄
        GetModuleHandle(NULL),  //程序实例句柄
        NULL
    );

    //显示窗口
    ShowWindow(hPinDialog, SW_SHOW);

    //更新（绘制）窗口
    UpdateWindow(hPinDialog);

    // 事件循环
    MSG msg;  //消息
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);  //翻译消息
        DispatchMessage(&msg);  //分派消息
    }

    return pin_code;
}

