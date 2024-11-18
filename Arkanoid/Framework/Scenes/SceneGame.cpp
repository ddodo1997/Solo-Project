#include "stdafx.h"
#include "SceneGame.h"
#include "Vause.h"
#include "Ball.h"
#include "TileMap.h"
#include "UiInGame.h"
#include "Bricks.h"
#include "Item.h"
#include "Laser.h"
SceneGame::SceneGame() : Scene(SceneIds::Game)
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
	InitBricks();

	Scene::Init();
}

void SceneGame::InitBricks()
{
	bricks.resize(bricksSize.x);
	for (int i = 0; i < bricksSize.x; i++)
	{
		bricks[i].resize(bricksSize.y);
	}
	for (int i = 0; i < bricksSize.x; i++)
	{
		for (int j = 0; j < bricksSize.y; j++)
		{
			bricks[i][j] = AddGo(new Bricks("Bricks"));
		}
	}
}

void SceneGame::Enter()
{
	SetStage("Stage1");
	sf::Vector2f size = FRAMEWORK.GetWindowSizeF();
	worldView.setSize(size);
	worldView.setCenter(0.f, 0.f);

	uiView.setSize(size);
	uiView.setCenter(size.x * 0.5f, size.y * 0.5f);


	Scene::Enter();

	mainBall = SpawnBall(vause->GetPosition());
}

void SceneGame::Exit()
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

	Scene::Exit();
}

void SceneGame::Update(float dt)
{
	Scene::Update(dt);
	UpdateUi();
	if (vause->IsGameover())
	{
		std::cout << "Gameover!!" << std::endl;
	}

	//TODO : 공의 isMoving 상태에 따라 바우스를 따라가도록

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
	uiInGame->SetHighScore(highScore);
	uiInGame->SetExtraLife(vause->GetExtraLife());
}

void SceneGame::SetStage(const std::string& key)
{
	for (int i = 0; i < bricksSize.x; i++)
	{
		for (int j = 0; j < bricksSize.y; j++)
		{
			bricks[i][j]->SetType((Bricks::Types)STAGES_TABLE->Get(key)[i][j]);
			auto size = bricks[i][j]->GetLocalBounds();
			auto scale = bricks[i][j]->GetScale();
			bricks[i][j]->SetPosition({ -320.f + j * size.width * scale.x, -400.f + i * size.height * scale.y });
		}
	}
}

void SceneGame::SpawnItem(const sf::Vector2f& position)
{
	Item* item = itemPool.Take();
	activeItems.push_back(item);

	int rand = Utils::RandomRange(0, 1000);
	int cnt = 0;
	int weight = 0;
	//
	// None,
	// Slow,
	// Laser,
	// Enlarge,
	// Disruption,
	// Player
	int percentage[6] = { 750,100,50,50,20,30 };
	for (int i = 0; i < Item::TotalTypes; i++)
	{
		if (weight + percentage[i] > rand)
		{
			break;
		}
		weight += percentage[i];
		cnt++;
	}

	Item::Types type = (Item::Types)cnt;
	item->SetType(type);
	item->SetPosition(position);

	AddGo(item);
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