#include "Draw.h"

void CreateRect(HBRUSH hmyb, HBRUSH hob, HDC hDC, HWND hWnd, COLORREF color, int x, int y, int width, int height)
{
	hmyb = CreateSolidBrush(color);
	hob = reinterpret_cast<HBRUSH>(SelectObject(hDC, hmyb));
	Rectangle(hDC, x, y, x + width, y + height);
	SelectObject(hDC, hob);
	DeleteObject(hmyb);
	ReleaseDC(hWnd, hDC);
}

void CreateRect(HBRUSH hmyb, HBRUSH hob, HDC hDC, HWND hWnd, int x, int y, int width, int height)
{
	CreateRect(hmyb, hob, hDC, hWnd, RGB(255, 255, 255), x, y, width, height);
}

void CreateText(HBRUSH hmyb, HBRUSH hob, HDC hDC, HWND hWnd, COLORREF color, int x, int y, LPCWSTR str)
{
	hmyb = CreateSolidBrush(color);
	hob = reinterpret_cast<HBRUSH>(SelectObject(hDC, hmyb));
	TextOut(hDC, x, y, str, lstrlen(str));
	SelectObject(hDC, hob);
	DeleteObject(hmyb);
	ReleaseDC(hWnd, hDC);
}

void CreateText(HBRUSH hmyb, HBRUSH hob, HDC hDC, HWND hWnd, int x, int y, LPCWSTR str)
{
	CreateText(hmyb, hob, hDC, hWnd, RGB(0, 0, 0), x, y, str);
}

void DrawBitmap(HDC hdc, int x, int y, HBITMAP hBit)
{
	HDC MemDC;
	HBITMAP OldBitmap;
	int bx, by;
	BITMAP bit;

	MemDC = CreateCompatibleDC(hdc);
	OldBitmap = (HBITMAP)SelectObject(MemDC, hBit);

	GetObject(hBit, sizeof(BITMAP), &bit);
	bx = bit.bmWidth;
	by = bit.bmHeight;

	BitBlt(hdc, x, y, bx, by, MemDC, 0, 0, SRCCOPY);

	SelectObject(MemDC, OldBitmap);
	DeleteDC(MemDC);
}