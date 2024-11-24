#include "stdafx.h"
#include "LavaBall.h"
#include "Vause.h"
#include "SceneGame.h"
#include "TileMap.h"
#include <SceneBoss2.h>
LavaBall::LavaBall(const std::string& name)
	: GameObject(name)
{
}

void LavaBall::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
	body.setPosition(position);
}

void LavaBall::SetRotation(float angle)
{
	rotation = angle;
	body.setRotation(rotation);
}

void LavaBall::SetScale(const sf::Vector2f& s)
{
	scale = s;
	body.setScale(scale);
}

void LavaBall::SetOrigin(Origins preset)
{
	originPreset = preset;
	if (originPreset != Origins::Custom)
	{
		origin = Utils::SetOrigin(body, originPreset);
	}
}

void LavaBall::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
	origin = newOrigin;
	body.setOrigin(origin);
}

void LavaBall::Init()
{
	sortingLayer = SortingLayers::Foreground;
	sortingOrder = 0;
}

void LavaBall::Release()
{
}

void LavaBall::Reset()
{
	sceneGame = dynamic_cast<SceneBoss2*>(SCENE_MGR.GetCurrentScene());
	vause = sceneGame->GetVause();
	animator.SetTarget(&body);
	animator.Play("animations/Boss2/boss2_lavaball.json");
	SetScale({ 2.f,2.f });
}

void LavaBall::Update(float dt)
{
	animator.Update(dt);
	TileMap* map = sceneGame->GetMap();
	sf::FloatRect mapBounds = map->GetGlobalBounds();
	sf::FloatRect movableBounds = {
		mapBounds.left,
		mapBounds.top,
		mapBounds.width + mapBounds.left,
		mapBounds.height + mapBounds.top
	};

	auto bossBounds = body.getGlobalBounds();

	if (position.x < movableBounds.left)
	{
		dynamic_cast<SceneBoss2*>(sceneGame)->ReturnLava(this);
	}
	else if (position.x > movableBounds.width)
	{
		dynamic_cast<SceneBoss2*>(sceneGame)->ReturnLava(this);
	}

	if (position.y < movableBounds.top)
	{
		dynamic_cast<SceneBoss2*>(sceneGame)->ReturnLava(this);
	}
	else if (position.y > movableBounds.height)
	{
		dynamic_cast<SceneBoss2*>(sceneGame)->ReturnLava(this);
	}




	velocity += gravity * dt;
	SetPosition(position + direction * velocity * dt);
	SetRotation(rotation + dt * 500);
}

void LavaBall::FixedUpdate(float dt)
{
	if (vause != nullptr)
	{
		auto vauseBounds = vause->GetGlobalBounds();
		if (body.getGlobalBounds().intersects(vauseBounds) && !vause->IsInvincible())
		{
			vause->SetGameover(true);
			dynamic_cast<SceneBoss2*>(SCENE_MGR.GetCurrentScene())->ReturnLava(this);
		}
	}
}

void LavaBall::Draw(sf::RenderWindow& window)
{
	window.draw(body);
}

void LavaBall::Scatter(sf::Vector2f pos)
{
	velocity = 300.f;
	SetPosition(pos);
	direction = Utils::GetNormal((Utils::RandomOnUnitCircle()));

	SetOrigin(Origins::MC);
}
