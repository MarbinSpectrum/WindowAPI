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

		hDC = GetDC(hWnd);

		Rectangle(hDC, 10, 10, 110, 110);

		Ellipse(hDC, 10, 10, 110, 110);

		TextOut(hDC, 10, 10, TEXT("Text"), 4);

		MoveToEx(hDC, 10, 10, nullptr);
		LineTo(hDC, 110, 110);
		LineTo(hDC, 10, 210);
		LineTo(hDC, 110, 310);

		ReleaseDC(hWnd, hDC);

		MoveToEx(hDC, 310, 10, nullptr);
		LineTo(hDC, 310, 110);
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
	wc.hbrBackground = CreateSolidBrush(RGB(255,255,255));
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
