#include <windows.h>  // ����Windows APIͷ�ļ����ṩ����������������к������ṹ�ͳ���

/*
 * ���ڹ��̺��� - ���Ǵ��ڵ�"����"�����������з��͵����ڵ���Ϣ
 * ����˵����
 *   hwnd   : ������Ϣ�Ĵ��ھ�������ڵ�Ψһ��ʶ����
 *   uMsg   : ��Ϣ���ͣ�����������������롢���ڻ��Ƶȣ�
 *   wParam : ��Ϣ�ĸ�����Ϣ�����庬��ȡ������Ϣ���ͣ�
 *   lParam : ��Ϣ�ĸ�����Ϣ�����庬��ȡ������Ϣ���ͣ�
 * ����ֵ����Ϣ����Ľ��
 */
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    // ���ݲ�ͬ����Ϣ���ͽ��з�֧����
    switch (uMsg) {
    case WM_DESTROY:
        // �����ڱ�����ʱ���û�����رհ�ť���������˳���Ϣ
        PostQuitMessage(0);  // ����0�ǳ�����˳�����
        return 0;            // ����0��ʾ��Ϣ�Ѵ���

    case WM_PAINT:
    {
        // WM_PAINT��Ϣ����������Ҫ�ػ�ʱ���ã��細���״���ʾ������С���ָ��������������ڵ���������ʾ�ȣ�
        PAINTSTRUCT ps;  // ��ͼ�ṹ�壬������ͼ�������Ϣ

        // ��ʼ��ͼ����ȡ�豸�����ģ�Device Context���൱�ڻ�����
        HDC hdc = BeginPaint(hwnd, &ps);

        // �ڴ����ϻ����ı�
        // �������豸������, x����, y����, Ҫ��ʾ���ı�, �ı�����
        TextOutW(hdc, 50, 50, L"Hello, Win32!", 13);

        // ������ͼ���ͷ��豸��������Դ
        EndPaint(hwnd, &ps);
    }
    return 0;  // ����0��ʾ��Ϣ�Ѵ���
    }

    // ��������δ���⴦�����Ϣ������WindowsĬ�ϵĴ��ڹ��̴���
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

/*
 * Windows�������ں������൱�ڿ���̨�����main����
 * ����˵����
 *   hInstance      : ��ǰӦ�ó����ʵ���������ʶ����
 *   hPrevInstance  : ǰһ��Ӧ�ó���ʵ���������32λ���Ժ�ϵͳ������NULL��
 *   lpCmdLine      : �����в����ַ���
 *   nCmdShow       : ���ڵ���ʾ��ʽ����󻯡���С����������ʾ�ȣ�
 * ����ֵ�������˳�����
 */
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    // ���崰��������ƣ�������Ψһ�ģ����ڱ�ʶ��������ࣩ
    const wchar_t CLASS_NAME[] = L"MyWindowClass";

    // ���岢��ʼ��������ṹ��WNDCLASSEXW
    // WNDCLASSEXW��"��������չ"�ṹ�壬�������ڵĸ�������
    WNDCLASSEXW wc = {};  // ʹ��{}�����г�Ա��ʼ��Ϊ0

    wc.cbSize = sizeof(WNDCLASSEXW);        // �ṹ���С���������ã�
    wc.lpfnWndProc = WindowProc;            // ���ô��ڹ��̺���ָ��
    wc.hInstance = hInstance;               // ����Ӧ�ó���ʵ�����
    wc.lpszClassName = CLASS_NAME;          // ���ô���������
    wc.hCursor = LoadCursor(NULL, IDC_ARROW); // ���ر�׼��ͷ���
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);  // ���ô��ڱ�����ɫΪ��׼������ɫ

    // ע�ᴰ���� - ���߲���ϵͳ������������Ϣ
    // ע��ɹ��󣬾Ϳ������������������������
    if (!RegisterClassExW(&wc)) {
        // ���ע��ʧ�ܣ���ʾ������Ϣ���˳�����
        MessageBoxW(NULL, L"ע�ᴰ����ʧ��", L"����", MB_ICONERROR);
        return 0;
    }

    /*
     * ��������ʵ��
     * ����˵����
     *   0                   : ��չ������ʽ����������ʽ��
     *   CLASS_NAME          : ���������ƣ�������ע�ᣩ
     *   L"Win32 API ����ʾ��": ���ڱ�������ʾ���ı�
     *   WS_OVERLAPPEDWINDOW : ������ʽ����׼���ص�ʽ���ڣ��������������߿���С����󻯰�ť�ȣ�
     *   CW_USEDEFAULT       : ���ڵ�x���꣨ʹ��Ĭ��ֵ��
     *   CW_USEDEFAULT       : ���ڵ�y���꣨ʹ��Ĭ��ֵ��
     *   800                 : ���ڿ��
     *   600                 : ���ڸ߶�
     *   NULL                : �����ھ�����޸����ڣ�
     *   NULL                : �˵�������޲˵���
     *   hInstance           : Ӧ�ó���ʵ�����
     *   NULL                : �����������޶��������
     */
    HWND hwnd = CreateWindowExW(
        0,
        CLASS_NAME,
        L"Win32 API ����ʾ��",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 800, 600,
        NULL, NULL, hInstance, NULL
    );

    // ��鴰���Ƿ񴴽��ɹ�
    if (hwnd == NULL) {
        MessageBoxW(NULL, L"��������ʧ��", L"����", MB_ICONERROR);
        return 0;
    }

    // ��ʾ����
    ShowWindow(hwnd, SW_SHOWNORMAL);  // ��������ʽ��ʾ����
    UpdateWindow(hwnd);               // ǿ�ƴ��������ػ棬����WM_PAINT��Ϣ

    /*
     * ��Ϣѭ�� - ����ĺ��Ĳ��֣����ϴ����͵����ڵ���Ϣ
     * ����Windows������¼������ܹ��ĺ���
     */
    MSG msg = {};  // ��Ϣ�ṹ�壬���ڴ洢����Ϣ�����л�ȡ����Ϣ

    // GetMessage����������Ϣ�����л�ȡ��Ϣ
    // ��������Ϣ�ṹ��, ���ھ��(NULL��ʾ���д���), ��Ϣ������Сֵ, ��Ϣ�������ֵ
    // ����ֵ������ȡ��WM_QUIT��Ϣʱ����0��ѭ������
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);  // ���������Ϣ����������Ϣת��Ϊ�ַ���Ϣ
        DispatchMessage(&msg);   // ����Ϣ�ַ�����Ӧ�Ĵ��ڹ��̺�����WindowProc��
    }

    // ��������������˳����루����WM_QUIT��Ϣ��wParam������
    return (int)msg.wParam;
}