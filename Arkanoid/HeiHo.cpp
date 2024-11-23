#include "stdafx.h"
#include "HeiHo.h"
#include "Vause.h"
#include <SceneBoss2.h>

HeiHo::HeiHo(const std::string& name)
	: GameObject(name)
{
}

void HeiHo::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
	body.setPosition(position);
}

void HeiHo::SetRotation(float angle)
{
	rotation = angle;
	body.setRotation(rotation);
}

void HeiHo::SetScale(const sf::Vector2f& s)
{
	scale = s;
	body.setScale(scale);
}

void HeiHo::SetOrigin(Origins preset)
{
	originPreset = preset;
	if (originPreset != Origins::Custom)
	{
		origin = Utils::SetOrigin(body, originPreset);
	}
}

void HeiHo::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
	origin = newOrigin;
	body.setOrigin(origin);
}

void HeiHo::Init()
{
	sortingLayer = SortingLayers::Foreground;
	sortingOrder = 0;
}

void HeiHo::Release()
{
}

void HeiHo::Reset()
{
	vause = dynamic_cast<SceneGame*>(SCENE_MGR.GetCurrentScene())->GetVause();
	animator.SetTarget(&body);
	SetScale({ 2.f,2.f });
}

void HeiHo::Update(float dt)
{
	SetRotation(rotation + dt * 300.f);

	velocity += gravity * dt;
	SetPosition({ position.x, position.y + velocity * dt });
	if (position.y >= 1000.f)
		dynamic_cast<SceneBoss2*>(SCENE_MGR.GetCurrentScene())->ReturnHeiHo(this);
}

void HeiHo::FixedUpdate(float dt)
{
	if (vause != nullptr)
	{
		auto vauseBounds = vause->GetGlobalBounds();
		if (body.getGlobalBounds().intersects(vauseBounds) && !vause->IsInvincible())
		{
			vause->SetGameover(true);
			dynamic_cast<SceneBoss2*>(SCENE_MGR.GetCurrentScene())->ReturnHeiHo(this);
		}
	}
}

void HeiHo::Draw(sf::RenderWindow& window)
{
	window.draw(body);
	hitBox.Draw(window);
}

void HeiHo::Drop(sf::Vector2f pos, char flag)
{
	velocity = 0.f;
	SetPosition(pos);
	switch (flag)
	{
	case 1:
		animator.Play("animations/Boss2/boss2_attack_heiho_red.json");
		break;
	case 2:
		animator.Play("animations/Boss2/boss2_attack_heiho_yellow.json");
		break;
	case 3:
		animator.Play("animations/Boss2/boss2_attack_heiho_green.json");
		break;
	}
	SetOrigin(Origins::MC);
}
