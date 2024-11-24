#include "stdafx.h"
#include "SceneMain.h"
#include "UiMain.h"
SceneMain::SceneMain() : Scene(SceneIds::Main)
{
}

void SceneMain::Init()
{
	uiMain = AddGo(new UiMain("Main Strings"));

	Scene::Init();
}

void SceneMain::Enter()
{
	Scene::Enter();

	sf::Vector2f size = FRAMEWORK.GetWindowSizeF();
	worldView.setSize(size);
	worldView.setCenter(0.f, 0.f);

	uiView.setSize(size);
	uiView.setCenter(size.x * 0.5f, size.y * 0.5f);

	score = 0;
}

void SceneMain::Exit()
{
	Scene::Exit();
}

void SceneMain::Update(float dt)
{
	Scene::Update(dt);
}

void SceneMain::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}
