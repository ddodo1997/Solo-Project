#include "stdafx.h"
#include "Ball.h"
#include "Vause.h"
#include "SceneGame.h"
#include "TileMap.h"
Ball::Ball(const std::string& name)
	:GameObject(name)
{
}

void Ball::SetPosition(const sf::Vector2f& pos)
{
	GameObject::SetPosition(pos);
	ball.setPosition(pos);
}

void Ball::SetScale(const sf::Vector2f& scale)
{
	GameObject::SetScale(scale);
	ball.setScale(scale);
}

void Ball::SetOrigin(Origins preset)
{
	GameObject::SetOrigin(preset);
	if (originPreset != Origins::Custom)
		origin = Utils::SetOrigin(ball, originPreset);
}

void Ball::SetOrigin(const sf::Vector2f& newOrigin)
{
	GameObject::SetOrigin(newOrigin);
	ball.setOrigin(newOrigin);
}

void Ball::Init()
{
	//기본 세팅
	ball.setRadius(radius);
	ball.setFillColor(sf::Color::Blue);
	ball.setOutlineColor(sf::Color::White);
	ball.setOutlineThickness(2);
	SetOrigin(Origins::BC);
}

void Ball::Reset()
{
	SceneGame* sceneGame = dynamic_cast<SceneGame*>(SCENE_MGR.GetCurrentScene());
	vause = sceneGame->GetVause();
	direction = sf::Vector2f(0.f, 0.f);
	speed = 0.f;
	score = 0;

	//윈도우 바운드와 공 크기에 비례해 무브에이블바운즈를 재설정
	TileMap* map = sceneGame->GetMap();
	sf::FloatRect mapBounds = map->GetGlobalBounds();
	movableBounds = {
		mapBounds.left + radius,
		mapBounds.top + radius * 2 + 8.f,
		mapBounds.width + mapBounds.left - radius,
		mapBounds.height + mapBounds.top
	};

	isMoving = false;
}

void Ball::Release()
{
}

void Ball::Update(float dt)
{
	auto newPos = position + direction * speed * dt;

	if (newPos.x < movableBounds.left)
	{
		newPos.x = movableBounds.left;
		direction.x *= -1.f;
	}
	else if (newPos.x > movableBounds.width)
	{
		newPos.x = movableBounds.width;
		direction.x *= -1.f;
	}

	if (newPos.y < movableBounds.top)
	{
		newPos.y = movableBounds.top;
		direction.y *= -1.f;
	}
	else if (newPos.y > movableBounds.height)
	{
		/*newPos.y = movableBounds.height;
		direction.y *= -1.f;*/
		isMoving = false;
		vause->SetGameover(true);
	}

	SetPosition(newPos);
	hitBox.UpdateTr(ball, ball.getGlobalBounds());
}

void Ball::FixedUpdate(float dt)
{
	if (vause != nullptr)
	{
		auto vauseBounds = vause->GetBatBounds();
		if (ball.getGlobalBounds().intersects(vauseBounds))
		{
			if (Utils::CheckCollision(hitBox, vause->GetHitBox()))
			{
				position.y = vauseBounds.top;
				direction.y *= -1.f;
				score++;
			}
		}
	}
}

void Ball::Draw(sf::RenderWindow& window)
{
	window.draw(ball);
	hitBox.Draw(window);
}
