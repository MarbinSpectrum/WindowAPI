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
		HBRUSH hMyBrush = nullptr;
		HBRUSH hOldBrush = nullptr;
		HPEN hOldPen = nullptr;
		HPEN hMyPen = nullptr;

		hDC = GetDC(hWnd);

		hMyBrush = CreateSolidBrush(RGB(255, 0, 0));
		hMyPen = CreatePen(PS_SOLID, 5, RGB(0, 255, 0));

		hOldBrush = reinterpret_cast<HBRUSH>(SelectObject(hDC, hMyBrush));
		hOldPen = reinterpret_cast<HPEN>(SelectObject(hDC, hMyPen));

		Rectangle(hDC, 10, 10, 110, 110);

		SelectObject(hDC , hOldBrush);
		SelectObject(hDC, hOldPen);

		DeleteObject(hMyBrush);
		DeleteObject(hMyPen);

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
	wc.hbrBackground = CreateSolidBrush(RGB(255, 255, 255));
	wc.lpszMenuName = NULL;
	wc.lpszClassName = TEXT("MyApp");

	RegisterClass(&wc);

	hWnd = CreateWindow(TEXT("MyApp"), TEXT("³ªÀÇ Ã¢"), WS_OVERLAPPEDWINDOW, 500, 200, 1000, 800, NULL, NULL, hInstance, NULL);

	ShowWindow(hWnd, SW_SHOW);

	while (GetMessage(&msg, NULL, NULL, NULL))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return 0;
}
