#include "stdafx.h"
#include "Boss.h"

Boss::Boss(const std::string& name)
	: GameObject(name)
{
}

void Boss::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
	body.setPosition(position);
}

void Boss::SetRotation(float angle)
{
	rotation = angle;
	body.setRotation(rotation);
}

void Boss::SetScale(const sf::Vector2f& s)
{
	scale = s;
	body.setScale(scale);
}

void Boss::SetOrigin(Origins preset)
{
	originPreset = preset;
	if (originPreset != Origins::Custom)
	{
		origin = Utils::SetOrigin(body, originPreset);
	}
}

void Boss::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
	origin = newOrigin;
	body.setOrigin(origin);
}

void Boss::Init()
{
	sortingLayer = SortingLayers::Foreground;
	sortingOrder = 1;
}

void Boss::Release()
{
}

void Boss::Reset()
{
	SetScale({ 5.5f,5.5f });


	animator.SetTarget(&body);
	animator.Play("animations/boss_spawn.json");
	animator.PlayQueue("animations/boss_idle.json");
	SetOrigin({ body.getLocalBounds().width * 0.5f, body.getLocalBounds().height * 0.8f });

	hitBox.UpdateBoss(body, body.getLocalBounds());
}

void Boss::Update(float dt)
{
	animator.Update(dt);
}

void Boss::Draw(sf::RenderWindow& window)
{
	window.draw(body);
	hitBox.Draw(window);
}

void Boss::OnHit()
{
	SOUND_MGR.PlaySfx("sounds/Arkanoid_boss_hit.wav");
	animator.Play("animations/boss_hit.json");
	animator.PlayQueue("animations/boss_idle.json");
	animator.SetSpeed(1.f);

	hp--;
}

void Boss::Attack()
{
	animator.Play("animations/boss_attack.json");
	animator.PlayQueue("animations/boss_idle.json");
	animator.SetSpeed(1.f);
}

void Boss::OnDie()
{
	animator.Play("animations/boss_spawn.json");
	animator.SetSpeed(-1.f);
}
