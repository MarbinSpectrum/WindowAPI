#include "Draw.h"

Vector2::Vector2(int ax, int ay)
{
	x = ax;
	y = ay;
};

Vector2::Vector2()
{
	x = 0;
	y = 0;
};

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
	BITMAP bit;
	GetObject(hBit, sizeof(BITMAP), &bit);
	DrawBitmap(hdc, x, y, bit.bmWidth, bit.bmHeight, x, y, hBit);
}

void DrawBitmap(HDC hdc, int x, int y, int img_width, int img_height, int img_x, int img_y, HBITMAP hBit)
{
	DrawBitmap(hdc, x, y, img_width, img_height, img_x, img_y, hBit, NULL);
}

void DrawBitmap(HDC hdc, int x, int y, int img_width, int img_height, int img_x, int img_y, HBITMAP hBit, HBITMAP hBitMask)
{
	DrawBitmap(hdc, x, y, img_width, img_height, img_x, img_y, hBit, hBitMask, false);
}

void DrawBitmap(HDC hdc, int x, int y, int img_width, int img_height, int img_x, int img_y, HBITMAP hBit, HBITMAP hBitMask, bool flipX)
{
	DrawBitmap(hdc, x, y, img_width, img_height, img_x, img_y, hBit, hBitMask, flipX, false);
}

void DrawBitmap(HDC hdc, int x, int y, int img_width, int img_height, int img_x, int img_y, HBITMAP hBit, HBITMAP hBitMask, bool flipX, bool flipY)
{
	HDC MemDC;
	HBITMAP OldBitmap;
	int bx, by;
	BITMAP bit;

	MemDC = CreateCompatibleDC(hdc);

	GetObject(hBit, sizeof(BITMAP), &bit);
	bx = bit.bmWidth;
	by = bit.bmHeight;

	if (hBitMask != NULL)
	{
		OldBitmap = (HBITMAP)SelectObject(MemDC, hBitMask);

		BitBlt(hdc, x, y, img_width, img_height, MemDC, img_x, img_y, SRCAND);
		SelectObject(MemDC, hBit);
		BitBlt(hdc, x, y, img_width, img_height, MemDC, img_x, img_y, SRCPAINT);
	}
	else
	{
		OldBitmap = (HBITMAP)SelectObject(MemDC, hBit);

		BitBlt(hdc, x, y, img_width, img_height, MemDC, img_x, img_y, SRCCOPY);

		StretchBlt(hdc, x, y, img_width, img_height, hdc, x, y, img_width, img_height, SRCCOPY);
	}


	StretchBlt(hdc, x, y, img_width, img_height, hdc, x + (flipX ? img_width : 0), y + (flipY ? img_height : 0), (flipX ? -img_width : +img_width), (flipX ? -img_height : +img_height), SRCCOPY);


	SelectObject(MemDC, OldBitmap);

	DeleteDC(MemDC);
}

HBITMAP Draw::character = nullptr;
HBITMAP Draw::characterMask = nullptr;
Vector2 Draw::characterRect(32, 40);

