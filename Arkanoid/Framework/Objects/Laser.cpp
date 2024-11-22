#include "stdafx.h"
#include "Laser.h"
#include "Vause.h"
#include "SceneGame.h"
#include "Bricks.h"
#include "Boss.h"
Laser::Laser(const std::string& name)
	: GameObject(name)
{
}

void Laser::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
	body.setPosition(position);
}

void Laser::SetRotation(float angle)
{
	rotation = angle;
	body.setRotation(rotation);
}

void Laser::SetScale(const sf::Vector2f& s)
{
	scale = s;
	body.setScale(scale);
}

void Laser::SetOrigin(Origins preset)
{
	originPreset = preset;
	if (originPreset != Origins::Custom)
	{
		origin = Utils::SetOrigin(body, originPreset);
	}
}

void Laser::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
	origin = newOrigin;
	body.setOrigin(origin);
}

void Laser::Init()
{
	sortingLayer = SortingLayers::Foreground;
	sortingOrder = -1;
	SetActive(false);
}

void Laser::Release()
{
}

void Laser::Reset()
{
	sceneGame = dynamic_cast<SceneGame*>(SCENE_MGR.GetCurrentScene());
	vause = sceneGame->GetVause();
	boss = sceneGame->GetBoss();
	body.setTexture(TEXTURE_MGR.Get(texId));

	body.setTextureRect(tex);

	SetPosition(vause->GetPosition());
	SetOrigin(Origins::BC);
	SetScale({ 3.f,3.f });
}

void Laser::Update(float dt)
{
	SetPosition(position + speed * direction * dt);
	if (position.y < -450.f)
	{
		isFire = false;
		SetActive(false);
	}
}

void Laser::FixedUpdate(float dt)
{
	if (sceneGame != nullptr)
	{
		auto& bricks = sceneGame->GetBricks();

		for (auto& vec : bricks)
		{
			for (auto brick : vec)
			{
				auto brickBound = brick->GetGlobalBounds();
				if (!brick->IsActive())
					continue;

				if (body.getGlobalBounds().intersects(brickBound))
				{
					brick->OnHit(damage);
					SetActive(false);
					isFire = false;
					break;
				}
			}
		}
	}

	if (boss != nullptr)
	{
		auto bossBounds = boss->GetHitBox().rect.getGlobalBounds();
		if (body.getGlobalBounds().intersects(bossBounds))
		{
			boss->OnHit(position,damage);
			SetActive(false);
			isFire = false;
		}
	}
}

void Laser::Draw(sf::RenderWindow& window)
{
	window.draw(body);
}

void Laser::Fire(const sf::Vector2f& position, float s)
{
	if (isFire)
		return;
	SOUND_MGR.PlaySfx("sounds/Arkanoid_laser.wav");
	SetPosition(position);
	speed = s;
	SetActive(true);
	isFire = true;
}
