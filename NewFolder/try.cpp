#include <windows.h>  // 包含Windows API头文件，提供创建窗口所需的所有函数、结构和常量

/*
 * 窗口过程函数 - 这是窗口的"大脑"，负责处理所有发送到窗口的消息
 * 参数说明：
 *   hwnd   : 接收消息的窗口句柄（窗口的唯一标识符）
 *   uMsg   : 消息类型（如鼠标点击、键盘输入、窗口绘制等）
 *   wParam : 消息的附加信息（具体含义取决于消息类型）
 *   lParam : 消息的附加信息（具体含义取决于消息类型）
 * 返回值：消息处理的结果
 */
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    // 根据不同的消息类型进行分支处理
    switch (uMsg) {
    case WM_DESTROY:
        // 当窗口被销毁时（用户点击关闭按钮），发送退出消息
        PostQuitMessage(0);  // 参数0是程序的退出代码
        return 0;            // 返回0表示消息已处理

    case WM_PAINT:
    {
        // WM_PAINT消息：当窗口需要重绘时调用（如窗口首次显示、从最小化恢复、被其他窗口遮挡后重新显示等）
        PAINTSTRUCT ps;  // 绘图结构体，包含绘图区域等信息

        // 开始绘图，获取设备上下文（Device Context，相当于画布）
        HDC hdc = BeginPaint(hwnd, &ps);

        // 在窗口上绘制文本
        // 参数：设备上下文, x坐标, y坐标, 要显示的文本, 文本长度
        TextOutW(hdc, 50, 50, L"Hello, Win32!", 13);

        // 结束绘图，释放设备上下文资源
        EndPaint(hwnd, &ps);
    }
    return 0;  // 返回0表示消息已处理
    }

    // 对于其他未特殊处理的消息，交给Windows默认的窗口过程处理
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

/*
 * Windows程序的入口函数，相当于控制台程序的main函数
 * 参数说明：
 *   hInstance      : 当前应用程序的实例句柄（标识符）
 *   hPrevInstance  : 前一个应用程序实例句柄（在32位及以后系统中总是NULL）
 *   lpCmdLine      : 命令行参数字符串
 *   nCmdShow       : 窗口的显示方式（最大化、最小化、正常显示等）
 * 返回值：程序退出代码
 */
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    // 定义窗口类的名称（必须是唯一的，用于标识这个窗口类）
    const wchar_t CLASS_NAME[] = L"MyWindowClass";

    // 定义并初始化窗口类结构体WNDCLASSEXW
    // WNDCLASSEXW是"窗口类扩展"结构体，包含窗口的各种属性
    WNDCLASSEXW wc = {};  // 使用{}将所有成员初始化为0

    wc.cbSize = sizeof(WNDCLASSEXW);        // 结构体大小（必须设置）
    wc.lpfnWndProc = WindowProc;            // 设置窗口过程函数指针
    wc.hInstance = hInstance;               // 设置应用程序实例句柄
    wc.lpszClassName = CLASS_NAME;          // 设置窗口类名称
    wc.hCursor = LoadCursor(NULL, IDC_ARROW); // 加载标准箭头光标
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);  // 设置窗口背景颜色为标准窗口颜色

    // 注册窗口类 - 告诉操作系统这个窗口类的信息
    // 注册成功后，就可以用这个类名来创建窗口了
    if (!RegisterClassExW(&wc)) {
        // 如果注册失败，显示错误消息框并退出程序
        MessageBoxW(NULL, L"注册窗口类失败", L"错误", MB_ICONERROR);
        return 0;
    }

    /*
     * 创建窗口实例
     * 参数说明：
     *   0                   : 扩展窗口样式（无特殊样式）
     *   CLASS_NAME          : 窗口类名称（必须已注册）
     *   L"Win32 API 窗口示例": 窗口标题栏显示的文本
     *   WS_OVERLAPPEDWINDOW : 窗口样式（标准的重叠式窗口，包含标题栏、边框、最小化最大化按钮等）
     *   CW_USEDEFAULT       : 窗口的x坐标（使用默认值）
     *   CW_USEDEFAULT       : 窗口的y坐标（使用默认值）
     *   800                 : 窗口宽度
     *   600                 : 窗口高度
     *   NULL                : 父窗口句柄（无父窗口）
     *   NULL                : 菜单句柄（无菜单）
     *   hInstance           : 应用程序实例句柄
     *   NULL                : 创建参数（无额外参数）
     */
    HWND hwnd = CreateWindowExW(
        0,
        CLASS_NAME,
        L"Win32 API 窗口示例",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 800, 600,
        NULL, NULL, hInstance, NULL
    );

    // 检查窗口是否创建成功
    if (hwnd == NULL) {
        MessageBoxW(NULL, L"创建窗口失败", L"错误", MB_ICONERROR);
        return 0;
    }

    // 显示窗口
    ShowWindow(hwnd, SW_SHOWNORMAL);  // 以正常方式显示窗口
    UpdateWindow(hwnd);               // 强制窗口立即重绘，发送WM_PAINT消息

    /*
     * 消息循环 - 程序的核心部分，不断处理发送到窗口的消息
     * 这是Windows程序的事件驱动架构的核心
     */
    MSG msg = {};  // 消息结构体，用于存储从消息队列中获取的消息

    // GetMessage函数：从消息队列中获取消息
    // 参数：消息结构体, 窗口句柄(NULL表示所有窗口), 消息过滤最小值, 消息过滤最大值
    // 返回值：当获取到WM_QUIT消息时返回0，循环结束
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);  // 翻译键盘消息，将按键消息转换为字符消息
        DispatchMessage(&msg);   // 将消息分发给对应的窗口过程函数（WindowProc）
    }

    // 程序结束，返回退出代码（来自WM_QUIT消息的wParam参数）
    return (int)msg.wParam;
}