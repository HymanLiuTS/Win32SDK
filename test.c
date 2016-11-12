#include "windows.h"
int APIENTRY wWinMain(_In_ HINSTANCE hInstance,  
                     _In_opt_ HINSTANCE hPrevInstance,  
                     _In_ LPWSTR    lpCmdLine,  
                     _In_ int       nCmdShow)   
{
  MessageBox(NULL,"Hello Win32","sdk",MB_ABORTRETRYIGNORE|MB_ICONERROR);
  return 0;
}