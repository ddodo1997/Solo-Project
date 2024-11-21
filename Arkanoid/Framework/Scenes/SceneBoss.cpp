#include "stdafx.h"
#include "SceneBoss.h"
#include "Vause.h"
#include "Ball.h"
#include "Boss.h"
#include "UiInGame.h"
SceneBoss::SceneBoss() : SceneGame(SceneIds::Boss)
{
	currentMode = Mode::Boss;
}

void SceneBoss::Init()
{
	boss = AddGo(new Boss("Boss"));
	SceneGame::Init();
}


void SceneBoss::Enter()
{
	SceneGame::Enter();	
	
	ReturnAllObj();
	vause->SetStatus(Vause::Status::Normal);
	mainBall = SpawnBall(vause->GetPosition());
}

void SceneBoss::Exit()
{
	SceneGame::Exit();
}

void SceneBoss::Update(float dt)
{
	SceneGame::Update(dt);

	if (InputMgr::GetKeyDown(sf::Keyboard::Num1))
	{
		boss->OnHit();
	}
	if (InputMgr::GetKeyDown(sf::Keyboard::Num2))
	{
		boss->Attack();
	}
	if (InputMgr::GetKeyDown(sf::Keyboard::Num3))
	{
		boss->OnDie();
	}
}

void SceneBoss::Draw(sf::RenderWindow& window)
{
	SceneGame::Draw(window);
}

bool SceneBoss::isStageClear()
{
	return boss->isDie();
}

void SceneBoss::UpdateUi()
{
	SceneGame::UpdateUi();
	uiInGame->SetHighScore(normalHighScore);
}

void SceneBoss::SpawnItem(const sf::Vector2f& position)
{
	Item* item = itemPool.Take();
	activeItems.push_back(item);

	int rand = Utils::RandomRange(0, 1000);
	int cnt = 0;
	int weight = 0;

	int percentage[6] = { 600,0,100,100,100,100 };
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
