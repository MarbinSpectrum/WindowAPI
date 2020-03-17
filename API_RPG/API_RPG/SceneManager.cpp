#include "SceneManager.h"

SceneManager *SceneManager::instance = nullptr;

void SceneManager::Init(HWND Hwnd)
{
	nowScene = INGAME;

	hwnd = Hwnd;

	brush = CreateSolidBrush(RGB(0, 0, 0));

	//���� �����쿡 �´� ��鿡�� DC�� �޾ƿ�
	frontDC = GetDC(hwnd);

}

void SceneManager::Add(SceneType i,Scene *p)
{
	if (sceneData.find(i) == sceneData.end())
		sceneData[i] = p;
}

void SceneManager::Render()
{
	//backDC�� frontDC ����
	backDC = CreateCompatibleDC(frontDC);

	//ȭ��ũ��� ���� ��Ʈ�ʻ���
	GetClientRect(hwnd, &rect);
	frontBitmap = CreateCompatibleBitmap(frontDC, rect.right, rect.bottom);

	//backDC�� ��Ʈ�ʼ���
	backBitmap = (HBITMAP)SelectObject(backDC, frontBitmap);

	FillRect(backDC, &rect, brush);

	//���� ���翩�θ� �ǵ��� ȣ��
	if (sceneData.find(nowScene) != sceneData.end())
		sceneData[nowScene]->Render(backDC);

	BitBlt(frontDC, 0, 0, rect.right, rect.bottom, backDC, 0, 0, SRCCOPY);

	//���۸� ��ü����
	DeleteObject(SelectObject(backDC, backBitmap));
	DeleteDC(backDC);
	ReleaseDC(hwnd, backDC);
}

void SceneManager::Run()
{
	if (sceneData.find(nowScene) != sceneData.end())
		sceneData[nowScene]->Run();
}

void SceneManager::Input()
{
	if (sceneData.find(nowScene) != sceneData.end())
		sceneData[nowScene]->Input();
}

void SceneManager::Update()
{
	if (sceneData.find(nowScene) != sceneData.end())
		sceneData[nowScene]->Update();
}

void SceneManager::Release()
{
	//���۸� ��ü����
	DeleteObject(backBitmap);
	DeleteObject(brush);
	DeleteObject(backDC);

	for (MITER iter = sceneData.begin(); iter != sceneData.end(); iter++)
		SAFE_RELEASE(iter->second);

	sceneData.clear();

	SAFE_RELEASE(instance);
}


SceneManager * SceneManager::Get()
{
	if (instance == nullptr)
		instance = new SceneManager;
	return instance;
}
