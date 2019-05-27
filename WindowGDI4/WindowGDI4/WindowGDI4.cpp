#include <Windows.h>
#include <tchar.h>

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	switch (iMsg)
	{
	case WM_DESTROY:

		PostQuitMessage(0);
		break;
	case WM_LBUTTONDOWN:
		HDC hDC = nullptr;
		HPEN hMyPen = nullptr;
		HPEN hOldPen = nullptr;
		HBRUSH hMyBrush = nullptr;
		HBRUSH hOldBrush = nullptr;
		HFONT hMyFont = nullptr;
		HFONT hOldFont = nullptr;

		hDC = GetDC(hWnd);

		hMyPen = CreatePen(PS_DOT, 1, RGB(255, 0,0));
		hOldPen = reinterpret_cast<HPEN>(SelectObject(hDC, hMyPen));
		
		hMyBrush = reinterpret_cast<HBRUSH>(GetStockObject(NULL_BRUSH));
		hOldBrush = reinterpret_cast<HBRUSH>(SelectObject(hDC, hMyBrush));

		hMyFont = CreateFont(20, 0 ,0 ,0, FW_NORMAL,0,0,0, ANSI_CHARSET,0,0,0,0,TEXT("Consolas"));
		hOldFont = reinterpret_cast<HFONT>(SelectObject(hDC, hMyFont));

		Rectangle(hDC, 20, 20, 120, 120);

		TextOut(hDC, 10, 10, TEXT("기모띠"), 8);

		SelectObject(hDC, hOldPen);

		SelectObject(hDC, hOldBrush);
		DeleteObject(hMyBrush);

		SelectObject(hDC, hMyFont);
		DeleteObject(hMyFont);

		ReleaseDC(hWnd, hDC);

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
	wc.hbrBackground = CreateSolidBrush(RGB(0, 0, 0));
	wc.lpszMenuName = NULL;
	wc.lpszClassName = TEXT("MyApp");

	RegisterClass(&wc);

	hWnd = CreateWindow(TEXT("MyApp"), TEXT("나의 창"), WS_OVERLAPPEDWINDOW, 500, 200, 400, 300, NULL, NULL, hInstance, NULL);

	ShowWindow(hWnd, SW_SHOW);

	while (GetMessage(&msg, NULL, NULL, NULL))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return 0;
}
