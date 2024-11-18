#include "stdafx.h"
#include "Vause.h"
#include "TileMap.h"
#include "SceneGame.h"
#include "Ball.h"
Vause::Vause(const std::string& name)
	: GameObject(name)
{
}

void Vause::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
	body.setPosition(position);
}

void Vause::SetRotation(float angle)
{
	rotation = angle;
	body.setRotation(rotation);
}

void Vause::SetScale(const sf::Vector2f& s)
{
	scale = s;
	body.setScale(scale);
}

void Vause::SetOrigin(Origins preset)
{
	originPreset = preset;
	if (originPreset != Origins::Custom)
	{
		origin = Utils::SetOrigin(body, originPreset);
	}
}

void Vause::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
	origin = newOrigin;
	body.setOrigin(origin);
}

sf::FloatRect Vause::GetLocalBounds() const
{
	return body.getLocalBounds();
}

sf::FloatRect Vause::GetGlobalBounds() const
{
	return body.getGlobalBounds();
}

void Vause::ChangeAni(const std::string& id, const std::string& nextId)
{
	auto windowSize = FRAMEWORK.GetWindowSizeF();

	animator.Play(id);
	if (nextId != "")
		animator.PlayQueue(nextId);
	SetOrigin(Origins::TC);

	TileMap* map = sceneGame->GetMap();
	sf::FloatRect mapBounds = map->GetGlobalBounds();

	minX = mapBounds.left + body.getLocalBounds().width;
	maxX = mapBounds.width + mapBounds.left - body.getLocalBounds().width;
}

void Vause::Init()
{
	SetScale({ 2.f,2.f });
	sortingLayer = SortingLayers::Foreground;
	sortingOrder = 0;
	animator.SetTarget(&body);
	SetOrigin(Origins::TC);
}

void Vause::Release()
{
}

void Vause::Reset()
{
	sceneGame = dynamic_cast<SceneGame*>(SCENE_MGR.GetCurrentScene());
	ChangeAni("animations/vause_spawn.json", "animations/vause_idle.json");
	direction = { 0.f,0.f };
	Utils::SetOrigin(body, Origins::TC);
	SetPosition({ 0.f,400.f });

	isGameover = false;
	enlargeTimer = 0.f;
	laserTimer = 0.f;
	lasers = sceneGame->GetLaser();
}

void Vause::Update(float dt)
{
	direction.x = InputMgr::GetAxis(Axis::Horizontal);

	auto newPos = position + direction * speed * dt;
	newPos.x = Utils::Clamp(newPos.x, minX, maxX);

	SetPosition(newPos);

	switch (currentStatus)
	{
	case Status::Enlarge:
		UpdateEnlarge(dt);
		break;
	case Status::Laser:
		UpdateLaser(dt);
		break;
	}

	animator.Update(dt);
	hitBox.UpdateTr(body, body.getLocalBounds());
}

void Vause::UpdateEnlarge(float dt)
{
	enlargeTimer += dt;
	if (enlargeDelay <= enlargeTimer)
	{
		enlargeTimer = 0.f;
		SetStatus(Status::Normal);
	}
}

void Vause::UpdateLaser(float dt)
{
	laserTimer += dt;
	if (laserDelay <= laserTimer)
	{
		laserTimer = 0.f;
		SetStatus(Status::Normal);
	}

	if (InputMgr::GetKeyDown(sf::Keyboard::Space) && sceneGame->GetMainBall()->isMove())
	{
		auto vauseBounds = GetGlobalBounds();

		lasers[(int)Laser::Direction::Left]->Fire({vauseBounds.left, vauseBounds.top},600.f);
		lasers[(int)Laser::Direction::Right]->Fire({vauseBounds.width + vauseBounds.left, vauseBounds.top }, 600.f);
	}
}

void Vause::SetStatus(Status stat)
{
	enlargeTimer = 0.f;
	laserTimer = 0.f;
	prevStatus = currentStatus;
	currentStatus = stat;
	switch (currentStatus)
	{
	case Status::Normal:
		if (prevStatus != Status::Normal)
			ChangeAni("animations/vause_idle.json");
		break;
	case Status::Laser:
		if (prevStatus != Status::Laser)
			ChangeAni("animations/vause_formchange.json", "animations/vause_attackformidle.json");
		break;
	case Status::Enlarge:
		if (prevStatus != Status::Enlarge)
			ChangeAni("animations/longvause_idle.json");
		break;
	}
}

void Vause::FixedUpdate(float dt)
{
	auto& list = sceneGame->GetActiveItems();
	if (list.empty())
		return;

	for (auto& item : list)
	{
		auto itemBounds = item->GetGlobalBounds();
		if (body.getGlobalBounds().intersects(itemBounds))
		{
			OnPickupItem(item->GetType());
			sceneGame->ReturnItem(item);
			break;
		}
	}
}

void Vause::Draw(sf::RenderWindow& window)
{
	window.draw(body);
	hitBox.Draw(window);
}

void Vause::OnPickupItem(Item::Types type)
{
	switch (type)
	{
	case Item::Types::Slow:
		for (auto& ball : sceneGame->GetActiveBall())
		{
			ball->SetSlow();
			ball->SetSlowTimer(0.f);
		}
		break;
	case Item::Types::Laser:
		SetStatus(Status::Laser);
		break;
	case Item::Types::Enlarge:
		SetStatus(Status::Enlarge);
		break;
	case Item::Types::Disruption:
	{
		auto& list = sceneGame->GetActiveBall();
		int size = list.size();
		auto it = list.begin();

		for (int i = 0; i < size; i++)
		{
			if ((*it)->isMove())
			{
				float speed = 500.f;
				auto disruptionBall1 = sceneGame->SpawnBall((*it)->GetPosition(), true);
				auto disruptionBall2 = sceneGame->SpawnBall((*it)->GetPosition(), true);

				if ((*it)->IsSlow())
				{
					speed = 100.f;
					disruptionBall1->SetSlowTimer((*it)->GetSlowTimer());
					disruptionBall1->SetSlow();
					disruptionBall2->SetSlowTimer((*it)->GetSlowTimer());
					disruptionBall2->SetSlow();
				}

				auto rand1 = Utils::RandomOnUnitCircle(Utils::DegreeToRadian(45.f));
				auto rand2 = Utils::RandomOnUnitCircle(Utils::DegreeToRadian(45.f));
				// y 성분을 강조하여 수직 방향을 선호하도록 함 (필요에 따라 조절)


				rand1.y *= 1.1f;
				rand2.y *= -1.1f;

				float dirMagnitude = Utils::Magnitude(rand1);
				if (dirMagnitude > 1.f)
				{
					Utils::Normailize(rand1);
				}
				 dirMagnitude = Utils::Magnitude(rand2);
				if (dirMagnitude > 1.f)
				{
					Utils::Normailize(rand2);
				}

				Utils::Normailize(rand1);
				Utils::Normailize(rand2);

				disruptionBall1->Fire(rand1, speed);
				disruptionBall2->Fire(rand2, speed);
				it++;
			}
		}
		break;
	}
	case Item::Types::Player:
		life++;
		break;
	}
}
