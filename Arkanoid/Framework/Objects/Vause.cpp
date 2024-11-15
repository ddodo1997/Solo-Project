#include "stdafx.h"
#include "Vause.h"
#include "TileMap.h"
#include "SceneGame.h"
Vause::Vause(const std::string& name)
	: GameObject(name)
{
}

void Vause::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
	body.setPosition(position);
}

void Vause::SetRotation(float angle)
{
	rotation = angle;
	body.setRotation(rotation);
}

void Vause::SetScale(const sf::Vector2f& s)
{
	scale = s;
	body.setScale(scale);
}

void Vause::SetOrigin(Origins preset)
{
	originPreset = preset;
	if (originPreset != Origins::Custom)
	{
		origin = Utils::SetOrigin(body, originPreset);
	}
}

void Vause::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
	origin = newOrigin;
	body.setOrigin(origin);
}

void Vause::ChangeAni(const std::string& id, const std::string& nextId)
{
	auto windowSize = FRAMEWORK.GetWindowSizeF();

	animator.Play(id);
	if(nextId != "")
		animator.PlayQueue(nextId);
	SetOrigin(Origins::TC);

	TileMap* map = sceneGame->GetMap();
	sf::FloatRect mapBounds = map->GetGlobalBounds();

	minX = mapBounds.left + body.getLocalBounds().width;
	maxX = mapBounds.width + mapBounds.left - body.getLocalBounds().width;
}

void Vause::Init()
{
	SetScale({ 2.f,2.f });
	sortingLayer = SortingLayers::Foreground;
	sortingOrder = 0;
	animator.SetTarget(&body);
	SetOrigin(Origins::TC);
}

void Vause::Release()
{
}

void Vause::Reset()
{
	sceneGame = dynamic_cast<SceneGame*>(SCENE_MGR.GetCurrentScene());
	ChangeAni("animations/vause_spawn.json", "animations/vause_idle.json");
	
	direction = { 0.f,0.f };
	Utils::SetOrigin(body,Origins::TC);
	SetPosition({ 0.f,400.f });

	isGameover = false;
}

void Vause::Update(float dt)
{
	direction.x = InputMgr::GetAxis(Axis::Horizontal);
	
	auto newPos = position + direction * speed * dt;
	newPos.x = Utils::Clamp(newPos.x, minX, maxX);

	SetPosition(newPos);




	//Test
	if(InputMgr::GetKeyDown(sf::Keyboard::Num1))
		ChangeAni("animations/vause_idle.json");
	if (InputMgr::GetKeyDown(sf::Keyboard::Num2))
		ChangeAni("animations/longvause_idle.json");
	if (InputMgr::GetKeyDown(sf::Keyboard::Num3))
		ChangeAni("animations/vause_formchange.json", "animations/vause_attackformidle.json");
	if (InputMgr::GetKeyDown(sf::Keyboard::Num4))
		ChangeAni("animations/vause_die.json");
	

	animator.Update(dt);
	hitBox.UpdateTr(body, body.getLocalBounds());
}

void Vause::Draw(sf::RenderWindow& window)
{
	window.draw(body);
	hitBox.Draw(window);
}
