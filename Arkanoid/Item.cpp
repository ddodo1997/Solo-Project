#include "stdafx.h"
#include "Item.h"
#include "SceneGame.h"
Item::Item(const std::string& name)
	: GameObject(name)
{
}

void Item::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
	body.setPosition(position);
}

void Item::SetRotation(float angle)
{
	rotation = angle;
	body.setRotation(rotation);
}

void Item::SetScale(const sf::Vector2f& s)
{
	scale = s;
	body.setScale(scale);
}

void Item::SetOrigin(Origins preset)
{
	originPreset = preset;
	if (originPreset != Origins::Custom)
	{
		origin = Utils::SetOrigin(body, originPreset);
	}
}

void Item::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
	origin = newOrigin;
	body.setOrigin(origin);
}

void Item::Init()
{
	sortingLayer = SortingLayers::Foreground;
	sortingOrder = 1;
	texture.loadFromFile(texId);
	body.setTexture(texture);
	animator.SetTarget(&body);
	SetScale({ 3.f,3.f });
	SetActive(false);
}

void Item::Release()
{
}

void Item::Reset()
{
}

void Item::Update(float dt)
{
	sf::Vector2f newPos = position + direction * speed * dt;

	if (newPos.y > 1080.f)
	{
		dynamic_cast<SceneGame*>(SCENE_MGR.GetCurrentScene())->ReturnItem(this);

	}

	SetPosition(position + direction * speed * dt);
	animator.Update(dt);
}

void Item::Draw(sf::RenderWindow& window)
{
	window.draw(body);
}

void Item::SetType(Types type)
{
	currentType = type;
	switch (currentType)
	{
	case Item::Types::Slow:
		animator.Play("animations/item_slow.json");
		break;
	case Item::Types::Catch:
		animator.Play("animations/item_catch.json");
		break;
	case Item::Types::Laser:
		animator.Play("animations/item_laser.json");
		break;
	case Item::Types::Enlarge:
		animator.Play("animations/item_enlarge.json");
		break;
	case Item::Types::Disruption:
		animator.Play("animations/item_disruption.json");
		break;
	case Item::Types::Player:
		animator.Play("animations/item_player.json");
		break;
	default:
		break;
	}
	SetActive(true);
}