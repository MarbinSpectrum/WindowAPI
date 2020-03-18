#include "Player.h"

Player::Player()
{
	objectSprites = Draw::character;
	objectSpritesMask = Draw::characterMask;

	characterRect = Draw::characterRect;

	MoveDic = Vector2(0, 0);
	scale = Vector2(3, 3);
	time = 0;
	speed = 5;
}

void Player::Render(HDC hdc)
{
	if (MoveDic.x == 1 && MoveDic.y == 0)
		state = rightMove;
	else if (MoveDic.x == 1 && MoveDic.y == 1)
		state = rightUpMove;
	else if (MoveDic.x == 1 && MoveDic.y == -1)
		state = rightDownMove;
	else if (MoveDic.x == 0 && MoveDic.y == 1)
		state = UpMove;
	else if (MoveDic.x == -1 && MoveDic.y == 0)
		state = leftMove;
	else if (MoveDic.x == -1 && MoveDic.y == 1)
		state = leftUpMove;
	else if (MoveDic.x == -1 && MoveDic.y == -1)
		state = leftDownMove;
	else if (MoveDic.x == 0 && MoveDic.y == -1)
		state = DownMove;
	else
		state = Idle;

	if(state != Idle)
		DrawRunAnim(hdc, state, ((int)(time) % 4));
	else
		DrawRunAnim(hdc, state, 0);

}

void Player::Input(WPARAM wParam, LPARAM lParam)
{
	if (GetKeyState(VK_LEFT) < 0)
	{
		MoveDic.x = -1;
		pos.x -= speed;
	}
	if (GetKeyState(VK_RIGHT) < 0)
	{
		MoveDic.x = +1;
		pos.x += speed;
	}
	if (GetKeyState(VK_RIGHT) >= 0 && GetKeyState(VK_LEFT) >= 0)
		MoveDic.x = 0;

	if (GetKeyState(VK_UP) < 0)
	{
		MoveDic.y = +1;
		pos.y -= speed;
	}
	if (GetKeyState(VK_DOWN) < 0)
	{
		MoveDic.y = -1;
		pos.y += speed;
	}
	if (GetKeyState(VK_UP) >= 0 && GetKeyState(VK_DOWN) >= 0)
		MoveDic.y = 0;
}

void Player::Update()
{
	time+=0.1f;
}

void Player::DrawRunAnim(HDC hdc,PlayerState state, int i)
{
	switch (state)
	{
	case Idle:
		DrawBitmap(hdc, pos.x, pos.y, characterRect.x, characterRect.y, characterRect.x * i, characterRect.y * 2, objectSprites, objectSpritesMask, true, false, scale);
		break;
	case rightMove:
		DrawBitmap(hdc, pos.x, pos.y, characterRect.x, characterRect.y, characterRect.x * i, characterRect.y * 2, objectSprites, objectSpritesMask, true, false, scale);
		break;
	case rightUpMove:
		DrawBitmap(hdc, pos.x, pos.y, characterRect.x, characterRect.y, characterRect.x * i, characterRect.y * 3, objectSprites, objectSpritesMask, true, false, scale);
		break;
	case rightDownMove:
		DrawBitmap(hdc, pos.x, pos.y, characterRect.x, characterRect.y, characterRect.x * i, characterRect.y * 1, objectSprites, objectSpritesMask, true, false, scale);
		break;
	case UpMove:
		DrawBitmap(hdc, pos.x, pos.y, characterRect.x, characterRect.y, characterRect.x * i, characterRect.y * 4, objectSprites, objectSpritesMask, false, false, scale);
		break;
	case leftMove:
		DrawBitmap(hdc, pos.x, pos.y, characterRect.x, characterRect.y, characterRect.x * i, characterRect.y * 2, objectSprites, objectSpritesMask, false, false, scale);
		break;
	case leftUpMove:
		DrawBitmap(hdc, pos.x, pos.y, characterRect.x, characterRect.y, characterRect.x * i, characterRect.y * 3, objectSprites, objectSpritesMask, false, false, scale);
		break;
	case leftDownMove:
		DrawBitmap(hdc, pos.x, pos.y, characterRect.x, characterRect.y, characterRect.x * i, characterRect.y * 1, objectSprites, objectSpritesMask, false, false, scale);
		break;
	case DownMove:
		DrawBitmap(hdc, pos.x, pos.y, characterRect.x, characterRect.y, characterRect.x * i, characterRect.y * 0, objectSprites, objectSpritesMask, false, false, scale);
		break;
	}
}
