#include <Windows.h>
#include <list>
#include <tchar.h>
#include <string>
#include <iostream>
#include <math.h>
#include <ctime>
using namespace std;

int windowW = 800;
int windowH = 800;
int counttime = 0;
int mouseX = windowW / 2;
int screenX = GetSystemMetrics(SM_CXFULLSCREEN);
int screenY = GetSystemMetrics(SM_CYFULLSCREEN);
float PI = 3.14159265359;
float centerx = 0;
float centery = 0;
float centerz = 3;
int angle = 0;
class Vertex
{
public:
	float x;
	float y;
	float z;
};

Vertex point[] =
{
	{ centerx - 0.5 ,centery - 0.5 ,centerz - 0.5 },
	{ centerx + 0.5, centery - 0.5, centerz - 0.5 },
	{ centerx + 0.5 ,centery + 0.5 ,centerz - 0.5 },
	{ centerx - 0.5, centery + 0.5, centerz - 0.5 },
	{ centerx - 0.5 ,centery - 0.5 ,centerz + 0.5 },
	{ centerx + 0.5, centery - 0.5, centerz + 0.5 },
	{ centerx + 0.5 ,centery + 0.5 ,centerz + 0.5 },
	{ centerx - 0.5, centery + 0.5, centerz + 0.5 }
};

HBITMAP hbmBuffer = nullptr;
HBITMAP hbmOldBuffer = nullptr;

HBRUSH hMyBrush = nullptr;
HBRUSH hOldBrush = nullptr;

HDC hDC = nullptr;
HDC hDCBuffer = nullptr;

HPEN hMyPen = nullptr;
HPEN hOldPen = nullptr;

HWND hWnd;

MSG msg;

RECT crt;

WNDCLASS wc;

