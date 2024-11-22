#include "stdafx.h"
#include "UiFrame.h"
int UiFrame::FPS = 0;
UiFrame::UiFrame(const std::string& name)
	: GameObject(name)
{
}

void UiFrame::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
	textFrame.setPosition(position);
}

void UiFrame::SetRotation(float angle)
{
	rotation = angle;
	textFrame.setRotation(rotation);
}

void UiFrame::SetScale(const sf::Vector2f& s)
{
	scale = s;
	textFrame.setScale(scale);
}

void UiFrame::SetOrigin(Origins preset)
{
	originPreset = preset;
	if (originPreset != Origins::Custom)
	{
		origin = Utils::SetOrigin(textFrame, originPreset);
	}
}

void UiFrame::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
	origin = newOrigin;
	textFrame.setOrigin(origin);
}

void UiFrame::Init()
{
	sortingLayer = SortingLayers::UI;
	sortingOrder = 0;
}

void UiFrame::Release()
{
}

void UiFrame::Reset()
{
	auto size = FRAMEWORK.GetWindowSizeF();
	auto& otherFont = FONT_MGR.Get("fonts/DungGeunMo.ttf");
	textFrame.setFont(otherFont);
	textFrame.setCharacterSize(50.f);
	textFrame.setString(std::to_string(FPS));
	FPS = 0;
}

void UiFrame::Update(float dt)
{
	timer += dt;
	FPS++;
	if (timer >= 1.f)
	{
		textFrame.setString(std::to_string(FPS));
		FPS = 0;
		timer = 0.f;
	}
}

void UiFrame::Draw(sf::RenderWindow& window)
{
	if(Variables::devMode)
		window.draw(textFrame);
}
