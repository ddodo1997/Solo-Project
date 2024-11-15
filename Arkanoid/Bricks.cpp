#include "stdafx.h"
#include "Bricks.h"

Bricks::Bricks(const std::string& name)
	: GameObject(name)
{
}

void Bricks::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
}

void Bricks::SetRotation(float angle)
{
	rotation = angle;
}

void Bricks::SetScale(const sf::Vector2f& s)
{
	scale = s;
}

void Bricks::SetOrigin(Origins preset)
{
	originPreset = preset;
	if (originPreset != Origins::Custom)
	{

	}
}

void Bricks::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
}

void Bricks::Init()
{
}

void Bricks::Release()
{
}

void Bricks::Reset()
{
}

void Bricks::Update(float dt)
{
}

void Bricks::Draw(sf::RenderWindow& window)
{
}
