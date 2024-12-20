#include "stdafx.h"
#include "SceneInfinity.h"
#include "Vause.h"
#include "Bricks.h"
#include "UiCenter.h"
#include "UiInGame.h"
SceneInfinity::SceneInfinity() : SceneGame(SceneIds::Infinity)
{
	currentMode = Mode::Infinity;
}

void SceneInfinity::Init()
{
	InitBricks();
	SceneGame::Init();
}

void SceneInfinity::InitBricks()
{
	for (int i = 0; i < bricksSize.x; i++)
	{
		bricks.push_back(std::vector<Bricks*>());
		for (int j = 0; j < bricksSize.y; j++)
		{
			bricks[i].push_back(AddGo(new Bricks("Bricks")));
		}
	}
}

void SceneInfinity::SetStage()
{
	ReturnAllObj();
	vause->SetStatus(Vause::Status::Normal);
	mainBall = SpawnBall(vause->GetPosition());

	for (int i = 0; i < bricksSize.x; i++)
	{
		for (int j = 0; j < bricksSize.y; j++)
		{
			bricks[i][j]->SetType((Bricks::Types)-1);
			auto size = bricks[i][j]->GetLocalBounds();
			auto scale = bricks[i][j]->GetScale();
			bricks[i][j]->SetPosition({ -320.f + j * size.width * scale.x, -505.f + i * size.height * scale.y });
		}
	}
}

void SceneInfinity::Enter()
{
	SceneGame::Enter();	
	
	SetStage();
	ReturnAllObj();
	vause->SetStatus(Vause::Status::Normal);
	mainBall = SpawnBall(vause->GetPosition());
	uiCenter->SetString("");

	currentWave = 0;
	waveTimer = 0.f;
	PushWave();
}

void SceneInfinity::Exit()
{
	ReturnAllObj();
	Scene::Exit();
}

void SceneInfinity::Update(float dt)
{
	SceneGame::Update(dt);

	if (vause->IsGameover())
	{
		uiCenter->SetString("Press Enter To Main...");
		if (InputMgr::GetKeyDown(sf::Keyboard::Enter))
		{
			SCENE_MGR.ChangeScene(SceneIds::Main);
			uiCenter->SetString("");
		}

		return;
	}

	if (GameOver())
	{
		vause->SetGameover(true);
		ReturnAllObj();
	}

	if (InputMgr::GetKeyDown(sf::Keyboard::Num1))
	{
		PushWave();
	}

	waveTimer += dt;
	if (waveTimer > waveDelay)
	{
		PushWave();
		waveTimer = 0.f;
	}
}

void SceneInfinity::Draw(sf::RenderWindow& window)
{
	SceneGame::Draw(window);
}

void SceneInfinity::UpdateUi()
{
	uiInGame->SetWave(currentWave);
	uiInGame->SetBestRecord(BestRecordWave);
}

void SceneInfinity::SpawnItem(const sf::Vector2f& position)
{
	Item* item = itemPool.Take();
	activeItems.push_back(item);

	int rand = Utils::RandomRange(0, 1000);
	int cnt = 0;
	int weight = 0;

	int percentage[6] = { 750,0,100,100,50,0 };
	for (int i = 0; i < Item::TotalTypes; i++)
	{
		if (weight + percentage[i] >= rand)
		{
			break;
		}
		weight += percentage[i];
		cnt++;
	}

	Item::Types type = (Item::Types)cnt;
	item->SetType(type);
	//item->SetType(Item::Types::Disruption);
	item->SetPosition(position);

	AddGo(item);
}

bool SceneInfinity::GameOver()
{
	bool result = false;
	for (int i = 0; i < bricksSize.y; i++)
	{
		if (bricks[bricksSize.x - 1][i]->GetCurrentType() != Bricks::Types::None)
		{
			result = true;
			break;
		}
	}
	return result;
}

void SceneInfinity::PushWave()
{
	AddWave();

	for (int i = bricksSize.x - 1; i > 0 ; i--)
	{
		for (int j = 0; j < bricksSize.y; j++)
		{
			bricks[i][j]->SetType(bricks[i - 1][j]->GetCurrentType());
			if(bricks[i][j]->GetCurrentType() == Bricks::Types::Super)
				bricks[i][j]->SetHp(bricks[i - 1][j]->GetHp());
		}
	}
	for (int i = 0; i < bricksSize.y; i++)
	{
		bricks[0][i]->SetType((Bricks::Types)Utils::RandomRange(-1, currentWave > 20 ? 8 : 7));
	}
}
