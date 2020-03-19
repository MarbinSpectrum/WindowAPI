﻿#include "framework.h"
#include "API_RPG.h"
#include "SceneManager.h"
#include "ObjectManager.h"
#include "Draw.h"
#include "Resource.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////																																																	////
////                 :::       :::	   :::::::::::	   ::::    :::		:::::::::		 ::::::::	   :::		:::					    :::			:::::::::	  :::::::::::							////
////                 :+:	   :+:	       :+:		   :+:+:   :+:		:+:	   :+:		:+:	   :+:	   :+:	    :+:					  :+: :+:		:+:    :+:	      :+:								////
////                 +:+       +:+	 	   +:+		   :+:+:+  +:+		+:+    +:+		+:+    +:+	   +:+		+:+					 +:+   +:+		+:+	   +:+		  +:+								////
////                 +#+  +:+  +#+	 	   +#+		   +#+ +:+ +#+		+#+	   +:+		+#+	   +:+	   +#+  +:+  +#+				+#++:++#++:		+#++:++#+		  +#+								////
////                 +#+ ++#++ +#+	 	   +#+		   +#+  +#+#+#		+#+	   #+#		+#+    +#+	   +#+ +#+#+ +#+				+#+		+#+		+#+				  +#+								////
////                  #+#+# #+#+#		   #+#		   #+#   #+#+#		#+#    #+#		#+#    #+#	    #+#+# #+#+#					#+#     #+#		#+#				  #+#								////
////                   ###   ###	   ###########	   ###    ####		#########		 ########		 ###   ###					###     ###		###			  ###########							////
////																																																	////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Vector2 window = Vector2(1200, 660);

HBITMAP hbmBuffer = nullptr;
HBITMAP hbmOldBuffer = nullptr;

HDC hDC = nullptr;
HDC hDCBuffer = nullptr;

HBRUSH hMyBrush = nullptr;
HBRUSH hOldBrush = nullptr;

RECT crt;

HINSTANCE hINSTANCE;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int time = 0;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

LRESULT WindowProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int APIENTRY WinMain
(
	HINSTANCE hInst,	// 생성한 윈도우의 식별자값
	HINSTANCE hPrev,	// 16비트에서 사용되었던 값 ( 지금은 사용되지않음 )
	LPSTR params,		// 전달될 문자열 값
	int nCmdShow		// 보여주는 방식
)
{
	// 1. 출력할 윈도우에 대한 기본 정보를 선언 및 등록한다.
	// 2. 실질적인 윈도우를 생성한다.
	// 3. 윈도우를 갱신하고, 보여줄 수 있도록 설정한다.
	// 4. 종료 메세지가 발생되기 전까지 윈도우를 순회한다. ( 메세지 루프 )

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	hINSTANCE = hInst;

	WNDCLASS wndClass;

	//cbClsExtra 와 cbWndExtra는 현재 사용되지 않는 부분임 0으로 처리
	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);	// 배경을 지정한 색으로 만듬(WHITE_BRUSH을 선택했기 때문에 하얀색 배경이 됨)
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);					// 커서를 등록함 LoadCursor를 통해 IDC_ARROW에 해당하는 커서를 불러옴
	wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);				// 아이콘를 등록함 LoadIcon을 통해 IDI_APPLICATION에 해당하는 아이콘을 불러옴
	wndClass.hInstance = hInst;										// 윈도우 식별자를 등록함 (생성한 식별자값을 넣어줫음)
	wndClass.lpfnWndProc = (WNDPROC)WindowProc;						// 윈도우의 메시지를 처리하는 함수를 등록 (메세지가 발생할때마다 여기서 등록된 함수가 메세지를 처리함)
	wndClass.lpszClassName = TEXT("Test");						    // 윈도우 클래스 이름을 등록
	wndClass.lpszMenuName = NULL;									// 사용할 메뉴를 지정함 (사용하지 않을것이기에 NULL 처리)
	wndClass.style = CS_HREDRAW | CS_VREDRAW;						// 윈도우의 스타일을 정의한다 (CS_HREDRAW : 수평으로 변하면 윈도우를 다시 그림 , CS_VREDRAW : 수직으로 변하면 윈도우를 다시 그림)
	RegisterClass(&wndClass);										// 정의한 wndClass를 등록함

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	HWND hWnd = CreateWindow
	(
		TEXT("Test"),								// 윈도우 클래스 이름을 검색해서 찾음
		TEXT("API"),								// 타이틀 이름을 의미
		WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU,	// 생성할 윈도우의 스타일을 지정 (예 >> WS_MINIMIZEBOX : 최소화 버튼을 만듬 , WS_OVERLAPPEDWINDOW : 가장 일반적인 윈도우 스타일)(현재 기본스타일에서 최소화 버튼을 뺌)
		(GetSystemMetrics(SM_CXFULLSCREEN) - window.x) / 2, (GetSystemMetrics(SM_CYFULLSCREEN) - window.y) / 2,	// 윈도우가 생성되는 x,y 좌표
		window.x, window.y,																						// 윈도우의 width , height 크기
		NULL,										// 부모 윈도우에 대한 정보를 지정(부모 윈도우가 없어서 NULL 처리)
		NULL,										// 메뉴를 지정함 (지금은 없는것으로 처리 NULL)
		hInst,										// 해당윈도우를 생성하는 윈도우 식별자 값을 입력해줌
		0
	);

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	UpdateWindow(hWnd);							// 윈도우를 업데이트 해줌
	ShowWindow(hWnd, nCmdShow);					// 윈도우를 보여줌

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	MSG msg;
	GetMessage(&msg, hWnd, 0, 0);
	// 윈도우는 메시지를 큐 방식을 사용 -> 발생된 메세지 순서대로 처리가 됨
	while (msg.message != WM_QUIT)		// GetMessage는 하나의 메시지를 받아오는 기능을함!! 메시지 큐에 메시지가 없으면 대기함 (scanf같은 느낌으로)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);		// 키보드 입력 메시지를 가공하여 컴퓨터가 처리할 수 있도록 만듬 (예 >> [WM_KEYDOWN A] -> [A키가 눌리면 A가 입력됬다는 메세지를 만듬])
			DispatchMessage(&msg);		// 윈도우에 등록된 프로시저 함수를 호출하는 함수	
		}
		else
		{
			SCENEMANAGER->Run();
		}
	}

	SCENEMANAGER->Release();

	return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

