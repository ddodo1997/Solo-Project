#include "stdafx.h"
#include "UiInGame.h"

UiInGame::UiInGame(const std::string& name)
	: GameObject(name)
{
}

void UiInGame::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
}

void UiInGame::SetRotation(float angle)
{
	rotation = angle;
}

void UiInGame::SetScale(const sf::Vector2f& s)
{
	scale = s;
}

void UiInGame::SetOrigin(Origins preset)
{
	originPreset = preset;
	if (originPreset != Origins::Custom)
	{

	}
}

void UiInGame::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
}

void UiInGame::Init()
{
	sortingLayer = SortingLayers::UI;
	sortingOrder = 0;

}

void UiInGame::Release()
{
}

void UiInGame::Reset()
{
	auto size = FRAMEWORK.GetWindowSizeF();
	auto& font = FONT_MGR.Get("fonts/DungGeunMo.ttf");

	txthighScore.setFont(font);
	txthighScore.setCharacterSize(50);
	txthighScore.setPosition({ size.x * 0.8f,0.f });


	txtscore.setFont(font);
	txtscore.setPosition({ size.x * 0.25f, 0.f });
	txtscore.setCharacterSize(50);
}

void UiInGame::Update(float dt)
{
}

void UiInGame::Draw(sf::RenderWindow& window)
{
	window.draw(txtscore);
	window.draw(txthighScore);
}

void UiInGame::SetScore(int score)
{
	txtscore.setString(STRING_TABLE->Get("Score") + std::to_string(score));
	Utils::SetOrigin(txtscore, Origins::TC);
}

void UiInGame::SetHighScore(int highScore)
{
	txthighScore.setString(STRING_TABLE->Get("HighScore") + std::to_string(highScore));
	Utils::SetOrigin(txthighScore, Origins::TC);
}
