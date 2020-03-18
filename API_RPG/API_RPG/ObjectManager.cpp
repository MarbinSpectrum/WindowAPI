#include "ObjectManager.h"

ObjectManager * ObjectManager::instance = nullptr;

ObjectManager * ObjectManager::Get()
{
	if (instance == nullptr)
		instance = new ObjectManager;
	return instance;
}

void ObjectManager::Add(Object * p)
{
	objectData.push_back(p);
}

void ObjectManager::Render(HDC hdc)
{
	for (int i = 0; i < objectData.size(); i++)
		objectData[i]->Render(hdc);
}

void ObjectManager::Update()
{
	for (int i = 0; i < objectData.size(); i++)
		objectData[i]->Update();
}

void ObjectManager::Input(WPARAM wParam, LPARAM lParam)
{
	for (int i = 0; i < objectData.size(); i++)
		objectData[i]->Input(wParam, lParam);
}

void ObjectManager::Clear()
{
	objectData.clear();
}
