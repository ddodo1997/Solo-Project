#include "stdafx.h"
#include "SceneGame.h"
#include "Vause.h"
#include "Ball.h"
#include "TileMap.h"
#include "UiInGame.h"
#include "Bricks.h"
#include "Item.h"
#include "Laser.h"
#include "UiCenter.h"
SceneGame::SceneGame(SceneIds id) : Scene(id)
{

}

void SceneGame::Init()
{
	tileMap = AddGo(new TileMap("TileMap"));
	vause = AddGo(new Vause("Vause"));
	for (int i = 0; i < 2; i++)
	{
		lasers.push_back(AddGo(new Laser("Laser")));
	}
	uiInGame = AddGo(new UiInGame("UiInGame"));
	uiCenter = AddGo(new UiCenter("UiCenter"));

	Scene::Init();
}



void SceneGame::Enter()
{
	Scene::Enter();

	SOUND_MGR.PlayBgm("sounds/resources_musics_evolution_sphere.ogg");

	worldView.setSize(windowSize);
	worldView.setCenter(0.f, 0.f);

	uiView.setSize(windowSize);
	uiView.setCenter(windowSize.x * 0.5f, windowSize.y * 0.5f);

	score = 0;
}

void SceneGame::Exit()
{
	ReturnAllObj();
	Scene::Exit();
}

void SceneGame::Update(float dt)
{
	Scene::Update(dt);
	UpdateUi();

	if (InputMgr::GetKeyDown(sf::Keyboard::Escape))
	{
		SCENE_MGR.ChangeScene(SceneIds::Main);
	}

	if (!mainBall->isMove())
	{
		mainBall->SetPosition(vause->GetPosition());
		if (InputMgr::GetKeyDown(sf::Keyboard::Space))
		{
			mainBall->Fire({ 1.f,-1.f }, 500.f);
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
		FRAMEWORK.SetTimeScale(0.05f);
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
	uiInGame->SetExtraLife(vause->GetExtraLife());
}

void SceneGame::ReturnItem(Item* item)
{
	RemoveGo(item);
	itemPool.Return(item);
	activeItems.remove(item);
}

Ball* SceneGame::SpawnBall(const sf::Vector2f& position, bool isMoving)
{
	Ball* ball = ballsPool.Take();
	activeBalls.push_back(ball);

	ball->SetMove(isMoving);

	ball->SetPosition(position);
	return AddGo(ball);
}

void SceneGame::ReturnBall(Ball* ball)
{
	RemoveGo(ball);
	ballsPool.Return(ball);
	activeBalls.remove(ball);
}

void SceneGame::ReturnAllObj()
{
	for (auto item : activeItems)
	{
		RemoveGo(item);
		itemPool.Return(item);
	}
	activeItems.clear();

	for (auto ball : activeBalls)
	{
		RemoveGo(ball);
		ballsPool.Return(ball);
	}
	activeBalls.clear();
}