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
	txtDev.setFont(otherFont);
	txtmainTitle.setFont(titleFont);
	txtNormal.setFont(otherFont);
	txtInfinity.setFont(otherFont);
	txtBoss.setFont(otherFont);
	txtExit.setFont(otherFont);
	txtArrow.setFont(otherFont);

	txtDev.setString(STRING_TABLE->Get("Who"));
	txtDev.setCharacterSize(50);
	Utils::SetOrigin(txtDev, Origins::TC);
	txtDev.setPosition({ size.x * 0.5f,0.f });

	txtmainTitle.setString(STRING_TABLE->Get("MainTitle"));
	txtmainTitle.setCharacterSize(150);
	Utils::SetOrigin(txtmainTitle, Origins::MC);
	txtmainTitle.setPosition({ size.x * 0.5f,size.y * 0.3f });
	txtmainTitle.setFillColor(sf::Color::Blue);
	txtmainTitle.setOutlineColor(sf::Color::Red);
	txtmainTitle.setOutlineThickness(3);

	txtNormal.setString(STRING_TABLE->Get("Normal"));
	txtNormal.setCharacterSize(50);
	Utils::SetOrigin(txtNormal, Origins::MC);
	txtNormal.setPosition({ size.x * 0.5f,size.y * 0.65f });


	txtInfinity.setString(STRING_TABLE->Get("Infinity"));
	txtInfinity.setCharacterSize(50);
	Utils::SetOrigin(txtInfinity, Origins::MC);
	txtInfinity.setPosition({ size.x * 0.5f,size.y * 0.72f });

	txtBoss.setString(STRING_TABLE->Get("Boss"));
	txtBoss.setCharacterSize(50);
	Utils::SetOrigin(txtBoss, Origins::MC);
	txtBoss.setPosition({ size.x * 0.5f,size.y * 0.78f });


	txtExit.setString(STRING_TABLE->Get("Exit"));
	txtExit.setCharacterSize(50);
	Utils::SetOrigin(txtExit, Origins::MC);
	txtExit.setPosition({ size.x * 0.5f,size.y * 0.85f });

	txtArrow.setString("->");
	txtArrow.setCharacterSize(50);
	Utils::SetOrigin(txtArrow, Origins::MC);
	txtArrow.setPosition({ size.x * 0.41f,size.y * 0.65f });

	currentSelect = Select::Normal;
}

void UiMain::Update(float dt)
{
	auto size = FRAMEWORK.GetWindowSizeF();
	if((InputMgr::GetKeyDown(sf::Keyboard::Down) || InputMgr::GetKeyDown(sf::Keyboard::S))&& currentSelect == Select::Normal)
	{
		txtArrow.setPosition({ size.x * 0.4f,size.y * 0.715f });
		Utils::SetOrigin(txtArrow, Origins::MC);
		currentSelect = Select::Infinity;
	}
	else if ((InputMgr::GetKeyDown(sf::Keyboard::Down) || InputMgr::GetKeyDown(sf::Keyboard::S)) && currentSelect == Select::Infinity)
	{
		txtArrow.setPosition({ size.x * 0.42f,size.y * 0.78f });
		Utils::SetOrigin(txtArrow, Origins::MC);
		currentSelect = Select::Boss;
	}
	else if ((InputMgr::GetKeyDown(sf::Keyboard::Down) || InputMgr::GetKeyDown(sf::Keyboard::S)) && currentSelect == Select::Boss)
	{
		txtArrow.setPosition({ size.x * 0.45f,size.y * 0.85f });
		Utils::SetOrigin(txtArrow, Origins::MC);
		currentSelect = Select::Exit;
	}


	if ((InputMgr::GetKeyDown(sf::Keyboard::Up) || InputMgr::GetKeyDown(sf::Keyboard::W)) && currentSelect == Select::Infinity)
	{
		txtArrow.setPosition({ size.x * 0.41f,size.y * 0.65f });
		Utils::SetOrigin(txtArrow, Origins::MC);
		currentSelect = Select::Normal;
	}
	else if ((InputMgr::GetKeyDown(sf::Keyboard::Up) || InputMgr::GetKeyDown(sf::Keyboard::W)) && currentSelect == Select::Boss)
	{
		txtArrow.setPosition({ size.x * 0.4f,size.y * 0.715f });
		Utils::SetOrigin(txtArrow, Origins::MC);
		currentSelect = Select::Infinity;
	}
	else if ((InputMgr::GetKeyDown(sf::Keyboard::Up) || InputMgr::GetKeyDown(sf::Keyboard::W)) && currentSelect == Select::Exit)
	{
		txtArrow.setPosition({ size.x * 0.42f,size.y * 0.78f });
		Utils::SetOrigin(txtArrow, Origins::MC);
		currentSelect = Select::Boss;
	}


	if (InputMgr::GetKeyDown(sf::Keyboard::Enter))
	{
		switch (currentSelect)
		{
		case Select::Normal:
			SCENE_MGR.ChangeScene(SceneIds::NormalGame);
			break;
		case Select::Infinity:
			SCENE_MGR.ChangeScene(SceneIds::Infinity);
			break;
		case Select::Boss:
			SCENE_MGR.ChangeScene(SceneIds::Boss);
			break;
		case Select::Exit:
			FRAMEWORK.GetWindow().close();
			break;
		}
	}
}

void UiMain::Draw(sf::RenderWindow& window)
{
	window.draw(txtDev);
	window.draw(txtmainTitle);
	window.draw(txtNormal);
	window.draw(txtInfinity);
	window.draw(txtBoss);
	window.draw(txtExit);
	window.draw(txtArrow);
}
