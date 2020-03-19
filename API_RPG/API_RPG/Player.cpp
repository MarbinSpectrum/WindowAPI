#include "Player.h"

Player::Player()
{
	objectSprites = Draw::character;
	objectSpritesMask = Draw::characterMask;

	characterRect = Draw::characterRect;

	MoveDic = Vector2(0, 0);
	scale = Vector2(1, 1);

	time = 0;
	speed = 2;

	pos = Vector2(25, 25);

	attackTime = 0;
	isAttack = false;
}

void Player::Render(HDC hdc)
{
	if (state != Idle)
	{
		//°È´Â°æ¿ì
		if (state < rightDownAttack)
		{
			backState = state;
			DrawAnim(hdc, state, ((int)(time / 2) % 4));
		}
		else 
		{
			DrawAnim(hdc, state, ((int)(attackTime / 10) % 2));
		}
	}
	else
		DrawAnim(hdc, backState, 0);

}

void Player::Input(WPARAM wParam, LPARAM lParam)
{

}

void Player::MovePlayer()
{
	if (isAttack)
		return;

	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{
		MoveDic.x = -1;
		pos.x -= speed;
	}
	else if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		MoveDic.x = +1;
		pos.x += speed;
	}
	else
		MoveDic.x = 0;

	if (GetAsyncKeyState(VK_UP) & 0x8000)
	{
		MoveDic.y = +1;
		pos.y -= speed;
	}
	else if (GetAsyncKeyState(VK_DOWN) & 0x8000)
	{
		MoveDic.y = -1;
		pos.y += speed;
	}
	else
		MoveDic.y = 0;

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
}

void Player::AttackPlayer()
{
	if (isAttack)
	{
		attackTime += 1;

		if (rightDownAttack <= state && state <= DownAttackEnd)
		{
			if (state % 2 == 1 && attackTime >= 15)
			{
				state = (PlayerState)((int)(state + 1));
				attackTime = 0;
			}
			else if (attackTime >= 15)
				isAttack = false;
		}


	}
	else
	{
		if (GetAsyncKeyState(VK_SPACE) & 0x8000)
		{
			if (backState == rightMove)
				state = rightAttack;
			else if (backState == rightUpMove)
				state = rightUpAttack;
			else if (backState == rightDownMove)
				state = rightDownAttack;
			else if (backState == UpMove)
				state = UpAttack;
			else if (backState == leftMove)
				state = leftAttack;
			else if (backState == leftUpMove)
				state = leftUpAttack;
			else if (backState == leftDownMove)
				state = leftDownAttack;
			else if (backState == DownMove)
				state = DownAttack;
			else
				state = DownAttack;

			isAttack = true;
			attackTime = 0;
		}
	}
}

void Player::Update()
{
	time+=0.1f;
	AttackPlayer();
	MovePlayer();
}

