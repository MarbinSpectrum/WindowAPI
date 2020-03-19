#pragma once

#include "Object.h"
class Player : public Object
{
public :
	Player();

	Vector2 characterRect;

	///////////////////////////////////////////////////////////////////////

	float speed;
	Vector2 MoveDic;

	bool isAttack;
	float attackTime;
	///////////////////////////////////////////////////////////////////////

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
		DownMove,

		rightDownAttack,
		rightDownAttackEnd,
		rightAttack,
		rightAttackEnd,
		rightUpAttack,
		rightUpAttackEnd,
		UpAttack,
		UpAttackEnd,
		leftUpAttack,
		leftUpAttackEnd,
		leftAttack,
		leftAttackEnd,
		leftDownAttack,
		leftDownAttackEnd,
		DownAttack,
		DownAttackEnd


	}PlayerState;

	PlayerState state;
	PlayerState backState;

	///////////////////////////////////////////////////////////////////////

	virtual void Render(HDC hdc);
	virtual void Input(WPARAM wParam, LPARAM lParam);
	void MovePlayer();
	void AttackPlayer();
	virtual void Update();

	void DrawAnim(HDC hdc, PlayerState state, int i);
};

