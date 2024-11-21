#include "stdafx.h"
#include "UiInGame.h"
#include <SceneGame.h>

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

	
	extraLifeSprite.setTexture(TEXTURE_MGR.Get("graphics/vause_sheet.png"));
	extraLifeSprite.setTextureRect({ 176,0,32,8 });
	extraLifeSprite.setPosition(size.x * 0.26f, size.y * 0.94f);
	extraLifeSprite.setScale({ 2.f, 2.f });

	extraLifeText.setFont(font);
	extraLifeText.setPosition(size.x * 0.3f, size.y * 0.93f);
}

void UiInGame::Update(float dt)
{
}

void UiInGame::Draw(sf::RenderWindow& window)
{
	window.draw(txtscore);
	window.draw(txthighScore);
	if (dynamic_cast<SceneGame*>(SCENE_MGR.GetCurrentScene())->GetCurrentMode() == SceneGame::Mode::Infinity)
		return;
	window.draw(extraLifeSprite);
	window.draw(extraLifeText);
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

void UiInGame::SetWave(int wave)
{
	txtscore.setString(STRING_TABLE->Get("Wave") + std::to_string(wave));
	Utils::SetOrigin(txtscore, Origins::TC);
}

void UiInGame::SetBestRecord(int bestRecord)
{
	txthighScore.setString(STRING_TABLE->Get("BestRecord") + std::to_string(bestRecord));
	Utils::SetOrigin(txthighScore, Origins::TC);
}

void UiInGame::SetExtraLife(int life)
{
	auto size = FRAMEWORK.GetWindowSizeF();
	extraLifeText.setString("X " + std::to_string(life));
	Utils::SetOrigin(extraLifeSprite, Origins::BC);
	Utils::SetOrigin(extraLifeText, Origins::BC);
}