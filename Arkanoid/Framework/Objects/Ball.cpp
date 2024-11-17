#include "stdafx.h"
#include "Ball.h"
#include "Vause.h"
#include "SceneGame.h"
#include "TileMap.h"
#include "Bricks.h"
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
	//�⺻ ����
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
	bricks = sceneGame->GetBricks();
	direction = sf::Vector2f(0.f, 0.f);
	speed = 0.f;
	score = 0;

	//������ �ٿ��� �� ũ�⿡ ����� ���꿡�̺�ٿ�� �缳��
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
		isMoving = false;
		vause->SetGameover(true);
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
			if (Utils::CheckCollision(hitBox, vause->GetHitBox()))
			{
				position.y = vauseBounds.top;
				direction.y *= -1.f;
				score++;
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
					auto ballBounds = ball.getGlobalBounds();

					auto brick6Points = Get6Points(brickBounds);
					auto closetPoint = FindClosesPoint(ballBounds, brick6Points);

					auto brickCenter = GetCenter(brickBounds);

					//�浹 �� ���� ����
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
					brick->OnHit();
				}
			}
		}
	}

	SetPosition(position + direction * speed * dt);
}

void Ball::Draw(sf::RenderWindow& window)
{
	window.draw(ball);
	hitBox.Draw(window);
}

std::vector<sf::Vector2f> Ball::Get6Points(const sf::FloatRect& bounds)
{
	std::vector<sf::Vector2f> result;


	// �� ������ ���ϱ�
	sf::Vector2f topLeft = sf::Vector2f(bounds.left, bounds.top);
	sf::Vector2f topRight = sf::Vector2f(bounds.left + bounds.width, bounds.top);
	sf::Vector2f bottomLeft = sf::Vector2f(bounds.left, bounds.top + bounds.height);
	sf::Vector2f bottomRight = sf::Vector2f(bounds.left + bounds.width, bounds.top + bounds.height);

	// ���θ� 3����� ��ġ ���
	float thirdWidth = bounds.width * 0.3333f;

	// ���θ� 2����� ��ġ ���
	float halfHeight = bounds.height * 0.5f;

	// 6�� �� ���
	result.push_back(sf::Vector2f(bounds.left + thirdWidth, bounds.top)); // ���� 3���� ��
	result.push_back(sf::Vector2f(bounds.left + thirdWidth * 2.f, bounds.top)); // ������ 3���� ��
	result.push_back(sf::Vector2f(bounds.left + thirdWidth, bounds.top + bounds.height)); // ���� 3���� �Ʒ�
	result.push_back(sf::Vector2f(bounds.left + thirdWidth * 2.f, bounds.top + bounds.height)); // ������ 3���� �Ʒ�
	result.push_back(sf::Vector2f(bounds.left, bounds.top + halfHeight)); // ���� ���� ����
	result.push_back(sf::Vector2f(bounds.left + bounds.width, bounds.top + halfHeight)); // ������ ���� ����

	// 0 1 2
	// 3 4 5

	return result;
}

// ���� ����� �� ã��
sf::Vector2f Ball::FindClosesPoint(
	const sf::FloatRect& ballBounds,
	const std::vector<sf::Vector2f>& brickPoints)
{
	sf::Vector2f ballCenter = ballBounds.getPosition() + sf::Vector2f(ballBounds.width / 2.f, ballBounds.height / 2.f);

	float minDistance = std::numeric_limits<float>::max();
	sf::Vector2f closestPoint;

	for (const auto& middle : brickPoints) {
		float dist = Utils::Distance(ballCenter, middle);
		if (dist < minDistance) {
			minDistance = dist;
			closestPoint = middle;
		}
	}

	return closestPoint;
}

sf::Vector2f Ball::GetCenter(const sf::FloatRect& rect) {
	// ���簢���� �� ������ ��ǥ
	sf::Vector2f topLeft = sf::Vector2f(rect.left, rect.top);
	sf::Vector2f bottomRight = sf::Vector2f(rect.left + rect.width, rect.top + rect.height);

	// ���� ��� (���⼭�� �߾����� ���)
	sf::Vector2f center = (topLeft + bottomRight) * 0.5f;

	return center;
}