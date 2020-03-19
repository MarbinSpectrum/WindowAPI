#include "TitleImg.h"

TitleImg::TitleImg()
{
	objectSprites = Draw::titleImg;
}

void TitleImg::Render(HDC hdc)
{
	DrawBitmap(hdc, pos.x, pos.y, objectSprites);
}