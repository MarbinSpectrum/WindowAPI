#pragma once

#include "Object.h"
class Player : public Object
{
public :
	Player();
	Vector2 characterRect;
	float speed;
	Vector2 MoveDic;
	typedef enum PlayerState
	{
		Idle,
		rightDownMove,
		rightMove,
		rightUpMove,
		UpMove,
		leftUpMove,
		leftMove,
		leftDownMove,
		DownMove

	}PlayerState;

	PlayerState state;

	virtual void Render(HDC hdc);
	virtual void Input(WPARAM wParam, LPARAM lParam);
	virtual void Update();

	void DrawRunAnim(HDC hdc, PlayerState state, int i);
};

