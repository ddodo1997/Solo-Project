#include "stdafx.h"
#include "VauseFire.h"
#include <SceneBoss2.h>
#include "Boss2.h"

VauseFire::VauseFire(const std::string& name)
	: GameObject(name)
{
}

void VauseFire::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
	body.setPosition(position);
}

void VauseFire::SetRotation(float angle)
{
	rotation = angle;
	body.setRotation(rotation);
}

void VauseFire::SetScale(const sf::Vector2f& s)
{
	scale = s;
	body.setScale(scale);
}

void VauseFire::SetOrigin(Origins preset)
{
	originPreset = preset;
	if (originPreset != Origins::Custom)
	{
		origin = Utils::SetOrigin(body, originPreset);
	}
}

void VauseFire::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
	origin = newOrigin;
	body.setOrigin(origin);
}

void VauseFire::Init()
{
	sortingLayer = SortingLayers::Foreground;
	sortingOrder = -2;
}

void VauseFire::Release()
{
}

void VauseFire::Reset()
{
	sceneGame = dynamic_cast<SceneBoss2*>(SCENE_MGR.GetCurrentScene());
	boss = sceneGame->GetBoss();
	animator.SetTarget(&body);
	animator.Play("animations/Boss2/vause_attack_fireball.json");
	SetOrigin(Origins::BL);
	SetScale({ 3.f,3.f });
}

void VauseFire::Update(float dt)
{
	SetPosition(position + direction * speed * dt);

	if (position.y <= -415.f)
	{
		dynamic_cast<SceneBoss2*>(sceneGame)->ReturnVauseFire(this);
	}
}

void VauseFire::FixedUpdate(float dt)
{
	if (sceneGame != nullptr)
	{
		auto bossBounds = boss->GetHitBox().rect.getGlobalBounds();
		if (body.getGlobalBounds().intersects(bossBounds))
		{
			boss->OnHit(position, damage);
			dynamic_cast<SceneBoss2*>(sceneGame)->ReturnVauseFire(this);
		}
	}
}

void VauseFire::Draw(sf::RenderWindow& window)
{
	window.draw(body);
}