void CreateBack(HBRUSH hmyb, HBRUSH hob, HDC hDC, HWND hWnd)
{
	hmyb = CreateSolidBrush(RGB(255, 255, 255));
	hob = reinterpret_cast<HBRUSH>(SelectObject(hDC, hmyb));
	Rectangle(hDC, 0, 0, windowW, windowH);
	SelectObject(hDC, hob);
	DeleteObject(hmyb);
	ReleaseDC(hWnd, hDC);
}
void CreateLine(HBRUSH hmyb, HBRUSH hob, HDC hDC, HWND hWnd, Vertex a, Vertex b)
{
	hmyb = CreateSolidBrush(RGB(0, 0, 0));
	hob = reinterpret_cast<HBRUSH>(SelectObject(hDC, hmyb));
	float ax;
	float ay;
	float bx;
	float by;
	if (a.z != 0)
	{
		ax = a.x / a.z;
		ay = a.y / a.z;
	}
	else
	{
		ax = 0;
		ay = 0;
	}
	if (b.z != 0)
	{
		bx = b.x / b.z;
		by = b.y / b.z;
	}
	else
	{
		bx = 0;
		by = 0;
	}

	ax = (ax + 1)*(windowW / 2);
	ay = (-ay + 1)*(windowH / 2);
	bx = (bx + 1)*(windowW / 2);
	by = (-by + 1)*(windowH / 2);
	if ((ax - bx)*(ax - bx) + (ay - by)*(ay - by) < windowH*windowH)
	{
		MoveToEx(hDC, ax, ay, nullptr);
		LineTo(hDC, bx, by);
	}
	SelectObject(hDC, hob);
	DeleteObject(hmyb);
	ReleaseDC(hWnd, hDC);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	switch (iMsg)
	{
	case WM_CREATE:
		//화면크기를 구해줌
		GetClientRect(hWnd, &crt);

		//0.01초주기로 타이머설정
		SetTimer(hWnd, 1, 10, NULL);
		SendMessage(hWnd, WM_TIMER, 1, 0);

		hDC = GetDC(hWnd);
		break;
	case WM_TIMER:
		counttime++;
	case WM_PAINT:

		//버퍼에 화면크기만큼 그릴수있게해줌
		hDCBuffer = CreateCompatibleDC(hDC);
		hbmBuffer = CreateCompatibleBitmap(hDC, crt.right, crt.bottom);
		hbmOldBuffer = (HBITMAP)SelectObject(hDCBuffer, hbmBuffer);

		////버퍼에 그림을 그려줌
		//배경 생성
		CreateBack(hMyBrush, hOldBrush, hDCBuffer, hWnd);
	
		//선을 그음
		CreateLine(hMyBrush, hOldBrush, hDCBuffer, hWnd ,point[0], point[1]);
		CreateLine(hMyBrush, hOldBrush, hDCBuffer, hWnd, point[1], point[2]);
		CreateLine(hMyBrush, hOldBrush, hDCBuffer, hWnd, point[2], point[3]);
		CreateLine(hMyBrush, hOldBrush, hDCBuffer, hWnd, point[3], point[0]);

		CreateLine(hMyBrush, hOldBrush, hDCBuffer, hWnd, point[3], point[0]);
		CreateLine(hMyBrush, hOldBrush, hDCBuffer, hWnd, point[0], point[4]);
		CreateLine(hMyBrush, hOldBrush, hDCBuffer, hWnd, point[4], point[7]);
		CreateLine(hMyBrush, hOldBrush, hDCBuffer, hWnd, point[7], point[3]);

		CreateLine(hMyBrush, hOldBrush, hDCBuffer, hWnd, point[0], point[1]);
		CreateLine(hMyBrush, hOldBrush, hDCBuffer, hWnd, point[1], point[5]);
		CreateLine(hMyBrush, hOldBrush, hDCBuffer, hWnd, point[5], point[4]);
		CreateLine(hMyBrush, hOldBrush, hDCBuffer, hWnd, point[4], point[0]);

		CreateLine(hMyBrush, hOldBrush, hDCBuffer, hWnd, point[2], point[1]);
		CreateLine(hMyBrush, hOldBrush, hDCBuffer, hWnd, point[1], point[5]);
		CreateLine(hMyBrush, hOldBrush, hDCBuffer, hWnd, point[5], point[6]);
		CreateLine(hMyBrush, hOldBrush, hDCBuffer, hWnd, point[6], point[2]);

		CreateLine(hMyBrush, hOldBrush, hDCBuffer, hWnd, point[3], point[2]);
		CreateLine(hMyBrush, hOldBrush, hDCBuffer, hWnd, point[2], point[6]);
		CreateLine(hMyBrush, hOldBrush, hDCBuffer, hWnd, point[6], point[7]);
		CreateLine(hMyBrush, hOldBrush, hDCBuffer, hWnd, point[7], point[3]);

		CreateLine(hMyBrush, hOldBrush, hDCBuffer, hWnd, point[4], point[5]);
		CreateLine(hMyBrush, hOldBrush, hDCBuffer, hWnd, point[5], point[6]);
		CreateLine(hMyBrush, hOldBrush, hDCBuffer, hWnd, point[6], point[7]);
		CreateLine(hMyBrush, hOldBrush, hDCBuffer, hWnd, point[7], point[4]);
		for (int i = 0; i<8; i++)
		{
			point[i].x += 0.001;
			point[i].y += 0.001;
			point[i].z += 0.001;
		}
		
		for (int i = 0; i<8; i++) 
		{
			point[i].y = point[i].y * cos(0.5 * PI / 180) - point[i].z * sin(0.5 * PI / 180);
			point[i].z = point[i].y * sin(0.5 * PI / 180) + point[i].z * cos(0.5 * PI / 180);
		}
		//버퍼에있는 그림을 화면에 그려줌
		BitBlt(hDC, 0, 0, crt.right, crt.bottom, hDCBuffer, 0, 0, SRCCOPY);

		//버퍼를 해체해줌
		DeleteObject(SelectObject(hDCBuffer, hbmOldBuffer));
		DeleteDC(hDCBuffer);
		ReleaseDC(hWnd, hDCBuffer);
		break;

	case WM_DESTROY:
		//창닫혔을때 프로세스종료
		PostQuitMessage(0);
		break;

	}

	return DefWindowProc(hWnd, iMsg, wParam, lParam);
}


INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR lpszCmdParam, int nCmdShow)
{
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

	hWnd = CreateWindow(TEXT("MyApp"), TEXT("3D Cube"), WS_OVERLAPPEDWINDOW, ((screenX - windowW) / 2), ((screenY - windowH) / 2), windowW, windowH, NULL, NULL, hInstance, NULL);

	ShowWindow(hWnd, SW_SHOW);

	while (GetMessage(&msg, NULL, NULL, NULL))
	{

		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return 0;
}
