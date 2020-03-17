#pragma once
#include"Scene.h"

class Title : public Scene
{
public:
	virtual void Awake();
	virtual void Start();
	virtual void Update();
	virtual void Input();
	virtual void Run();
	virtual void Render(HDC hdc);
	virtual void Exit();
};