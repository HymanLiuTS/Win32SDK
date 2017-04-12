// MessageTS.cpp : 定义应用程序的入口点。
//

#include "stdafx.h"
#include "stdio.h"
#include "MessageTS.h"

HANDLE hOutput;
HINSTANCE g_hInstance = 0;  
//窗口处理函数  
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)  
{  
	switch (uMsg)  
	{  
	case WM_DESTROY:  
		PostQuitMessage(0);//可以使GetMessage返回0  
		break; 
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
void Message(HWND hWnd)  
{  
	MSG nMsg = { 0 };
	while (GetMessage(&nMsg, hWnd, 0, 0))  
	{  
		TranslateMessage(&nMsg);  
		DispatchMessage(&nMsg);  

		if(nMsg.message == WM_PAINT)
		{
			char buff[30]={};
			sprintf(buff,"处理消息%d\n",nMsg.message);
			WriteConsole(hOutput,buff,sizeof(buff),NULL,NULL);
		}
	}  
}  

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,  
	_In_opt_ HINSTANCE hPrevInstance,  
	_In_ LPWSTR    lpCmdLine,  
	_In_ int       nCmdShow)  
{  
	AllocConsole();
	hOutput=GetStdHandle(STD_OUTPUT_HANDLE);
	g_hInstance = hInstance;  
	BOOL nRet = Register("Main", WndProc);  
	if (!nRet)  
	{  
		MessageBox(NULL, "注册失败", "Infor", MB_OK);  
		return 0;  
	}  
	HWND hWnd = CreateMain("Main", "window");  
	Display(hWnd);  
	Message(hWnd);  
	return 0;  
}  