#include "stdafx.h"
#include "UiMain.h"

UiMain::UiMain(const std::string& name)
	: GameObject(name)
{
}

void UiMain::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
}

void UiMain::SetRotation(float angle)
{
	rotation = angle;
}

void UiMain::SetScale(const sf::Vector2f& s)
{
	scale = s;
}

void UiMain::SetOrigin(Origins preset)
{
	originPreset = preset;
	if (originPreset != Origins::Custom)
	{

	}
}

void UiMain::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
}

void UiMain::Init()
{
	sortingLayer = SortingLayers::UI;
	sortingOrder = 0;
}

void UiMain::Release()
{
}

void UiMain::Reset()
{
	auto size = FRAMEWORK.GetWindowSizeF();
	auto& otherFont = FONT_MGR.Get("fonts/DungGeunMo.ttf");
	auto& titleFont = FONT_MGR.Get("fonts/Arka_solid.ttf");
	txthighScore.setFont(otherFont);
	txtmainTitle.setFont(titleFont);
	txtstart.setFont(otherFont);
	txtExit.setFont(otherFont);
	txtArrow.setFont(otherFont);

	txthighScore.setString(STRING_TABLE->Get("HighScore"));
	txthighScore.setCharacterSize(50);
	Utils::SetOrigin(txthighScore, Origins::TC);
	txthighScore.setPosition({ size.x * 0.5f,0.f });

	txtmainTitle.setString(STRING_TABLE->Get("MainTitle"));
	txtmainTitle.setCharacterSize(150);
	Utils::SetOrigin(txtmainTitle, Origins::MC);
	txtmainTitle.setPosition({ size.x * 0.5f,size.y * 0.3f });
	txtmainTitle.setFillColor(sf::Color::Blue);
	txtmainTitle.setOutlineColor(sf::Color::Red);
	txtmainTitle.setOutlineThickness(3);

	txtstart.setString(STRING_TABLE->Get("Start"));
	txtstart.setCharacterSize(50);
	Utils::SetOrigin(txtstart, Origins::MC);
	txtstart.setPosition({ size.x * 0.5f,size.y * 0.8f });

	txtExit.setString(STRING_TABLE->Get("Exit"));
	txtExit.setCharacterSize(50);
	Utils::SetOrigin(txtExit, Origins::MC);
	txtExit.setPosition({ size.x * 0.5f,size.y * 0.85f });

	txtArrow.setString("->");
	txtArrow.setCharacterSize(50);
	Utils::SetOrigin(txtArrow, Origins::MC);
	txtArrow.setPosition({ txtstart.getPosition().x - 150, txtstart.getPosition().y });
}

void UiMain::Update(float dt)
{
	if(InputMgr::GetKeyDown(sf::Keyboard::Down) || InputMgr::GetKeyDown(sf::Keyboard::S))
	{
		txtArrow.setPosition({ txtExit.getPosition().x - 75, txtExit.getPosition().y });
		currentSelect = Select::Exit;
	}
	if (InputMgr::GetKeyDown(sf::Keyboard::Up) || InputMgr::GetKeyDown(sf::Keyboard::W))
	{
		txtArrow.setPosition({ txtstart.getPosition().x - 150, txtstart.getPosition().y });
		currentSelect = Select::Play;
	}

	if (InputMgr::GetKeyDown(sf::Keyboard::Enter))
	{
		switch (currentSelect)
		{
		case Select::Play:
			SCENE_MGR.ChangeScene(SceneIds::NormalGame);
			break;
		case Select::Exit:
			FRAMEWORK.GetWindow().close();
			break;
		}
	}
}

void UiMain::Draw(sf::RenderWindow& window)
{
	window.draw(txthighScore);
	window.draw(txtmainTitle);
	window.draw(txtstart);
	window.draw(txtExit);
	window.draw(txtArrow);
}
