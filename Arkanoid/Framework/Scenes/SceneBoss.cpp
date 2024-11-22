#include "stdafx.h"
#include "SceneBoss.h"
#include "Vause.h"
#include "Ball.h"
#include "Boss.h"
#include "Shuriken.h"
#include "LavaRain.h"
#include "FireBall.h"
#include "UiInGame.h"
#include "UiCenter.h"
SceneBoss::SceneBoss() : SceneGame(SceneIds::Boss)
{
	currentMode = Mode::Boss;
}

void SceneBoss::Init()
{
	boss = AddGo(new Boss("Boss"));
	fire = AddGo(new FireBall("FireBall"));
	SceneGame::Init();
}


void SceneBoss::Enter()
{
	SceneGame::Enter();	
	
	ReturnAllObj();
	vause->SetStatus(Vause::Status::Normal);
	mainBall = SpawnBall(vause->GetPosition());
	uiCenter->SetString("");
}

void SceneBoss::Exit()
{
	ReturnAllObj();

	SceneGame::Exit();
}

void SceneBoss::Update(float dt)
{
	SceneGame::Update(dt);
	if (vause->IsGameover())
	{
		ReturnAllObj();
		uiCenter->SetString("Press Enter To Main...");
		if (InputMgr::GetKeyDown(sf::Keyboard::Enter))
		{
			SCENE_MGR.ChangeScene(SceneIds::Main);
			uiCenter->SetString("");
		}

		return;
	}


	if (boss->isDie())
	{
		ReturnAllObj();
		uiCenter->SetString("Congratulations!");
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

	int percentage[6] = { 901,0,33,0,33,33 };
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


Shuriken* SceneBoss::SpawnShuriken()
{
	Shuriken* shuriken = shurikenPool.Take();
	activeShurikens.push_back(shuriken);

	return AddGo(shuriken);
}

void SceneBoss::ReturnShuriken(Shuriken* shuriken)
{
	RemoveGo(shuriken);
	shurikenPool.Return(shuriken);
	activeShurikens.remove(shuriken);
}

void SceneBoss::FireShuriken()
{
	SpawnShuriken()->Fire(vause->GetPosition());
}

LavaRain* SceneBoss::SpawnRain()
{
	LavaRain* rain = rainPool.Take();
	activeRains.push_back(rain);
	return AddGo(rain);
}

void SceneBoss::ReturnRain(LavaRain* rain)
{
	RemoveGo(rain);
	rainPool.Return(rain);
	activeRains.remove(rain);
}

void SceneBoss::RainDrop()
{
	SpawnRain()->Drop(Utils::RandomRange(-280.f, 280.f));
}

void SceneBoss::ReturnAllObj()
{
	SceneGame::ReturnAllObj();
	for (auto& shuriken : activeShurikens)
	{
		RemoveGo(shuriken);
		shurikenPool.Return(shuriken);
	}
	activeShurikens.clear();

	for (auto& rain : activeRains)
	{
		RemoveGo(rain);
		rainPool.Return(rain);
	}
	activeRains.clear();
}

void SceneBoss::ShootFireBall()
{
	fire->Shoot(boss->GetTargetPos());
}

void SceneBoss::OnUpgrade(UiDevMode::DevMenu menu)
{
	SceneGame::OnUpgrade(menu);
	if (menu == UiDevMode::DevMenu::ClearUp)
		boss->OnHit({ 0.f,0.f }, 50);
}
