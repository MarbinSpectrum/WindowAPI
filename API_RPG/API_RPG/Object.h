#pragma once
#include "Draw.h"

class Object
{
public : 
	float time = 0;
	bool act;
	Vector2 pos;
	Vector2 scale;
	HBITMAP objectSprites;
	HBITMAP objectSpritesMask;
	virtual void Render(HDC hdc);
	virtual void Input(WPARAM wParam, LPARAM lParam);
	virtual void Update();

};

