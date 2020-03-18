#include "Title.h"
#include "SceneManager.h"
#include "ObjectManager.h"

void Title::Awake()
{
}

void Title::Start()
{
}

void Title::Update()
{
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
