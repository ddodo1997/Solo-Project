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
	SetScale({ 4.f,4.f });
}

void Bricks::Release()
{
}

void Bricks::Reset()
{
	texture.loadFromFile(texId);
	body.setTexture(texture);
}

void Bricks::Update(float dt)
{
	if (animator)
	{
		animator.Update(dt);
		flickeringTimer += dt;
		if (flickeringDelay < flickeringTimer)
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
			flickeringTimer = 0.f;
		}
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
	currentType = type;

	switch (currentType)
	{
	case Types::None:
		SetActive(false);
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
		break;
	}
	case Types::Immotal:
	{
		auto& data = BRICKS_TABLE->Get("Immotal");
		score = data.at("Score")[0];
		hp = data.at("HP")[0];
		animator.SetTarget(&body);
		animator.Play("animations/immotal_brick.json");
		break;
	}
	}
}

void Bricks::OnHit()
{
	hp--;
	if (hp <= 0)
	{
		SetActive(false);
		
		dynamic_cast<SceneGame*>(SCENE_MGR.GetCurrentScene())->SpawnItem(position);
	}
}
