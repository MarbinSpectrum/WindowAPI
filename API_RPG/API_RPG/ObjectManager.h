#pragma once

#include<vector>

#include"Player.h"
#include"TitleImg.h"

class ObjectManager
{
private:
	static ObjectManager *instance;
	typedef std::vector<Object*> ObjectVector;
	typedef ObjectVector::iterator MITER;

	ObjectVector objectData;
public:
	static ObjectManager *Get();

	void Add(Object *p);

	void Render(HDC hdc);
	void Update();
	void Input(WPARAM wParam, LPARAM lParam);
	void Clear();
};

#define OBJECTMANAGER ObjectManager::Get()

