#include "stdafx.h"
#include "SceneGame.h"
#include "Vause.h"
#include "Ball.h"
#include "TileMap.h"
#include "UiInGame.h"
SceneGame::SceneGame() : Scene(SceneIds::Game)
{

}

void SceneGame::Init()
{
	tileMap = AddGo(new TileMap("TileMap"));
	vause = AddGo(new Vause("Vause"));
	ball = AddGo(new Ball("Ball"));
	uiInGame = AddGo(new UiInGame("UiInGame"));
	Scene::Init();
}

void SceneGame::Enter()
{

	Scene::Enter();
	sf::Vector2f size = FRAMEWORK.GetWindowSizeF();
	worldView.setSize(size);
	worldView.setCenter(0.f, 0.f);

	uiView.setSize(size);
	uiView.setCenter(size.x * 0.5f, size.y * 0.5f);

}

void SceneGame::Exit()
{
	Scene::Exit();
}

void SceneGame::Update(float dt)
{
	Scene::Update(dt);
	UpdateUi();
	if(vause->IsGameover())
	{
		std::cout << "Gameover!!" << std::endl;
	}

	if (!ball->isMove())
	{
		ball->SetPosition(vause->GetPosition()); 

		if (InputMgr::GetKeyDown(sf::Keyboard::Space))
		{
			ball->Fire({ 1.f,-1.f }, 500.f);
		}
	}




	///배속 코드
	if (InputMgr::GetKey(sf::Keyboard::Z))
	{
		FRAMEWORK.SetTimeScale(3.f);
	}
	if (InputMgr::GetKeyUp(sf::Keyboard::Z))
	{
		FRAMEWORK.SetTimeScale(1.f);
	}

	if (InputMgr::GetKey(sf::Keyboard::X))
	{
		FRAMEWORK.SetTimeScale(0.3f);
	}
	if (InputMgr::GetKeyUp(sf::Keyboard::X))
	{
		FRAMEWORK.SetTimeScale(1.f);
	}

	if (InputMgr::GetKeyDown(sf::Keyboard::C))
	{
		Variables::isDrawHitBox = !Variables::isDrawHitBox;
	}	
}

void SceneGame::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}

void SceneGame::UpdateUi()
{
	uiInGame->SetScore(score);
	uiInGame->SetHighScore(highScore);
}