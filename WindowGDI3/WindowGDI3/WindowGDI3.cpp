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

		hDC = GetDC(hWnd);
		for (int i = 0; i < 6; i++) {
			hMyBrush = CreateHatchBrush(i, RGB(0, 0, 0));

			hOldBrush = reinterpret_cast<HBRUSH>(SelectObject(hDC, hMyBrush));

			Rectangle(hDC, 20 + ((i % 3) * 120), 20 + ((i / 3) * 120), 120 + ((i % 3) * 120), 120 + ((i / 3) * 120));

			SelectObject(hDC, hOldBrush);

			DeleteObject(hMyBrush);
		}
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

	hWnd = CreateWindow(TEXT("MyApp"), TEXT("³ªÀÇ Ã¢"), WS_OVERLAPPEDWINDOW, 500, 200, 400, 300, NULL, NULL, hInstance, NULL);

	ShowWindow(hWnd, SW_SHOW);

	while (GetMessage(&msg, NULL, NULL, NULL))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return 0;
}
