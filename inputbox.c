#include<windows.h>

/**
 * pin �������
 *
 * @param hWnd
 * @param message
 * @param wParam
 * @param lParam
 * @return
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
    TCHAR szUsername[100];
    TCHAR szPassword[100];
    TCHAR szUserInfo[200];
    switch (message) {
    case WM_CREATE:
        //�����߼�����
        hFont = CreateFont(-14/*��*/, -7/*��*/, 0, 0, 400 /*һ�����ֵ��Ϊ400*/,
            FALSE/*б��?*/, FALSE/*�»���?*/, FALSE/*ɾ����?*/, DEFAULT_CHARSET,
            OUT_CHARACTER_PRECIS, CLIP_CHARACTER_PRECIS, DEFAULT_QUALITY,
            FF_DONTCARE, TEXT("΢���ź�")
        );
        //������̬�ı���ؼ�--����
        hLabPassword = CreateWindow(TEXT("static"), TEXT("PIN�룺"),
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
            //��ȡ����������
            GetWindowText(hEditPassword, szPassword, 100);
            wsprintf(szUserInfo, TEXT("C������������ʾ��\r\n�����û����룺%s"), szPassword);
            MessageBox(hWnd, szUserInfo, TEXT("��Ϣ��ʾ"), MB_ICONINFORMATION);
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
 * �ı������� GBK ���룬������ʾ����
 *
 * @param hWnd
 * @param message
 * @param wParam
 * @param lParam
 * @return
 */
LRESULT CALLBACK LoginProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
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
    TCHAR szUsername[100];
    TCHAR szPassword[100];
    TCHAR szUserInfo[200];
    switch (message) {
    case WM_CREATE:
        //�����߼�����
        hFont = CreateFont(-14/*��*/, -7/*��*/, 0, 0, 400 /*һ�����ֵ��Ϊ400*/,
            FALSE/*б��?*/, FALSE/*�»���?*/, FALSE/*ɾ����?*/, DEFAULT_CHARSET,
            OUT_CHARACTER_PRECIS, CLIP_CHARACTER_PRECIS, DEFAULT_QUALITY,
            FF_DONTCARE, TEXT("΢���ź�")
        );
        //������̬�ı���ؼ�--�û���
        // hInstance ��������Ϊ NULL��������ò�������
        hLabUsername = CreateWindow(TEXT("static"), TEXT("�û�����"),
            WS_CHILD | WS_VISIBLE | SS_CENTERIMAGE /*��ֱ����*/ | SS_RIGHT /*ˮƽ����*/,
            0 /*x����*/, 20 /*y����*/, 70 /*���*/, 26 /*�߶�*/,
            hWnd /*�����ھ��*/, (HMENU)1 /*�ؼ�ID*/, NULL /*��ǰ����ʵ�����*/, NULL
        );
        //������̬�ı���ؼ�--����
        hLabPassword = CreateWindow(TEXT("static"), TEXT("���룺"),
            WS_CHILD | WS_VISIBLE | SS_CENTERIMAGE /*��ֱ����*/ | SS_RIGHT /*ˮƽ����*/,
            0, 56, 70, 26,
            hWnd, (HMENU)2, NULL, NULL
        );
        //���������ı���ؼ�
        hEditUsername = CreateWindow(TEXT("edit"), TEXT(""),
            WS_CHILD | WS_VISIBLE | WS_BORDER /*�߿�*/ | ES_AUTOHSCROLL /*ˮƽ����*/,
            80, 20, 200, 26,
            hWnd, (HMENU)3, NULL, NULL
        );
        //�������������
        hEditPassword = CreateWindow(TEXT("edit"), TEXT(""),
            WS_CHILD | WS_VISIBLE | WS_BORDER | ES_PASSWORD /*����*/ |
            ES_AUTOHSCROLL /*ˮƽ����*/,
            80, 56, 200, 26,
            hWnd, (HMENU)4, NULL, NULL
        );
        //������ť�ؼ�
        hBtnLogin = CreateWindow(TEXT("button"), TEXT("��¼"),
            WS_CHILD | WS_VISIBLE | WS_BORDER | BS_FLAT/*��ƽ��ʽ*/,
            80, 92, 200, 30,
            hWnd, (HMENU)5, NULL, NULL
        );
        //�������ÿؼ�������
        SendMessage(hLabUsername, WM_SETFONT, (WPARAM)hFont, NULL);
        SendMessage(hLabPassword, WM_SETFONT, (WPARAM)hFont, NULL);
        SendMessage(hEditUsername, WM_SETFONT, (WPARAM)hFont, NULL);
        SendMessage(hEditPassword, WM_SETFONT, (WPARAM)hFont, NULL);
        SendMessage(hBtnLogin, WM_SETFONT, (WPARAM)hFont, NULL);
        break;
    case WM_COMMAND:
        wmId = LOWORD(wParam);
        wmEvent = HIWORD(wParam);
        switch (wmId) {
        case 5:  //��ť��HMENU����
            //��ȡ����������
            GetWindowText(hEditUsername, szUsername, 100);
            GetWindowText(hEditPassword, szPassword, 100);
            wsprintf(szUserInfo, TEXT("C������������ʾ��\r\n�����û��˺ţ�%s\r\n�����û����룺%s"), szUsername, szPassword);
            MessageBox(hWnd, szUserInfo, TEXT("��Ϣ��ʾ"), MB_ICONINFORMATION);
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
 * ��ں���
 *
 * @param hInstance
 * @param hPrevInstance
 * @param szCmdLine
 * @param iCmdShow
 * @return
 */
int WINAPI WinMain(
    HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    PSTR szCmdLine,
    int iCmdShow
) {
    static TCHAR szClassName[] = TEXT("HelloWin");  //��������
    HWND hwnd;  //���ھ��
    MSG msg;  //��Ϣ
    WNDCLASS wndclass;  //������

    /**********�ڢٲ���ע�ᴰ����**********/
    //Ϊ������ĸ����ֶθ�ֵ
    wndclass.style = CS_HREDRAW | CS_VREDRAW;  //���ڷ��
    wndclass.lpfnWndProc = InputPINCodeProc;  //���ڹ���
    wndclass.cbClsExtra = 0;  //��ʱ����Ҫ���
    wndclass.cbWndExtra = 0;  //��ʱ����Ҫ���
    wndclass.hInstance = NULL;  //��ǰ���ھ��
    wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);  //����ͼ��
    wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);  //�����ʽ
    wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);  //���ڱ�����ˢ
    wndclass.lpszMenuName = NULL;  //���ڲ˵�
    wndclass.lpszClassName = szClassName;  //��������

    //ע�ᴰ��
    RegisterClass(&wndclass);

    /*****�ڢڲ�����������(���ô�����ʾ����)*****/
    hwnd = CreateWindow(
        szClassName,  //�����������
        TEXT("������ PIN ��"),  //���ڱ��⣨�����ڱ�������
        WS_OVERLAPPEDWINDOW,  //���ڷ��
        CW_USEDEFAULT,  //��ʼ��ʱx���λ��
        CW_USEDEFAULT,  //��ʼ��ʱy���λ��
        350,  //���ڿ��
        200,  //���ڸ߶�
        NULL,  //�����ھ��
        NULL,  //���ڲ˵����
        hInstance,  //��ǰ���ڵľ��
        NULL  //��ʹ�ø�ֵ
    );

    //��ʾ����
    ShowWindow(hwnd, iCmdShow);
    //���£����ƣ�����
    UpdateWindow(hwnd);

    /**********�ڢ۲�����Ϣѭ��**********/
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);  //������Ϣ
        DispatchMessage(&msg);  //������Ϣ
    }

    return msg.wParam;
}