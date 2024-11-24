#include "stdafx.h"
#include "SceneBoss.h"
#include "Vause.h"
#include "Ball.h"
#include "Boss.h"
#include "UiInGame.h"
#include "UiCenter.h"
SceneBoss::SceneBoss(SceneIds id) : SceneGame(id)
{
}

void SceneBoss::Init()
{
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

void SceneBoss::OnUpgrade(UiDevMode::DevMenu menu)
{
	SceneGame::OnUpgrade(menu);
	if (menu == UiDevMode::DevMenu::ClearUp)
		boss->OnHit({ 0.f,0.f }, 50);
}
