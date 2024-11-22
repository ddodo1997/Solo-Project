#include "stdafx.h"
#include "LavaRain.h"
#include "Vause.h"
#include "SceneBoss.h"
LavaRain::LavaRain(const std::string& name)
	: GameObject(name)
{
}

void LavaRain::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
	body.setPosition(position);
}

void LavaRain::SetRotation(float angle)
{
	rotation = angle;
	body.setRotation(rotation);
}

void LavaRain::SetScale(const sf::Vector2f& s)
{
	scale = s;
	body.setScale(scale);
}

void LavaRain::SetOrigin(Origins preset)
{
	originPreset = preset;
	if (originPreset != Origins::Custom)
	{
		origin = Utils::SetOrigin(body, originPreset);
	}
}

void LavaRain::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
	origin = newOrigin;
	body.setOrigin(origin);
}

void LavaRain::Init()
{
	sortingLayer = SortingLayers::Foreground;
	sortingOrder = 1;
	animator.SetTarget(&body);
	body.setColor(sf::Color::Yellow);
}

void LavaRain::Release()
{
}

void LavaRain::Reset()
{
	vause = dynamic_cast<SceneGame*>(SCENE_MGR.GetCurrentScene())->GetVause();
	animator.Play("animations/boss_rain.json");
	SetScale({ 2.f,2.f });
	SetOrigin(Origins::MC);
	SetPosition({ position.x, -450.f });

	velocity = 0.f;
}

void LavaRain::Update(float dt)
{
	animator.Update(dt);

	velocity += gravity * dt;
	SetPosition({position.x, position.y + velocity * dt });


	if (position.y >= 1000.f)
		dynamic_cast<SceneBoss*>(SCENE_MGR.GetCurrentScene())->ReturnRain(this);
}

void LavaRain::FixedUpdate(float dt)
{
	if (vause != nullptr)
	{
		auto vauseBounds = vause->GetGlobalBounds();
		if (body.getGlobalBounds().intersects(vauseBounds) && !vause->IsInvincible())
		{
			vause->SetGameover(true);
			dynamic_cast<SceneBoss*>(SCENE_MGR.GetCurrentScene())->ReturnRain(this);
		}
	}
}

void LavaRain::Draw(sf::RenderWindow& window)
{
	window.draw(body);
}

void LavaRain::Drop(float xPos)
{
	SetPosition({ xPos, position.y });
}
