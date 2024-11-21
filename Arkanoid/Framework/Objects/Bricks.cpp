#include "stdafx.h"
#include "Bricks.h"
#include "Item.h"
#include "SceneGame.h"
Bricks::Bricks(const std::string& name)
	: GameObject(name)
{
}

void Bricks::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
	body.setPosition(position);
}

void Bricks::SetRotation(float angle)
{
	rotation = angle;
	body.setRotation(rotation);
}

void Bricks::SetScale(const sf::Vector2f& s)
{
	scale = s;
	body.setScale(scale);
}

void Bricks::SetOrigin(Origins preset)
{
	originPreset = preset;
	if (originPreset != Origins::Custom)
	{
		origin = Utils::SetOrigin(body, originPreset);
	}
}

void Bricks::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
	origin = newOrigin;
	body.setOrigin(newOrigin);
}

void Bricks::Init()
{
	sortingLayer = SortingLayers::Foreground;
	sortingOrder = 0;
}

void Bricks::Release()
{
}

void Bricks::Reset()
{
	texture.loadFromFile(texId);
	body.setTexture(texture);
	SetScale({ 4.f,4.f });

	switch (currentType)
	{
	case Types::None:
	case Types::Super:
	case Types::Immotal:
		isBroken = true;
		break;
	default :
		isBroken = false;
	}
}

void Bricks::Update(float dt)
{
	if (animator)
	{
		animator.Update(dt);
	}

	hitBox.UpdateTr(body, body.getLocalBounds());
}

void Bricks::Draw(sf::RenderWindow& window)
{
	window.draw(body);
	hitBox.Draw(window);
}


void Bricks::SetType(Types type)
{
	animator.SetTarget(nullptr);
	currentType = type;
	isBroken = false;
	switch (currentType)
	{
	case Types::None:
	{
		auto& data = BRICKS_TABLE->Get("None");
		score = data.at("Score")[0];
		hp = data.at("HP")[0];
		body.setTextureRect({
			data.at("Position")[0],
			data.at("Position")[1],
			data.at("Position")[2],
			data.at("Position")[3]
			});
		isBroken = true;
		SetActive(false);
		return;
	}
	case Types::White:
	{
		auto& data = BRICKS_TABLE->Get("White");
		score = data.at("Score")[0];
		hp = data.at("HP")[0];
		body.setTextureRect({
			data.at("Position")[0],
			data.at("Position")[1],
			data.at("Position")[2],
			data.at("Position")[3]
			});
		break;
	}
	case Types::Orange:
	{
		auto& data = BRICKS_TABLE->Get("Orange");
		score = data.at("Score")[0];
		hp = data.at("HP")[0];
		body.setTextureRect({
			data.at("Position")[0],
			data.at("Position")[1],
			data.at("Position")[2],
			data.at("Position")[3]
			});
		break;
	}
	case Types::Sky:
	{
		auto& data = BRICKS_TABLE->Get("Sky");
		score = data.at("Score")[0];
		hp = data.at("HP")[0];
		body.setTextureRect({
			data.at("Position")[0],
			data.at("Position")[1],
			data.at("Position")[2],
			data.at("Position")[3]
			});
		break;
	}
	case Types::Green:
	{
		auto& data = BRICKS_TABLE->Get("Green");
		score = data.at("Score")[0];
		hp = data.at("HP")[0];
		body.setTextureRect({
			data.at("Position")[0],
			data.at("Position")[1],
			data.at("Position")[2],
			data.at("Position")[3]
			});
		break;
	}
	case Types::Red:
	{
		auto& data = BRICKS_TABLE->Get("Red");
		score = data.at("Score")[0];
		hp = data.at("HP")[0];
		body.setTextureRect({
			data.at("Position")[0],
			data.at("Position")[1],
			data.at("Position")[2],
			data.at("Position")[3]
			});
		break;
	}
	case Types::Blue:
	{
		auto& data = BRICKS_TABLE->Get("Blue");
		score = data.at("Score")[0];
		hp = data.at("HP")[0];
		body.setTextureRect({
			data.at("Position")[0],
			data.at("Position")[1],
			data.at("Position")[2],
			data.at("Position")[3]
			});
		break;
	}
	case Types::Pink:
	{
		auto& data = BRICKS_TABLE->Get("Pink");
		score = data.at("Score")[0];
		hp = data.at("HP")[0];
		body.setTextureRect({
			data.at("Position")[0],
			data.at("Position")[1],
			data.at("Position")[2],
			data.at("Position")[3]
			});
		break;
	}
	case Types::Yellow:
	{
		auto& data = BRICKS_TABLE->Get("Yello");
		score = data.at("Score")[0];
		hp = data.at("HP")[0];
		body.setTextureRect({
			data.at("Position")[0],
			data.at("Position")[1],
			data.at("Position")[2],
			data.at("Position")[3]
			});
		break;
	}
	case Types::Super:
	{
		auto& data = BRICKS_TABLE->Get("Super");
		score = data.at("Score")[0];
		hp = data.at("HP")[0];
		animator.SetTarget(&body);
		animator.Play("animations/super_brick.json");
		isBroken = true;
		break;
	}
	case Types::Immotal:
	{
		auto& data = BRICKS_TABLE->Get("Immotal");
		score = data.at("Score")[0];
		hp = data.at("HP")[0];
		animator.SetTarget(&body);
		animator.Play("animations/immotal_brick.json");
		isBroken = true;
		break;
	}
	}
	SetActive(true);
}

void Bricks::OnHit()
{
	if(animator)
	{
		switch (currentType)
		{
		case Types::Super:
			animator.Play("animations/super_brick.json");
			break;
		case Types::Immotal:
			animator.Play("animations/immotal_brick.json");
			break;
		}
		SOUND_MGR.PlaySfx("sounds/Arkanoid_super_brick.wav");
	}
	else {
		SOUND_MGR.PlaySfx("sounds/Arkanoid_brick.wav");
	}
	hp--;
	if (hp <= 0)
	{
		SetActive(false);
		isBroken = true;
		currentType = Types::None;
		dynamic_cast<SceneGame*>(SCENE_MGR.GetCurrentScene())->SpawnItem(position);
		dynamic_cast<SceneGame*>(SCENE_MGR.GetCurrentScene())->AddScore(score);
	}
}
