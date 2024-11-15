#pragma once
#include "GameObject.h"
class Vause;
class SceneGame;
class Ball :
    public GameObject
{
protected:
    sf::CircleShape ball;
	float radius = 5.f;

    sf::Vector2f direction;
    float speed = 0.f;

	sf::FloatRect movableBounds;
	int score = 0;

	Vause* vause = nullptr;
	bool isMoving = false;
public:
	Ball(const std::string& name = "");
	~Ball() = default;

	void SetPosition(const sf::Vector2f& pos)override;
	void SetScale(const sf::Vector2f& scale) override;
	void SetOrigin(Origins preset)override;
	void SetOrigin(const sf::Vector2f& newOrigin)override;
	void Init()override;
	void Reset()override;
	void Release()override;
	void Update(float dt)override;
	void FixedUpdate(float dt) override;
	void Draw(sf::RenderWindow& window)override;

	void Fire(const sf::Vector2f& d, float s)
	{
		isMoving = true;
		direction = d;
		speed = s;
	}

	void SetBat(Vause* bat) { this->vause = bat; }
	bool isMove() const { return isMoving; }

	void SetScore(int score) { this->score = score; }
	int GetScore()const { return score; }
};

