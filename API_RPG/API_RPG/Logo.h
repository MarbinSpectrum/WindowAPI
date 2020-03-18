#pragma once
#include"Scene.h"

class Logo : public Scene
{
public:
	virtual void Awake();
	virtual void Start();
	virtual void Update();
	virtual void Input(WPARAM wParam, LPARAM lParam);
	virtual void Run();
	virtual void Render(HDC hdc);
	virtual void Exit();
};