LRESULT WindowProc
(
	HWND hWnd,						// 메세지 프로시저 함수를 호출한 윈도우의 식별자값
	UINT Msg,						// 발생한 메세지 타입 ( 이벤트 타입 )
	WPARAM wParam, LPARAM lParam	// 이벤트 타입에 따른 부가적인 값 (키 , 마우스 , 시스템 정보 등) 
)
{
	switch (Msg)
	{
	case WM_CREATE:								// 윈도우가 생성될때	

		SCENEMANAGER->Init(hWnd);
		SCENEMANAGER->Add(SceneManager::LOGO, new Logo);
		SCENEMANAGER->Add(SceneManager::TITLE, new Title);
		SCENEMANAGER->Add(SceneManager::INGAME, new InGame);

		Draw::character = (HBITMAP)LoadImage(NULL, TEXT("Character.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
		Draw::characterMask = (HBITMAP)LoadImage(NULL, TEXT("CharacterMask.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);

		Draw::titleImg = (HBITMAP)LoadImage(NULL, TEXT("Title.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);

		GetClientRect(hWnd, &crt);				// 화면크기를 Rect변수에 넣어줌

		SetTimer(hWnd, 1, 10, NULL);			// 0.01초주기로 타이머설정
		SendMessage(hWnd, WM_TIMER, 1, 0);		// 타이머 메시지를 보내줌

		hDC = GetDC(hWnd);
		break;

	case WM_COMMAND:							// 사용자가 추가한 이벤트를 처리할 때 사용됨
		break;
	case WM_KEYDOWN:							// 키입력시 발생함
		SCENEMANAGER->Input(wParam, lParam);
		break;
	case WM_TIMER:								// 타이머 신호가 왓을때
		SCENEMANAGER->Awake();
		SCENEMANAGER->Update();
		time++;
	case WM_PAINT:	//윈도우 사이즈 변경 및 최소화 최대화가 발생될때 호출되는 메시지

		SCENEMANAGER->Render();
		break;
	case WM_DESTROY:							// 윈도우가 파괴됨
		PostQuitMessage(0);						// 메세지 큐에 WM_QUIT 메세지를 넣어주는 함수 (WM_QUIT : 윈도우를 종료하라는 메세지)
		return 0;
	}

	return DefWindowProc(hWnd, Msg, wParam, lParam);		// 컴퓨터가 처리하지 않은 기본적인 처리를 해주는 함수
}
