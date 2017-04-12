HINSTANCE g_hInstance = 0;  
//窗口处理函数  
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)  
{  
	switch (uMsg)  
	{  
	case WM_DESTROY:  
		PostQuitMessage(0);//可以使GetMessage返回0  
		break; 
	case  WM_CREATE:
	{
		CREATESTRUCT crt = *((CREATESTRUCT*)lParam);
		char buf[256] = {0};
		sprintf(buf,"创建的窗口类名称是%s，窗口名称是%s",crt.lpszClass,crt.lpszName);
		MessageBox(NULL, buf, "消息处理", MB_OK);
	}
	case WM_QUIT:
	{
		int param = (int)wParam;
		char buf[256];
		sprintf(buf, "进程退出，退出码:%d", param);
		MessageBox(NULL, buf, "消息处理", MB_OK);
	}
	case WM_SYSCOMMAND:
	{
		if (wParam == SC_MAXIMIZE)
		{
			short x = LOWORD(lParam);
			short y = HIWORD(lParam);
			char buf[256];
			sprintf(buf, "窗口最大化，x坐标:%d，y坐标:%d", x,y);
			MessageBox(NULL, buf, "消息处理", MB_OK);
		}
	}
	case WM_SIZE:
	{
		if (wParam == SIZE_MAXIMIZED)
		{
			short width = LOWORD(lParam);
			short hight = HIWORD(lParam);
			char buf[256];
			sprintf(buf, "窗口最大化，高度:%d，宽度:%d", hight, width);
			MessageBox(NULL, buf, "消息处理", MB_OK);
		}
	}
	default:  
		break;  
	}  
	return DefWindowProc(hWnd, uMsg, wParam, lParam);  
}  
//注册窗口类  
BOOL Register(LPSTR lpClassName, WNDPROC wndProc)  
{  
	WNDCLASSEX wce = { 0 };  
	wce.cbSize = sizeof(wce);  
	wce.cbClsExtra = 0;  
	wce.cbWndExtra = 0;  
	wce.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);  
	wce.hCursor = NULL;  
	wce.hIcon = NULL;  
	wce.hIconSm = NULL;  
	wce.hInstance = g_hInstance;  
	wce.lpfnWndProc = wndProc;  
	wce.lpszClassName = lpClassName;  
	wce.lpszMenuName = NULL;  
	wce.style = CS_HREDRAW | CS_VREDRAW;  
	ATOM nAtom = RegisterClassEx(&wce);  
	if (nAtom == 0)  
		return FALSE;  
	return true;  

}  
//创建主窗口  
HWND CreateMain(LPSTR lpClassName, LPSTR lpWndName)  
{  
	HWND hWnd = CreateWindowEx(0, lpClassName, lpWndName,  
		WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, g_hInstance, NULL);  
	return hWnd;  
}  
//显示窗口  
void Display(HWND hWnd)  
{  
	ShowWindow(hWnd, SW_SHOW);  
	UpdateWindow(hWnd);  
}  
//消息循环  
void Message()  
{  
	MSG nMsg = { 0 };  
	while (GetMessage(&nMsg, NULL, 0, 0))  
	{  
		TranslateMessage(&nMsg);  
		DispatchMessage(&nMsg);  
	}  
}  
int APIENTRY wWinMain(_In_ HINSTANCE hInstance,  
	_In_opt_ HINSTANCE hPrevInstance,  
	_In_ LPWSTR    lpCmdLine,  
	_In_ int       nCmdShow)  
{  
	// TODO: Place code here.  

	g_hInstance = hInstance;  
	BOOL nRet = Register("Main", WndProc);  
	if (!nRet)  
	{  
		MessageBox(NULL, "注册失败", "Infor", MB_OK);  
		return 0;  
	}  
	HWND hWnd = CreateMain("Main", "window");  
	Display(hWnd);  
	Message();  
	return 0;  
}  