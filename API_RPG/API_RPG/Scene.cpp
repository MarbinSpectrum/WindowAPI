#include "Scene.h"
#include "ObjectManager.h"

Scene::Scene()
{
}

Scene::~Scene()
{
}

void Scene::Awake()
{

}

void Scene::Start()
{

}

void Scene::Update()
{

}

void Scene::Input(WPARAM wParam, LPARAM lParam)
{
	switch (wParam) {
	case VK_LEFT:
		break;
	case VK_RIGHT:
		break;
	case VK_UP:
		break;
	case VK_DOWN:
		break;
	}

	OBJECTMANAGER->Input(wParam, lParam);
}

void Scene::Run()
{

}

void Scene::Render(HDC hdc)
{
}

void Scene::Exit()
{
}
