#include <Windows.h>
#include <list>
#include <tchar.h>
#include <string>
#include <iostream>
#include <math.h>
#include <ctime>
using namespace std;

bool Block[10][5];

int speed = 5;
int windowW = 800;
int windowH = 500;
int blockw = (((windowW - 16) / 10));
int blockh = (((windowH) / 25));
int point = 0;
double ballx = windowW / 2;
double bally = 432;
double ballangle = 120;
int counttime = 0;
int mouseX = windowW/2;
int screenX = GetSystemMetrics(SM_CXFULLSCREEN);
int screenY = GetSystemMetrics(SM_CYFULLSCREEN);

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
void CreateBall(HBRUSH hmyb, HBRUSH hob, HDC hDC, double bx, double by, HWND hWnd)
{
	hmyb = CreateSolidBrush(RGB(0, 0, 0));
	hob = reinterpret_cast<HBRUSH>(SelectObject(hDC, hmyb));
	Ellipse(hDC, bx-8, by-8, bx+8, by+8);
	SelectObject(hDC, hob);
	DeleteObject(hmyb);
	ReleaseDC(hWnd, hDC);
}
void CreateBlock(HBRUSH hmyb, HBRUSH hob, HPEN hmyp, HPEN hop,HDC hDC, HWND hWnd)
{
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			if (Block[i][j])
			{
				hmyp = CreatePen(0, 1, RGB(255, 255, 255));
				hop = reinterpret_cast<HPEN>(SelectObject(hDC, hmyp));
				hmyb = CreateSolidBrush(RGB(0, 0, 0));
				hob = reinterpret_cast<HBRUSH>(SelectObject(hDC, hmyb));
				Rectangle(hDC,
					2 + (i * blockw),
					1 + (j * blockh),
					2 + ((i + 1) * blockw),
					1 + ((j + 1) * blockh)
				);
				SelectObject(hDC, hob);
				SelectObject(hDC, hop);
				DeleteObject(hmyb);
				DeleteObject(hmyp);
				ReleaseDC(hWnd, hDC);
			}
		}
	}
}
void CreateStick(HBRUSH hmyb, HBRUSH hob, HDC hDC, HWND hWnd)
{
	hmyb = CreateSolidBrush(RGB(0, 0, 0));
	hob = reinterpret_cast<HBRUSH>(SelectObject(hDC, hmyb));
	Rectangle(hDC, mouseX - 40, 440, mouseX + 40, 455);
	SelectObject(hDC, hob);
	DeleteObject(hmyb);
	ReleaseDC(hWnd, hDC);
}
void MoveBall(double angle) 
{
	if (point < 5) 
	{
		speed = 5;
	}else if (point <15)
	{
		speed = 6;
	}
	else if (point <25)
	{
		speed = 7;
	}
	else if (point <35)
	{
		speed = 9;
	}
	else if (point <45)
	{
		speed = 11;
	}
	else
	{
		speed = 14;
	}

	double radian = (angle * 3.1416 / 180);

	ballx += cos(radian)*speed;
	bally -= sin(radian)*speed;
	//�����ʺ��� ����
	if (ballx + 8>windowW-16)
	{
		ballangle = 180 - ballangle;
	}
	//���ʺ��� ����
	if (ballx - 8<0)
	{
		ballangle = 180 - ballangle;
	}
	//õ�忡 ����
	if (bally + 8<0)
	{
		ballangle = -ballangle;
	} 
	//���뿡 ����
		if (bally + 8 > windowH - 55 && bally + 8 < windowH - 40)
		{
			if (ballx + 8 > mouseX - 40 && ballx - 8 < mouseX + 40)
			{
				ballangle = -ballangle;
			}
		}

	
	//������ ����
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			if (Block[i][j])
			{
				if (bally + 8 > (1 + (j * blockh)) && bally - 8 <(1 + (j + 1) * blockh))
				{
					if (ballx + 8 > (2 + (i * blockw)) && ballx - 8 < (2 + (i + 1) * blockw))
					{
						if (radian > 0 && radian <= 90) 
						{
							if (ballx + 6 >(2 + (i * blockw)))
							{
								ballangle = -ballangle;
							}
							else 
							{
								ballangle = 180 - ballangle;
							}
							Block[i][j] = false;
							point++;
						}
						else if (radian > 90 && radian <= 180)
						{
							if (ballx -7 <(2 + (i + 1) * blockw))
							{
								ballangle = -ballangle;
							}
							else
							{
								ballangle = 180 - ballangle;
							}
							Block[i][j] = false;
							point++;
						}
						else if (radian > 180 && radian <= 270)
						{
							if (ballx - 7 <(2 + (i + 1) * blockw))
							{
								ballangle = -ballangle;
							}
							else
							{
								ballangle = 180 - ballangle;
							}
							Block[i][j] = false;
							point++;
						}
						else
						{
							if (ballx + 7 >(2 + (i * blockw)))
							{
								ballangle = -ballangle;
							}
							else
							{
								ballangle = 180 - ballangle;

							}
							Block[i][j] = false;
							point++;
						}
					}
				}
			}
		}
	}
}
LRESULT CALLBACK WndProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	switch (iMsg)
	{
	case WM_CREATE:
		
		srand((unsigned int)time(NULL));
		ballangle = (rand() % 90) + 45;
		while (ballangle == 90)
		{
			srand((unsigned int)time(NULL));
			ballangle = (rand() % 90) + 45;
		}


		//ȭ��ũ�⸦ ������
		GetClientRect(hWnd, &crt);

		//����� �ʱⰪ����
		for (int i = 0; i < 10; i++)
		{
			for (int j = 0; j < 5; j++)
			{
				Block[i][j] = true;
			}
		}
		//0.01���ֱ�� Ÿ�̸Ӽ���
		SetTimer(hWnd, 1, 10, NULL);
		SendMessage(hWnd, WM_TIMER, 1, 0);

		hDC = GetDC(hWnd);
		break;
	case WM_TIMER:
		counttime++;
	case WM_PAINT:

		//���ۿ� ȭ��ũ�⸸ŭ �׸����ְ�����
		hDCBuffer = CreateCompatibleDC(hDC);
		hbmBuffer = CreateCompatibleBitmap(hDC, crt.right, crt.bottom);
		hbmOldBuffer = (HBITMAP)SelectObject(hDCBuffer, hbmBuffer);

		////���ۿ� �׸��� �׷���
		//��� ����
		CreateBack(hMyBrush, hOldBrush, hDCBuffer, hWnd);

		//���� ����
		CreateStick(hMyBrush, hOldBrush, hDCBuffer, hWnd);

		//��� ����
		CreateBlock(hMyBrush, hOldBrush, hMyPen, hOldPen, hDCBuffer, hWnd);
		
		//�� ����
		CreateBall(hMyBrush, hOldBrush, hDCBuffer , ballx , bally, hWnd);

		//�� �̵�
		MoveBall(ballangle);

		//���ۿ��ִ� �׸��� ȭ�鿡 �׷���
		BitBlt(hDC, 0, 0, crt.right, crt.bottom, hDCBuffer, 0, 0, SRCCOPY);

		//���۸� ��ü����
		DeleteObject(SelectObject(hDCBuffer, hbmOldBuffer));
		DeleteDC(hDCBuffer);
		ReleaseDC(hWnd, hDCBuffer);
		break;
	case WM_GETMINMAXINFO:
		//âũ�� ����
		((MINMAXINFO *)lParam)->ptMaxTrackSize.x = 800;
		((MINMAXINFO *)lParam)->ptMinTrackSize.x = 800;
		((MINMAXINFO *)lParam)->ptMaxTrackSize.y = 500;
		((MINMAXINFO *)lParam)->ptMinTrackSize.y = 500;
		break;
	case WM_DESTROY:
		//â�������� ���μ�������
		PostQuitMessage(0);
		break;
	case WM_MOUSEMOVE:
		//���콺�� x��ǥ�� �����
		mouseX = LOWORD(lParam);
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

	hWnd = CreateWindow(TEXT("MyApp"), TEXT("��������"), WS_OVERLAPPEDWINDOW, ((screenX - windowW) / 2), ((screenY - windowH) / 2), windowW, windowH, NULL, NULL, hInstance, NULL);

	ShowWindow(hWnd, SW_SHOW);

	while (GetMessage(&msg, NULL, NULL, NULL))
	{

		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return 0;
}
