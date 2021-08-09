#pragma once
#include<windows.h>

char* pin_code = NULL;  // ����� PIN ��


/**
 * ��ʾ��
 *
 * @sInfo: ��ʾ��Ϣ���磺L"�������"
 */
void showInfoBox(LPCWSTR sInfo) {
    if (sInfo != NULL) {
        MessageBox(NULL, sInfo, TEXT("��ʾ"), MB_ICONINFORMATION);
    }
}

/**
 * unicode ת UTF-8
 */
void UnicodeToUtf8(const wchar_t* unicode, char** utf8) {
    int len = WideCharToMultiByte(CP_UTF8, 0, unicode, -1, NULL, 0, NULL, NULL);
    *utf8 = (char*)malloc(len + 1);
    memset(*utf8, 0, len + 1);
    WideCharToMultiByte(CP_UTF8, 0, unicode, -1, *utf8, len, NULL, NULL);
}


/*
 * InputDialog �¼��ص�
 */
LRESULT CALLBACK InputPINCodeProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    int wmId, wmEvent;
    PAINTSTRUCT ps;
    HDC hdc;
    static HFONT hFont;  //�߼�����
    static HWND hLabUsername;  //��̬�ı���--�û���
    static HWND hLabPassword;  //��̬�ı���--����
    static HWND hEditUsername;  //�����ı������
    static HWND hEditPassword;  //���������
    static HWND hBtnLogin;  //��¼��ť

    //���建����
    TCHAR szPassword[100];

    switch (message) {
    case WM_CREATE:
        //�����߼�����
        hFont = CreateFont(-14, -7, 0, 0, 400,
            FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_CHARACTER_PRECIS,
            CLIP_CHARACTER_PRECIS, DEFAULT_QUALITY, FF_DONTCARE, TEXT("΢���ź�"));

        //������̬�ı���ؼ�--����
        hLabPassword = CreateWindow(TEXT("static"), L"PIN�룺",
            WS_CHILD | WS_VISIBLE | SS_CENTERIMAGE /*��ֱ����*/ | SS_RIGHT /*ˮƽ����*/,
            0, 56, 70, 26,
            hWnd, (HMENU)2, NULL, NULL
        );

        //�������������
        hEditPassword = CreateWindow(TEXT("edit"), TEXT(""),
            WS_CHILD | WS_VISIBLE | WS_BORDER | ES_PASSWORD /*����*/ |
            ES_AUTOHSCROLL /*ˮƽ����*/,
            80, 56, 200, 26,
            hWnd, (HMENU)4, NULL, NULL
        );
        //������ť�ؼ�
        hBtnLogin = CreateWindow(TEXT("button"), TEXT("ȷ��"),
            WS_CHILD | WS_VISIBLE | WS_BORDER | BS_FLAT/*��ƽ��ʽ*/,
            80, 92, 200, 30,
            hWnd, (HMENU)5, NULL, NULL
        );
        //�������ÿؼ�������
        SendMessage(hLabPassword, WM_SETFONT, (WPARAM)hFont, NULL);
        SendMessage(hEditPassword, WM_SETFONT, (WPARAM)hFont, NULL);
        SendMessage(hBtnLogin, WM_SETFONT, (WPARAM)hFont, NULL);
        break;

    case WM_COMMAND:
        wmId = LOWORD(wParam);
        wmEvent = HIWORD(wParam);
        switch (wmId) {
        case 5:  //��ť��HMENU����
            //
            // ��ȡ����
            //
            GetWindowText(hEditPassword, szPassword, 100);
            if (wcslen(szPassword) == 0) {
                showInfoBox(TEXT("���벻��Ϊ��"));
                break;
            }
            else {
                if (pin_code != NULL) {
                    free(pin_code);
                }
                UnicodeToUtf8(szPassword, &pin_code);
            }

            //
            // �˳�����
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
        // TODO:  �ڴ���������ͼ����...
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
 * ��ʾ ���� PIN ��Ĵ���
 *
 * @return PIN ��
 */
const char* showPinDialog() {
    static TCHAR szClassName[] = TEXT("PinDialog");  //��������
    HWND hPinDialog;  //���ھ��
    WNDCLASS wndclass;  //������

    // ע�ᴰ����
    wndclass.style = CS_HREDRAW | CS_VREDRAW;  //���ڷ��
    wndclass.lpfnWndProc = InputPINCodeProc;  //���ڹ���
    wndclass.cbClsExtra = 0;
    wndclass.cbWndExtra = 0;
    wndclass.hInstance = NULL;
    wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);  //����ͼ��
    wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);  //�����ʽ
    wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);  //���ڱ�����ˢ
    wndclass.lpszMenuName = NULL;  //���ڲ˵�
    wndclass.lpszClassName = szClassName;  //��������
    RegisterClass(&wndclass);

    // ��������
    hPinDialog = CreateWindow(
        szClassName,  //�����������
        TEXT("������ PIN �� "),  //���ڱ��⣨�����ڱ�������
        WS_OVERLAPPEDWINDOW,  //���ڷ��
        CW_USEDEFAULT,  //��ʼ��ʱx���λ��
        CW_USEDEFAULT,  //��ʼ��ʱy���λ��
        350,  //���ڿ��
        200,  //���ڸ߶�
        NULL,  //�����ھ��
        NULL,  //���ڲ˵����
        GetModuleHandle(NULL),  //����ʵ�����
        NULL
    );

    //��ʾ����
    ShowWindow(hPinDialog, SW_SHOW);

    //���£����ƣ�����
    UpdateWindow(hPinDialog);

    // �¼�ѭ��
    MSG msg;  //��Ϣ
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);  //������Ϣ
        DispatchMessage(&msg);  //������Ϣ
    }

    return pin_code;
}

