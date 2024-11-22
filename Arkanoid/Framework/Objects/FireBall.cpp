#include "stdafx.h"
#include "FireBall.h"
#include "SceneGame.h"
#include "SceneBoss.h"
#include "Boss.h"
#include "Vause.h"
FireBall::FireBall(const std::string& name)
	: GameObject(name)
{
}

void FireBall::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
	body.setPosition(position);
}

void FireBall::SetRotation(float angle)
{
	rotation = angle;
	body.setRotation(rotation);
}

void FireBall::SetScale(const sf::Vector2f& s)
{
	scale = s;
	body.setScale(scale);
}

void FireBall::SetOrigin(Origins preset)
{
	originPreset = preset;
	if (originPreset != Origins::Custom)
	{
		origin = Utils::SetOrigin(body, originPreset);
	}
}

void FireBall::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
	origin = newOrigin;
	body.setOrigin(origin);
}

void FireBall::Init()
{
	sortingLayer = SortingLayers::Foreground;
	sortingOrder = 1;
	animator.SetTarget(&body);
}

void FireBall::Release()
{
}

void FireBall::Reset()
{
	boss = dynamic_cast<SceneBoss*>(SCENE_MGR.GetCurrentScene())->GetBoss();
	vause = dynamic_cast<SceneGame*>(SCENE_MGR.GetCurrentScene())->GetVause();
	animator.Play("animations/boss_fire.json");
	SetScale({ 2.f,2.f });
	SetActive(false);
}

void FireBall::Update(float dt)
{
	animator.Update(dt);
	SetPosition(position + direction * speed * dt);

	if (position.y >= 1000.f || position.x < -310.f || position.x > 300.f)
		SetActive(false);
}

void FireBall::FixedUpdate(float dt)
{
	if (vause != nullptr)
	{
		auto vauseBounds = vause->GetGlobalBounds();
		if (body.getGlobalBounds().intersects(vauseBounds) && !vause->IsInvincible())
		{
			vause->SetGameover(true);
			SetActive(false);
		}
	}
}

void FireBall::Draw(sf::RenderWindow& window)
{
	window.draw(body);
}

void FireBall::Shoot(sf::Vector2f targetDirection)
{
	position = { boss->GetPosition().x, boss->GetPosition().y - 150.f };
	direction = Utils::GetNormal(targetDirection - position);
	SetActive(true);
}
