#include "InGame.h"
#include "SceneManager.h"
#include "ObjectManager.h"

void InGame::Awake()
{
	OBJECTMANAGER->Add(new Player);
}

void InGame::Start()
{
}

void InGame::Update()
{
	OBJECTMANAGER->Update();
}

void InGame::Input(WPARAM wParam, LPARAM lParam)
{
	switch (wParam) {
	case VK_LEFT:
		break;
	case VK_RIGHT:
		break;
	case VK_UP:
		break;
	case VK_DOWN:
		break;
	}
	OBJECTMANAGER->Input(wParam, lParam);
}

void InGame::Run()
{
}

void InGame::Render(HDC hdc)
{
	OBJECTMANAGER->Render(hdc);
}

void InGame::Exit()
{
	OBJECTMANAGER->Clear();
}
