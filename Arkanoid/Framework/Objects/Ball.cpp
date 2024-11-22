#include "stdafx.h"
#include "Ball.h"
#include "Vause.h"
#include "SceneGame.h"
#include "TileMap.h"
#include "Bricks.h"
#include "Boss.h"
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
	sceneGame = dynamic_cast<SceneGame*>(SCENE_MGR.GetCurrentScene());
	vause = sceneGame->GetVause();
	bricks = sceneGame->GetBricks();
	boss = sceneGame->GetBoss();
	
	direction = sf::Vector2f(0.f, 0.f);
	speed = 0.f;

	TileMap* map = sceneGame->GetMap();
	sf::FloatRect mapBounds = map->GetGlobalBounds();
	movableBounds = {
		mapBounds.left + radius,
		mapBounds.top + radius * 2 + 16.f,
		mapBounds.width + mapBounds.left - radius,
		mapBounds.height + mapBounds.top
	};

	isMoving = false;
	isSlow = false;
	slowTimer = 0.f;
}

void Ball::Release()
{
}

void Ball::Update(float dt)
{

	if (isSlow)
	{
		slowTimer += dt;
		if (slowTimer > slowDelay)
		{
			speed = 500.f;
			slowTimer = 0.f;
			isSlow = false;
		}
	}

	if (position.x < movableBounds.left)
	{
		position.x = movableBounds.left;
		direction.x *= -1.f;
	}
	else if (position.x > movableBounds.width)
	{
		position.x = movableBounds.width;
		direction.x *= -1.f;
	}

	if (position.y < movableBounds.top)
	{
		position.y = movableBounds.top;
		direction.y *= -1.f;
	}
	else if (position.y > movableBounds.height)
	{
		sceneGame->ReturnBall(this);
		SetPosition({ 0.f,0.f });
		if (sceneGame->GetActiveBall().empty())
		{
			vause->SetGameover(true);
			if (vause->IsGameover())
				return;
			sceneGame->GetMainBall() = sceneGame->SpawnBall(vause->GetPosition(), false);
			
		}
	}

	hitBox.UpdateTr(ball, ball.getGlobalBounds());
}

void Ball::FixedUpdate(float dt)
{

	if (vause != nullptr)
	{
		auto vauseBounds = vause->GetBatBounds();
		if (ball.getGlobalBounds().intersects(vauseBounds))
		{
			SOUND_MGR.PlaySfx("sounds/Arkanoid_vause.wav");
			auto vauseUpperPoints = Utils::GetUpperPoints(vauseBounds);
			auto closetPoint = Utils::FindClosesPoint(ball.getGlobalBounds(), vauseUpperPoints);

			sf::Vector2f topLeft = sf::Vector2f(vauseBounds.left, vauseBounds.top);
			sf::Vector2f topRight = sf::Vector2f(vauseBounds.left + vauseBounds.width, vauseBounds.top);

			float percentage = Utils::GetRelativePosition(topLeft, topRight, closetPoint);
			percentage = percentage > 0 ? Utils::Clamp(percentage, 0.3f, 1.f) : Utils::Clamp(percentage, -1.f, -0.3f);

			position.y = vauseBounds.top;

			direction.x = percentage;
			direction.y *= -1.f;
			if (direction.y < -0.3f)
			{
				direction.y = -1.f;
			}
		}
	}

	for (auto& vec : bricks)
	{
		for (auto& brick : vec)
		{
			if (brick != nullptr && brick->IsActive())
			{
				auto brickBounds = brick->GetGlobalBounds();
				if (ball.getGlobalBounds().intersects(brickBounds))
				{
					auto brick6Points = Utils::Get6Points(brickBounds);
					auto closetPoint = Utils::FindClosesPoint(ball.getGlobalBounds(), brick6Points);

					auto brickCenter = Utils::GetCenter(brickBounds);

					//충돌 시 방향 반전
					if (closetPoint.y != brickCenter.y)
					{
						if (closetPoint.y > brickCenter.y)
						{
							position.y = closetPoint.y + 20.f;
						}
						if (closetPoint.y < brickCenter.y)
						{
							position.y = closetPoint.y;
						}

						direction.y *= -1.f;
					}
					else
					{
						if (closetPoint.x > brickCenter.x)
						{
							position.x = closetPoint.x + 15.f;
						}
						if (closetPoint.x < brickCenter.x)
						{
							position.x = closetPoint.x - 5.f;
						}

						direction.x *= -1.f;
					}
					if(isDevMode)
						brick->OnHit(devDamage);
					else
						brick->OnHit(damage);

					break;
				}
			}
		}
	}

	if (boss != nullptr)
	{
		auto bossBounds = boss->GetHitBox().rect.getGlobalBounds();
		if (bossBounds.intersects(ball.getGlobalBounds()))
		{
			if (position.x < bossBounds.left)
			{
				position.x = bossBounds.left - radius;
				direction.x *= -1.f;
			}
			else if (position.x > bossBounds.width + bossBounds.left)
			{
				position.x = bossBounds.width + bossBounds.left + radius * 2.f;
				direction.x *= -1.f;
			}

			else if (position.y > bossBounds.top && position.y <= bossBounds.top + radius * 2.f)
			{
				position.y = bossBounds.top - radius;
				direction.y *= -1.f;
			}
			else if (position.y > bossBounds.height + bossBounds.top)
			{
				position.y = bossBounds.height + bossBounds.top + radius * 4.f;
				direction.y *= -1.f;
			}
			if (isDevMode)
				boss->OnHit(position,devDamage);
			else
				boss->OnHit(position,damage);
		}
	}

	float dirMagnitude = Utils::Magnitude(direction);
	if (dirMagnitude != 1.f)
	{
		Utils::Normailize(direction);
	}

	SetPosition(position + direction * speed * dt);
}

void Ball::Draw(sf::RenderWindow& window)
{
	window.draw(ball);
	hitBox.Draw(window);
}

void Ball::SetSlow()
{
	isSlow = true;
	speed = 300.f;
}