#pragma once

#include "framework.h"
#include "resource.h"

void CreateRect(HBRUSH hmyb, HBRUSH hob, HDC hDC, HWND hWnd, COLORREF color, int x, int y, int width, int height);
void CreateRect(HBRUSH hmyb, HBRUSH hob, HDC hDC, HWND hWnd, int x, int y, int width, int height);
void CreateText(HBRUSH hmyb, HBRUSH hob, HDC hDC, HWND hWnd, COLORREF color, int x, int y, LPCWSTR str);
void CreateText(HBRUSH hmyb, HBRUSH hob, HDC hDC, HWND hWnd, int x, int y, LPCWSTR str);
void DrawBitmap(HDC hdc, int x, int y, HBITMAP hBit);