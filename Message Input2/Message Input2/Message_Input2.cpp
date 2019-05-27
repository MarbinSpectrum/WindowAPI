#include <Windows.h>
#include <list>
#include <tchar.h>
#include <string>
using namespace std;

HDC hDC;
int countx = 0;
int county = 0;
int counttime = 0;
LRESULT CALLBACK WndProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	static bool bMouseDown = false;
	static std::list<POINT> draw;
	switch (iMsg)
	{
	case WM_CREATE:
		SetTimer(hWnd, 1, 100, NULL);
		SendMessage(hWnd, WM_TIMER, 1, 0);
		break;
	case WM_TIMER:
		counttime++;
		hDC = GetDC(hWnd);
		TCHAR str[128];
		wsprintf(str, TEXT("%d"), counttime);

		TextOut(hDC, 10, 10, str, lstrlen(str));
		break;
	case WM_PAINT:
		hDC = GetDC(hWnd);
		
		if (draw.size() > 1) 
		{
			MoveToEx(hDC, draw.front().x, draw.front().y, nullptr);

			for (auto i = ++draw.begin(); i != draw.end(); i++) 
			{
				LineTo(hDC, i->x, i->y);
			}

			ReleaseDC(hWnd, hDC);
		}
		break;
	case WM_DESTROY:

		PostQuitMessage(0);
		break;
	case WM_LBUTTONDOWN:

		bMouseDown = true;

		draw.push_back(POINT{ LOWORD(lParam), HIWORD(lParam) });
		
		break;

	case WM_MOUSEMOVE:

		if (bMouseDown)
		{
			draw.push_back(POINT{ LOWORD(lParam), HIWORD(lParam) });

			InvalidateRect(hWnd , nullptr, false);
		}
		break;

	case WM_LBUTTONUP:
		bMouseDown = false;
		break;

	case  WM_CHAR:
		hDC = GetDC(hWnd);
		TCHAR key = 0;
		key = wParam;
		if (key == VK_RETURN)
		{
			countx = 0;
			county++;
		}
		else {
			TextOut(hDC, 10 + (15 * countx), 10 + (15 * county), &key, 1);
			ReleaseDC(hWnd, hDC);
			countx++;
		}
		break;
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
