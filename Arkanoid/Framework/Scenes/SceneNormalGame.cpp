#include "stdafx.h"
#include "SceneNormalGame.h"
#include "Vause.h"
#include "Ball.h"
#include "TileMap.h"
#include "UiInGame.h"
#include "Bricks.h"
#include "Item.h"
#include "Laser.h"
#include "UiCenter.h"
SceneNormalGame::SceneNormalGame() : SceneGame(SceneIds::NormalGame)
{
	currentMode = Mode::Normal;
}

void SceneNormalGame::Init()
{
	InitBricks();
	SceneGame::Init();
}

void SceneNormalGame::InitBricks()
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

void SceneNormalGame::Enter()
{
	SceneGame::Enter();
	SetStage(Stages::Stage1);
	uiCenter->SetString("");
	score = 0;
}

void SceneNormalGame::Exit()
{
	ReturnAllObj();
	SceneGame::Exit();
}

void SceneNormalGame::Update(float dt)
{
	if (isStageClear())
	{
		uiCenter->SetString("Press Enter To Next Stage!");
		ReturnAllObj();
		if (InputMgr::GetKeyDown(sf::Keyboard::Enter))
		{
			switch (currentStage)
			{
			case Stages::Stage1:
				SetStage(Stages::Stage2);
				break;
			case Stages::Stage2:
				SetStage(Stages::Stage3);
				break;
			case Stages::Stage3:
				prevMode = currentMode;
				SCENE_MGR.ChangeScene(SceneIds::Boss1);
				break;
			}
			uiCenter->SetString("");
		}

		return;
	}


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

}

void SceneNormalGame::Draw(sf::RenderWindow& window)
{
	SceneGame::Draw(window);
}

void SceneNormalGame::SetStage(Stages stage)
{
	ReturnAllObj();
	vause->SetStatus(Vause::Status::Normal);
	mainBall = SpawnBall(vause->GetPosition());

	currentStage = stage;

	std::string key;
	switch (currentStage)
	{
	case Stages::Stage1:
		key = "Stage1";
		break;
	case Stages::Stage2:
		key = "Stage2";
		break;
	case Stages::Stage3:
		key = "Stage3";
		break;
	}
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

bool SceneNormalGame::isStageClear()
{
	for (int i = 0; i < bricksSize.x; i++)
	{
		for (int j = 0; j < bricksSize.y; j++)
		{
			if (!bricks[i][j]->IsBroken())
				return false;
		}
	}

	return true;
}

void SceneNormalGame::UpdateUi()
{
	SceneGame::UpdateUi();
	uiInGame->SetHighScore(normalHighScore);
}

void SceneNormalGame::SpawnItem(const sf::Vector2f& position)
{
	Item* item = itemPool.Take();
	activeItems.push_back(item);

	int rand = Utils::RandomRange(0, 1000);
	int cnt = 0;
	int weight = 0;

	int percentage[6] = { 750,100,50,50,25,25 };
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
	item->SetPosition(position);

	AddGo(item);
}