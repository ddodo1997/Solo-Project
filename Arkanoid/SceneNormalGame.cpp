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
				SetStage(Stages::Stage1);
				break;
			}
			uiCenter->SetString("");
		}

		return;
	}


	SceneGame::Update(dt);

	if (vause->IsGameover())
	{
		uiCenter->SetString("Press Enter To Restart...");
		if (InputMgr::GetKeyDown(sf::Keyboard::Enter))
		{
			SCENE_MGR.ChangeScene(SceneIds::NormalGame);
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
