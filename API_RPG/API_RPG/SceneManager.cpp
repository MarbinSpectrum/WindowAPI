#include "SceneManager.h"

SceneManager *SceneManager::instance = nullptr;

void SceneManager::Init(HWND Hwnd)
{
	nowScene = TITLE;

	hwnd = Hwnd;

	brush = CreateSolidBrush(RGB(0, 0, 0));

	//현재 윈도우에 맞는 헨들에서 DC를 받아옴
	frontDC = GetDC(hwnd);

	sceneAwake = false;
	sceneStart = false;
}

void SceneManager::Add(SceneType i,Scene *p)
{
	if (sceneData.find(i) == sceneData.end())
		sceneData[i] = p;
}

void SceneManager::Render()
{
	//backDC에 frontDC 복사
	backDC = CreateCompatibleDC(frontDC);

	//화면크기와 같은 비트맵생성
	GetClientRect(hwnd, &rect);
	frontBitmap = CreateCompatibleBitmap(frontDC, rect.right, rect.bottom);

	//backDC에 비트맵설정
	backBitmap = (HBITMAP)SelectObject(backDC, frontBitmap);

	FillRect(backDC, &rect, brush);

	//씬이 존재여부를 판독후 호출
	if (sceneData.find(nowScene) != sceneData.end())
		sceneData[nowScene]->Render(backDC);

	BitBlt(frontDC, 0, 0, rect.right, rect.bottom, backDC, 0, 0, SRCCOPY);

	//버퍼를 해체해줌
	DeleteObject(SelectObject(backDC, backBitmap));
	DeleteDC(backDC);
	ReleaseDC(hwnd, backDC);
}

void SceneManager::Run()
{
	if (sceneData.find(nowScene) != sceneData.end())
		sceneData[nowScene]->Run();
}

void SceneManager::Input(WPARAM wParam, LPARAM lParam)
{
	if (sceneData.find(nowScene) != sceneData.end())
		sceneData[nowScene]->Input(wParam, lParam);
}

void SceneManager::Awake()
{
	if (sceneAwake)
		return;
	sceneAwake = true;

	if (sceneData.find(nowScene) != sceneData.end())
		sceneData[nowScene]->Awake();

	Start();
}

void SceneManager::Start()
{
	if (sceneStart)
		return;
	sceneStart = true;

	if (sceneData.find(nowScene) != sceneData.end())
		sceneData[nowScene]->Start();
}

void SceneManager::Update()
{
	if (sceneData.find(nowScene) != sceneData.end())
		sceneData[nowScene]->Update();
}


void SceneManager::Exit()
{
	if (sceneData.find(nowScene) != sceneData.end())
		sceneData[nowScene]->Exit();
}

void SceneManager::Release()
{
	//버퍼를 해체해줌
	DeleteObject(backBitmap);
	DeleteObject(brush);
	DeleteObject(backDC);

	for (MITER iter = sceneData.begin(); iter != sceneData.end(); iter++)
		SAFE_RELEASE(iter->second);

	sceneData.clear();

	SAFE_RELEASE(instance);
}

void SceneManager::MoveScene(SceneType i)
{
	Exit();
	nowScene = i;
	sceneAwake = false;
	sceneStart = false;
}


SceneManager * SceneManager::Get()
{
	if (instance == nullptr)
		instance = new SceneManager;
	return instance;
}