void Player::DrawAnim(HDC hdc,PlayerState state, int i)
{
	switch (state)
	{
#pragma region Idle
	case Idle:
		DrawBitmap(hdc, pos.x, pos.y, characterRect.x, characterRect.y, characterRect.x * i, characterRect.y * 0, objectSprites, objectSpritesMask, true, false, scale);
		break;
#pragma endregion

#pragma region rightMove
	case rightMove:
		DrawBitmap(hdc, pos.x, pos.y, characterRect.x, characterRect.y, characterRect.x * i, characterRect.y * 2, objectSprites, objectSpritesMask, true, false, scale);
		break;
#pragma endregion

#pragma region rightUpMove
	case rightUpMove:
		DrawBitmap(hdc, pos.x, pos.y, characterRect.x, characterRect.y, characterRect.x * i, characterRect.y * 3, objectSprites, objectSpritesMask, true, false, scale);
		break;
#pragma endregion

#pragma region rightDownMove
	case rightDownMove:
		DrawBitmap(hdc, pos.x, pos.y, characterRect.x, characterRect.y, characterRect.x * i, characterRect.y * 1, objectSprites, objectSpritesMask, true, false, scale);
		break;
#pragma endregion

#pragma region UpMove
	case UpMove:
		DrawBitmap(hdc, pos.x, pos.y, characterRect.x, characterRect.y, characterRect.x * i, characterRect.y * 4, objectSprites, objectSpritesMask, false, false, scale);
		break;
#pragma endregion

#pragma region leftMove
	case leftMove:
		DrawBitmap(hdc, pos.x, pos.y, characterRect.x, characterRect.y, characterRect.x * i, characterRect.y * 2, objectSprites, objectSpritesMask, false, false, scale);
		break;
#pragma endregion

#pragma region leftUpMove
	case leftUpMove:
		DrawBitmap(hdc, pos.x, pos.y, characterRect.x, characterRect.y, characterRect.x * i, characterRect.y * 3, objectSprites, objectSpritesMask, false, false, scale);
		break;
#pragma endregion

#pragma region leftDownMove
	case leftDownMove:
		DrawBitmap(hdc, pos.x, pos.y, characterRect.x, characterRect.y, characterRect.x * i, characterRect.y * 1, objectSprites, objectSpritesMask, false, false, scale);
		break;
#pragma endregion

#pragma region DownMove
	case DownMove:
		DrawBitmap(hdc, pos.x, pos.y, characterRect.x, characterRect.y, characterRect.x * i, characterRect.y * 0, objectSprites, objectSpritesMask, false, false, scale);
		break;
#pragma endregion


#pragma region rightAttack
	case rightAttack:
		DrawBitmap(hdc, pos.x, pos.y, characterRect.x, characterRect.y, 0, characterRect.y * 2 + 512, objectSprites, objectSpritesMask, true, false, scale);
		break;
	case rightAttackEnd:
		DrawBitmap(hdc, pos.x, pos.y, 48, characterRect.y, 48 * i + 32, characterRect.y * 2 + 512, objectSprites, objectSpritesMask, true, false, scale);
		break;
#pragma endregion

#pragma region rightUpAttack
	case rightUpAttack:
		DrawBitmap(hdc, pos.x, pos.y, characterRect.x, characterRect.y, 40 * 0, characterRect.y * 3 + 512, objectSprites, objectSpritesMask, true, false, scale);
		break;
	case rightUpAttackEnd:
		DrawBitmap(hdc, pos.x, pos.y, 48, characterRect.y, 48 * i + 32, characterRect.y * 2 + 512, objectSprites, objectSpritesMask, true, false, scale);
		break;
#pragma endregion

#pragma region rightDownAttack
	case rightDownAttack:
		DrawBitmap(hdc, pos.x, pos.y, characterRect.x, characterRect.y, 40 * 0, characterRect.y * 1 + 512, objectSprites, objectSpritesMask, true, false, scale);
		break;
	case rightDownAttackEnd:
		DrawBitmap(hdc, pos.x, pos.y, 48, characterRect.y, 48 * i + 32, characterRect.y * 1 + 512, objectSprites, objectSpritesMask, true, false, scale);
		break;
#pragma endregion

#pragma region UpAttack
	case UpAttack:
		DrawBitmap(hdc, pos.x, pos.y, characterRect.x, characterRect.y, 40 * 0, characterRect.y * 4 + 510, objectSprites, objectSpritesMask, false, false, scale);
		break;
	case UpAttackEnd:
		DrawBitmap(hdc, pos.x, pos.y, 40, characterRect.y, 48 * i + 40, characterRect.y * 4 + 512, objectSprites, objectSpritesMask, false, false, scale);
		break;
#pragma endregion

#pragma region leftAttack
	case leftAttack:
		DrawBitmap(hdc, pos.x, pos.y, characterRect.x, characterRect.y, 0, characterRect.y * 2 + 512, objectSprites, objectSpritesMask, false, false, scale);
		break;
	case leftAttackEnd:
		DrawBitmap(hdc, pos.x - scale.x * 16, pos.y, 48, characterRect.y, 48 * i + 32, characterRect.y * 2 + 512, objectSprites, objectSpritesMask, false, false, scale);
		break;
#pragma endregion

#pragma region leftUpAttack
	case leftUpAttack:
		DrawBitmap(hdc, pos.x, pos.y, characterRect.x, characterRect.y, 40 * 0, characterRect.y * 3 + 512, objectSprites, objectSpritesMask, false, false, scale);
		break;
	case leftUpAttackEnd:
		DrawBitmap(hdc, pos.x - scale.x * 16, pos.y, 48, characterRect.y, 48 * i + 32, characterRect.y * 3 + 512, objectSprites, objectSpritesMask, false, false, scale);
		break;
#pragma endregion

#pragma region leftDownAttack
	case leftDownAttack:
		DrawBitmap(hdc, pos.x, pos.y, characterRect.x, characterRect.y, 40 * 0, characterRect.y * 1 + 512, objectSprites, objectSpritesMask, false, false, scale);
		break;
	case leftDownAttackEnd:
		DrawBitmap(hdc, pos.x - scale.x * 16, pos.y, 48, characterRect.y, 48 * i + 32, characterRect.y * 1 + 512, objectSprites, objectSpritesMask, false, false, scale);
		break;
#pragma endregion

#pragma region DownAttack
	case DownAttack:
		DrawBitmap(hdc, pos.x, pos.y, characterRect.x, characterRect.y, 40 * 0, characterRect.y * 0 + 512, objectSprites, objectSpritesMask, false, false, scale);
		break;
	case DownAttackEnd:
		DrawBitmap(hdc, pos.x, pos.y, 40, characterRect.y, 48 * i + 40, characterRect.y * 0 + 512, objectSprites, objectSpritesMask, false, false, scale);
		break;
#pragma endregion
	}
}
