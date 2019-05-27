#include <Windows.h>
#include <list>
#include <tchar.h>
#include <string>
using namespace std;

void SetRandomPixel(HDC hDC , UINT iBeginX , UINT iBeginY , UINT iEndX , UINT iEndY) 
{
	COLORREF value;

	for (UINT i = iBeginX; i < iEndX; i++)
	{
		for (UINT j = iBeginY; j < iEndY; j++)
		{
			value = RGB(rand() % 256, rand() % 256, rand() % 256);

			SetPixel(hDC , i , j , value);
		}
	}
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{



	static HDC hDC;
	PAINTSTRUCT ps = { };
	RECT rc = {};
	switch (iMsg)
	{
	case WM_PAINT:
		hDC = BeginPaint(hWnd, &ps);
		SetRandomPixel(hDC , ps.rcPaint.left, ps.rcPaint.top, ps.rcPaint.right, ps.rcPaint.bottom);
		EndPaint(hWnd , &ps);
		break;
	case WM_DESTROY:

		PostQuitMessage(0);
		break;
	case WM_MOUSEMOVE:
		rc.left = LOWORD(lParam) - 10;
		rc.top = HIWORD(lParam) - 10;
		rc.right = rc.left + 20;
		rc.bottom = rc.top + 20;

		InvalidateRect(hWnd , &rc , false);
	}

	return DefWindowProc(hWnd, iMsg, wParam, lParam);
}


INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR lpszCmdParam, int nCmdShow)
{

	HWND hWnd;
	WNDCLASS wc;
	MSG msg;

	wc.style = CS_OWNDC;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(NULL, IDC_ICON);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = CreateSolidBrush(RGB(255, 255, 255));
	wc.lpszMenuName = NULL;
	wc.lpszClassName = TEXT("MyApp");

	RegisterClass(&wc);

	hWnd = CreateWindow(TEXT("MyApp"), TEXT("³ªÀÇ Ã¢"), WS_OVERLAPPEDWINDOW, 500, 200, 400, 300, NULL, NULL, hInstance, NULL);

	ShowWindow(hWnd, SW_SHOW);

	while (GetMessage(&msg, NULL, NULL, NULL))
	{

		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return 0;
}
