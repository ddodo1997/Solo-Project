#include "stdafx.h"
#include "Boss.h"
#include <SceneBoss.h>
#include "Shuriken.h"
#include "Vause.h"
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
	sortingOrder = -3;
}

void Boss::Release()
{

}

void Boss::Reset()
{
	sceneGame = dynamic_cast<SceneGame*>(SCENE_MGR.GetCurrentScene());

	animator.SetTarget(&body);
	hp = 50;
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

void Boss::OnHit(sf::Vector2f pos, int damage)
{
	sceneGame->SpawnItem(pos);
	SOUND_MGR.PlaySfx("sounds/Arkanoid_boss_hit.wav");
	hp -= damage;
}