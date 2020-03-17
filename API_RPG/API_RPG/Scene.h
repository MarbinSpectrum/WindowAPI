#pragma once

#include "framework.h"
#include "Draw.h"

class Scene
{
public:
	Scene();
	virtual ~Scene();
	virtual void Awake();
	virtual void Start();
	virtual void Update();
	virtual void Input();
	virtual void Run();
	virtual void Render(HDC hdc);
	virtual void Exit();
};