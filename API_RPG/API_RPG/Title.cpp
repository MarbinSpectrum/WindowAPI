#include "Title.h"
#include "SceneManager.h"
#include "ObjectManager.h"

void Title::Awake()
{
	OBJECTMANAGER->Add(new TitleImg);
	OBJECTMANAGER->Add(new Player);
}

void Title::Start()
{
}

void Title::Update()
{
	OBJECTMANAGER->Update();
}

void Title::Input(WPARAM wParam, LPARAM lParam)
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

void Title::Run()
{

}

void Title::Render(HDC hdc)
{
	OBJECTMANAGER->Render(hdc);
}

void Title::Exit()
{
	OBJECTMANAGER->Clear();
}
