#include "stdafx.h"
#include "UiCenter.h"

UiCenter::UiCenter(const std::string& name)
	: GameObject(name)
{
}

void UiCenter::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
	txtCenter.setPosition(position);
}

void UiCenter::SetRotation(float angle)
{
	rotation = angle;
	txtCenter.setRotation(rotation);
}

void UiCenter::SetScale(const sf::Vector2f& s)
{
	scale = s;
	txtCenter.setScale(scale);
}

void UiCenter::SetOrigin(Origins preset)
{
	originPreset = preset;
	if (originPreset != Origins::Custom)
	{
		origin = Utils::SetOrigin(txtCenter, originPreset);
	}
}

void UiCenter::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
	origin = newOrigin;
	txtCenter.setOrigin(origin);
}

void UiCenter::Init()
{
	sortingLayer = SortingLayers::UI;
	sortingOrder = 1;
}

void UiCenter::Release()
{
}

void UiCenter::Reset()
{
	txtCenter.setFont(FONT_MGR.Get(fontId));
	auto size = FRAMEWORK.GetWindowSizeF();
	SetPosition({ size.x * 0.5f, size.y * 0.5f });
	txtCenter.setCharacterSize(100);
}

void UiCenter::Update(float dt)
{
}

void UiCenter::Draw(sf::RenderWindow& window)
{
	window.draw(txtCenter);
}

void UiCenter::SetString(std::string str)
{
	txtCenter.setString(str);
	SetOrigin(Origins::MC);
}
