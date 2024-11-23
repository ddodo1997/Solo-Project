#include "stdafx.h"
#include "SceneBoss1.h"
#include "Boss1.h"
#include "Shuriken.h"
#include "LavaRain.h"
#include "FireBall.h"
#include "Vause.h"
#include "Ball.h"
#include "UiCenter.h"
SceneBoss1::SceneBoss1() : SceneBoss(SceneIds::Boss1)
{
	currentMode = Mode::Boss1;
}

void SceneBoss1::Init()
{
	boss = AddGo(new Boss1("Boss1"));
	fire = AddGo(new FireBall("FireBall"));
	SceneBoss::Init();
}

void SceneBoss1::Enter()
{
	SceneBoss::Enter();
}

void SceneBoss1::Exit()
{
	SceneBoss::Exit();
}

void SceneBoss1::Update(float dt)
{
	SceneBoss::Update(dt);	
	
	if (boss->isDie())
	{
		ReturnAllObj();
		uiCenter->SetString("Congratulations!");
	}
}

void SceneBoss1::Draw(sf::RenderWindow& window)
{
	SceneBoss::Draw(window);
}

void SceneBoss1::UpdateUi()
{
	SceneBoss::UpdateUi();
}

Shuriken* SceneBoss1::SpawnShuriken()
{
	Shuriken* shuriken = shurikenPool.Take();
	activeShurikens.push_back(shuriken);

	return AddGo(shuriken);
}

void SceneBoss1::ReturnShuriken(Shuriken* shuriken)
{
	RemoveGo(shuriken);
	shurikenPool.Return(shuriken);
	activeShurikens.remove(shuriken);
}

void SceneBoss1::FireShuriken()
{
	SpawnShuriken()->Fire(vause->GetPosition());
}

LavaRain* SceneBoss1::SpawnRain()
{
	LavaRain* rain = rainPool.Take();
	activeRains.push_back(rain);
	return AddGo(rain);
}

void SceneBoss1::ReturnRain(LavaRain* rain)
{
	RemoveGo(rain);
	rainPool.Return(rain);
	activeRains.remove(rain);
}

void SceneBoss1::RainDrop()
{
	SpawnRain()->Drop(Utils::RandomRange(-280.f, 280.f));
}

void SceneBoss1::ReturnAllObj()
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

void SceneBoss1::ShootFireBall()
{
	fire->Shoot(dynamic_cast<Boss1*>(boss)->GetTargetPos());
}