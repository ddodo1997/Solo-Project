#include "stdafx.h"
#include "SceneInfinity.h"
#include "Vause.h"
#include "Bricks.h"
#include "UiCenter.h"
#include "UiInGame.h"
SceneInfinity::SceneInfinity() : SceneGame(SceneIds::Infinity)
{

}

void SceneInfinity::Init()
{
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

void SceneInfinity::Enter()
{
	SceneGame::Enter();	
	
	ReturnAllObj();
	vause->SetStatus(Vause::Status::Normal);
	mainBall = SpawnBall(vause->GetPosition());
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
		uiCenter->SetString("Press Enter To Restart...");
		if (InputMgr::GetKeyDown(sf::Keyboard::Enter))
		{
			SCENE_MGR.ChangeScene(SceneIds::Infinity);
			uiCenter->SetString("");
		}

		return;
	}

}

void SceneInfinity::Draw(sf::RenderWindow& window)
{
	SceneGame::Draw(window);
}

void SceneInfinity::UpdateUi()
{
	SceneGame::UpdateUi();
	uiInGame->SetHighScore(infinityHighScore);
}
