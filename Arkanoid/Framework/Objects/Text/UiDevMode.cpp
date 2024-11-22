#include "stdafx.h"
#include "UiDevMode.h"
#include "SceneGame.h"
#include "SceneNormalGame.h"
#include "SceneInfinity.h"
#include <SceneBoss.h>
UiDevMode::UiDevMode(const std::string& name)
	: GameObject(name)
{
}

void UiDevMode::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
}

void UiDevMode::SetRotation(float angle)
{
	rotation = angle;
}

void UiDevMode::SetScale(const sf::Vector2f& s)
{
	scale = s;
}

void UiDevMode::SetOrigin(Origins preset)
{
	originPreset = preset;
	if (originPreset != Origins::Custom)
	{

	}
}

void UiDevMode::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
}

void UiDevMode::Init()
{
	sortingLayer = SortingLayers::UI;
	sortingOrder = 0;
	for (int i = 0; i < (int)DevMenu::Count; i++)
	{
		sf::Text text;
		devTexts.push_back(text);
	}
}

void UiDevMode::Release()
{
}

void UiDevMode::Reset()
{
	switch (dynamic_cast<SceneGame*>(SCENE_MGR.GetCurrentScene())->GetCurrentMode())
	{
	case SceneGame::Mode::Normal:
		sceneGame = dynamic_cast<SceneNormalGame*>(SCENE_MGR.GetCurrentScene());
		break;
	case SceneGame::Mode::Infinity:
		sceneGame = dynamic_cast<SceneInfinity*>(SCENE_MGR.GetCurrentScene());
		break;
	case SceneGame::Mode::Boss:
		sceneGame = dynamic_cast<SceneBoss*>(SCENE_MGR.GetCurrentScene());
		break;
	}
	auto size = FRAMEWORK.GetWindowSizeF();
	auto& font = FONT_MGR.Get("fonts/DungGeunMo.ttf");
	for (int i = 0; i < (int)DevMenu::Count; i++)
	{
		devTexts[i].setFont(font);
		devTexts[i].setCharacterSize(100.f);
		devTexts[i].setFillColor(sf::Color::White);
		devTexts[i].setString(STRING_TABLE->Get("Dev" + std::to_string(i + 1)));
		devTexts[i].setPosition({ 0.f, 200 + i * 200.f });
	}
	SetActive(Variables::devMode);
}

void UiDevMode::Update(float dt)
{
}

void UiDevMode::FixedUpdate(float dt)
{
	if (sceneGame == nullptr)
		return;

	sf::Vector2f mousePos = sceneGame->ScreenToUi(InputMgr::GetMousePosition());


	for (int i = 0; i < (int)DevMenu::Count; i++)
	{
		if (devTexts[i].getGlobalBounds().contains(mousePos))
		{
			devTexts[i].setFillColor(sf::Color::Red);
		}
		else
		{
			devTexts[i].setFillColor(sf::Color::White);
		}

		if (InputMgr::GetMouseButtonDown(sf::Mouse::Left))
		{
			if (Utils::PointInTransformBounds(devTexts[i], devTexts[i].getLocalBounds(), mousePos))
			{
				sceneGame->OnUpgrade((DevMenu)i);
			}
		}
	}
}

void UiDevMode::Draw(sf::RenderWindow& window)
{
	for (int i = 0 ; i < (int)DevMenu::Count ; i++)
	{
		window.draw(devTexts[i]);
	}
}
