#include "stdafx.h"
#include "Boss2.h"
#include "Bricks.h"
#include "VauseFire.h"
#include "HeiHo.h"
#include "LavaBall.h"
#include "BulletBill.h"
#include "SceneBoss2.h"
#include "UiCenter.h"

SceneBoss2::SceneBoss2():SceneBoss(SceneIds::Boss2)
{
	currentMode = Mode::Boss2;
}

void SceneBoss2::Init()
{
	boss = AddGo(new Boss2("Boss2"));
	InitBricks();
	SceneBoss::Init();
}

void SceneBoss2::InitBricks()
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

void SceneBoss2::Enter()
{
	SceneBoss::Enter(); 
	SetStage();
}

void SceneBoss2::SetStage()
{
	for (int i = 0; i < bricksSize.x; i++)
	{
		for (int j = 0; j < bricksSize.y; j++)
		{
			bricks[i][j]->SetType((Bricks::Types)9);
			auto size = bricks[i][j]->GetLocalBounds();
			auto scale = bricks[i][j]->GetScale();
			bricks[i][j]->SetPosition({ -320.f + j * size.width * scale.x, 0 });
		}
	}
}

void SceneBoss2::Exit()
{
	ReturnAllObj();
	SceneBoss::Exit();
}

void SceneBoss2::Update(float dt)
{
	SceneBoss::Update(dt);	
	if (boss->isDie())
	{
		ReturnAllObj();
		uiCenter->SetString("Congratulations!");
		if (InputMgr::GetKeyDown(sf::Keyboard::Enter))
		{
			SCENE_MGR.ChangeScene(SceneIds::Main);
		}
	}
	if (shaking)
		ViewShake(0.5f,dt);
}

void SceneBoss2::Draw(sf::RenderWindow& window)
{
	SceneBoss::Draw(window);
}

void SceneBoss2::UpdateUi()
{
	SceneBoss::UpdateUi();
}

void SceneBoss2::ViewShake(float duration, float dt)
{
	static float timer = 0.f;
	if (timer < duration) {
		float offsetX = Utils::RandomRange(-15,15) *  300.f * dt;
		float offsetY = Utils::RandomRange(-0.5f, 0.f) *  300.f * dt;

		worldView.move(offsetX, offsetY);

		timer += dt;
	}
	else {
		timer = 0.f;
		worldView.setCenter(0.f, 0.f);
		shaking = false;
	}
}

void SceneBoss2::ReturnAllObj()
{
	SceneBoss::ReturnAllObj();
	for (auto fire : activeVauseFire)
	{
		RemoveGo(fire);
		vauseFirePool.Return(fire);
	}
	activeVauseFire.clear();

	for (auto heiho : activeHeiHo)
	{
		RemoveGo(heiho);
		heiHoPool.Return(heiho);
	}
	activeHeiHo.clear();

	for (auto lava : activeLava)
	{
		RemoveGo(lava);
		lavaPool.Return(lava);
	}
	activeLava.clear();

	for (auto bill : activeBill)
	{
		RemoveGo(bill);
		billPool.Return(bill);
	}
	activeBill.clear();
}

VauseFire* SceneBoss2::SpawnVauseFire()
{
	VauseFire* vauseFire = vauseFirePool.Take();
	activeVauseFire.push_back(vauseFire);
	return AddGo(vauseFire);
}

void SceneBoss2::ReturnVauseFire(VauseFire* val)
{
	RemoveGo(val);
	vauseFirePool.Return(val);
	activeVauseFire.remove(val);
}

HeiHo* SceneBoss2::SpawnHeiHo()
{
	HeiHo* heiho = heiHoPool.Take();
	activeHeiHo.push_back(heiho);
	return AddGo(heiho);
}

void SceneBoss2::ReturnHeiHo(HeiHo* val)
{
	RemoveGo(val);
	heiHoPool.Return(val);
	activeHeiHo.remove(val);
}

LavaBall* SceneBoss2::SpawnLava()
{
	LavaBall* lava = lavaPool.Take();
	activeLava.push_back(lava);
	return AddGo(lava);
}

void SceneBoss2::ReturnLava(LavaBall* val)
{
	RemoveGo(val);
	lavaPool.Return(val);
	activeLava.remove(val);
}

BulletBill* SceneBoss2::SpawnBill()
{
	BulletBill* bill = billPool.Take();
	activeBill.push_back(bill);
	return AddGo(bill);
}

void SceneBoss2::ReturnBill(BulletBill* val)
{
	RemoveGo(val);
	billPool.Return(val);
	activeBill.remove(val);
}
