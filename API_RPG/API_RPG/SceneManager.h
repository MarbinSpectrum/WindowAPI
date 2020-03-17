#pragma once

#include<map>

#include"Title.h"
#include"Logo.h"
#include"InGame.h"

class SceneManager
{
private :
	static SceneManager *instance;

public :

	typedef enum SceneType
	{
		LOGO,
		TITLE,
		INGAME
	}SceneType;

	typedef std::map<int, Scene*> SceneMap;
	typedef SceneMap::iterator MITER;

	SceneMap sceneData;

	void Init(HWND hWnd);
	void Add(SceneType i, Scene *p);
	void Render();
	void Run();
	void Input();
	void Update();
	void Release();

public:
	SceneType nowScene;

	static SceneManager *Get();

	HWND hwnd;

	HDC frontDC;
	HDC backDC;

	HBRUSH brush;

	//화면크기
	RECT rect;

	HBITMAP frontBitmap;
	HBITMAP backBitmap;

};

#define SCENEMANAGER SceneManager::Get()

#define SAFE_RELEASE(P){  if(P != nullptr) {delete P;  P =nullptr; }    }