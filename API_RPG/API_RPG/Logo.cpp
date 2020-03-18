#include "Logo.h"
#include "SceneManager.h"
#include "ObjectManager.h"

void Logo::Awake()
{
}

void Logo::Start()
{
}

void Logo::Update()
{
}

void Logo::Input(WPARAM wParam, LPARAM lParam)
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

void Logo::Run()
{

}

void Logo::Render(HDC hdc)
{
	OBJECTMANAGER->Render(hdc);
}

void Logo::Exit()
{
	OBJECTMANAGER->Clear();
}
