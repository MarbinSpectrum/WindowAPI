#pragma once

#include "framework.h"
#include "resource.h"

class Vector2
{
public:
	int x;
	int y;
	Vector2(int ax, int ay);
	Vector2();
};

void CreateRect(HBRUSH hmyb, HBRUSH hob, HDC hDC, HWND hWnd, COLORREF color, int x, int y, int width, int height);
void CreateRect(HBRUSH hmyb, HBRUSH hob, HDC hDC, HWND hWnd, int x, int y, int width, int height);
void CreateText(HBRUSH hmyb, HBRUSH hob, HDC hDC, HWND hWnd, COLORREF color, int x, int y, LPCWSTR str);
void CreateText(HBRUSH hmyb, HBRUSH hob, HDC hDC, HWND hWnd, int x, int y, LPCWSTR str);
void DrawBitmap(HDC hdc, int x, int y, HBITMAP hBit);
void DrawBitmap(HDC hdc, int x, int y, int img_width, int img_height, int img_x, int img_y, HBITMAP hBit);
void DrawBitmap(HDC hdc, int x, int y, int img_width, int img_height, int img_x, int img_y, HBITMAP hBit, HBITMAP hBitMask);
void DrawBitmap(HDC hdc, int x, int y, int img_width, int img_height, int img_x, int img_y, HBITMAP hBit, HBITMAP hBitMask, bool flipX);
void DrawBitmap(HDC hdc, int x, int y, int img_width, int img_height, int img_x, int img_y, HBITMAP hBit, HBITMAP hBitMask, bool flipX, bool flipY);


class Draw
{
public:
	static HBITMAP character;
	static Vector2 characterRect;
	static HBITMAP characterMask;
};