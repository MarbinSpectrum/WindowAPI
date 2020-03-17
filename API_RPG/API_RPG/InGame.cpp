#include "InGame.h"

void InGame::Awake()
{
}

void InGame::Start()
{
}

void InGame::Update()
{
}

void InGame::Input()
{
}

void InGame::Run()
{
}

void InGame::Render(HDC hdc)
{
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			DrawBitmap(hdc, i * Draw::characterRect.x, j * Draw::characterRect.y, Draw::characterRect.x, Draw::characterRect.y, i * Draw::characterRect.x, j * Draw::characterRect.y, Draw::character, Draw::characterMask);
}

void InGame::Exit()
{
}
