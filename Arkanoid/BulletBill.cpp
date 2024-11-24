#include "stdafx.h"
#include "BulletBill.h"
#include <SceneGame.h>
#include "Vause.h"
#include <SceneBoss2.h>

BulletBill::BulletBill(const std::string& name)
	: GameObject(name)
{
}

void BulletBill::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
	body.setPosition(position);
}

void BulletBill::SetRotation(float angle)
{
	rotation = angle;
	body.setRotation(rotation);
}

void BulletBill::SetScale(const sf::Vector2f& s)
{
	scale = s;
	body.setScale(scale);
}

void BulletBill::SetOrigin(Origins preset)
{
	originPreset = preset;
	if (originPreset != Origins::Custom)
	{
		origin = Utils::SetOrigin(body, originPreset);
	}
}

void BulletBill::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
	origin = newOrigin;
	body.setOrigin(origin);
}

void BulletBill::Init()
{
	sortingLayer = SortingLayers::Foreground;
	sortingOrder = 0;
}

void BulletBill::Release()
{
}

void BulletBill::Reset()
{
	vause = dynamic_cast<SceneGame*>(SCENE_MGR.GetCurrentScene())->GetVause();
	animator.SetTarget(&body);
	animator.Play("animations/Boss2/boss2_bullet_bill.json");
	SetOrigin(Origins::MC);
	SetScale({ 4.f,4.f });
}

void BulletBill::Update(float dt)
{
	SetPosition(position + direction * speed * dt);
	if(position.y >= 1000.f)
		dynamic_cast<SceneBoss2*>(SCENE_MGR.GetCurrentScene())->ReturnBill(this);
}

void BulletBill::FixedUpdate(float dt)
{
	if (vause != nullptr)
	{
		auto vauseBounds = vause->GetGlobalBounds();
		if (body.getGlobalBounds().intersects(vauseBounds) && !vause->IsInvincible())
		{
			vause->SetGameover(true);
			dynamic_cast<SceneBoss2*>(SCENE_MGR.GetCurrentScene())->ReturnBill(this);
		}
	}
}

void BulletBill::Draw(sf::RenderWindow& window)
{
	window.draw(body);
}

void BulletBill::Fire(sf::Vector2f pos)
{
	SetPosition(pos);
}
