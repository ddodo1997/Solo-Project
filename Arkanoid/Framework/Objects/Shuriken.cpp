#include "stdafx.h"
#include "Shuriken.h"
#include "SceneGame.h"
#include "Boss.h"
#include "Vause.h"
#include "SceneBoss1.h"

Shuriken::Shuriken(const std::string& name)
	: GameObject(name)
{
}

void Shuriken::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
	body.setPosition(position);
}

void Shuriken::SetRotation(float angle)
{
	rotation = angle;
	body.setRotation(rotation);
}

void Shuriken::SetScale(const sf::Vector2f& s)
{
	scale = s;
	body.setScale(scale);
}

void Shuriken::SetOrigin(Origins preset)
{
	originPreset = preset;
	if (originPreset != Origins::Custom)
	{
		origin = Utils::SetOrigin(body, originPreset);
	}
}

void Shuriken::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
	origin = newOrigin;
	body.setOrigin(origin);
}

void Shuriken::Init()
{
	sortingLayer = SortingLayers::Foreground;
	sortingOrder = 1;
	animator.SetTarget(&body);
	body.setColor({0,144,248,255});
}

void Shuriken::Release()
{
}

void Shuriken::Reset()
{
	animator.Play("animations/Boss1/boss1_shuriken.json");
	boss = dynamic_cast<SceneGame*>(SCENE_MGR.GetCurrentScene())->GetBoss();
	vause = dynamic_cast<SceneGame*>(SCENE_MGR.GetCurrentScene())->GetVause();
	SetScale({ 3.f,3.f });
	SetOrigin(Origins::MC);
}

void Shuriken::Update(float dt)
{
	SetPosition(position + direction * speed * dt);
	animator.Update(dt);


	if (position.y >= 1000.f || position.x < -310.f || position.x > 300.f)
		dynamic_cast<SceneBoss1*>(SCENE_MGR.GetCurrentScene())->ReturnShuriken(this);
}

void Shuriken::FixedUpdate(float dt)
{
	if (vause != nullptr)
	{
		auto vauseBounds = vause->GetGlobalBounds();
		if (body.getGlobalBounds().intersects(vauseBounds) && !vause->IsInvincible())
		{
			vause->SetGameover(true);
			dynamic_cast<SceneBoss1*>(SCENE_MGR.GetCurrentScene())->ReturnShuriken(this);
		}
	}
}

void Shuriken::Draw(sf::RenderWindow& window)
{
	window.draw(body);
}

void Shuriken::Fire(sf::Vector2f targetPos)
{
	position = { boss->GetPosition().x, boss->GetPosition().y - 150.f};
	direction = Utils::GetNormal(targetPos - position);
}
