#pragma once
#include "Item.h"
#include "Laser.h"
class SceneGame;
class Ball;
class Vause : public GameObject
{
public:
	enum class Status
	{
		Normal,
		Enlarge,
		Laser,
		GameOver,
	};
protected:
	sf::Sprite body;
	std::vector<Laser*> lasers;
	Status currentStatus = Status::Normal;
	Status prevStatus;
	Animator animator;

	sf::Vector2f direction;
	float speed = 700.f;

	sf::Vector2f initPos;

	float minX = 0.f;
	float maxX = 0.f;
	int life = 3;
	bool isLaser = false;

	SceneGame* sceneGame;

	float enlargeTimer = 0.f;
	float enlargeDelay = 10.f;

	float laserTimer = 0.f;
	float laserDelay = 10.f;

	float invincibleTimer = 0.f;
	float invincibleDelay = 1.f;
	bool isInvincible = false;
public:
	Vause(const std::string& name = "");
	~Vause() = default;

	void SetPosition(const sf::Vector2f& pos) override;
	void SetRotation(float angle) override;
	void SetScale(const sf::Vector2f& scale) override;

	void SetOrigin(Origins preset) override;
	void SetOrigin(const sf::Vector2f& newOrigin) override;

	sf::FloatRect GetLocalBounds()const  override;
	sf::FloatRect GetGlobalBounds()const override;

	void ChangeAni(const std::string& id, const std::string& nextId = "");

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;

	void UpdateEnlarge(float dt);
	void UpdateLaser(float dt);

	void SetStatus(Status stat);

	void FixedUpdate(float dt)override;
	void Draw(sf::RenderWindow& window) override;

	bool IsGameover() const { return currentStatus == Status::GameOver ? true : false; }
	void SetGameover(bool isGameover);

	bool IsInvincible()const { return isInvincible; }
	void SetInvincible(bool stat) { isInvincible = stat; }

	sf::FloatRect GetBatBounds() { return body.getGlobalBounds(); }
	int GetExtraLife() const { return life; }

	void OnPickupItem(Item::Types type);

	void OnHit();
};
