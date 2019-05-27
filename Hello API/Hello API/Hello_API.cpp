#include <Windows.h>
#include <tchar.h>

INT APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE, TCHAR *pszLine, int nShow)
{
	MessageBox(NULL, TEXT("Hello World!"), TEXT("Title"), MB_OK);

	return 0;
}
