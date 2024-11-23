#pragma once
#include "Boss.h"
class Boss1 :
    public Boss
{
public:
	struct Pattern1
	{
		float attackDelay = 7.5f;
		float attackTimer = 0.f;

		float attackingDelay = 2.5f;
		float attackingTimer = 0.f;

		float rapidDelay = 0.5f;
		float rapidTimer = 0.f;

		bool attack = false;
		bool attacking = false;
		bool rapid = false;
	};
	struct Pattern2
	{
		float rapidDelay = 1.f;
		float rapidTimer = 0.f;
	};
	struct Pattern3
	{
		float attackDelay = 5.f;
		float attackTimer = 0.f;

		float fireDelay = 2.f;
		float fireTimer = 0.f;

		sf::Vector2f targetPos;

		bool attack = false;

		bool isReady = false;
	};
protected:

	Pattern1 pattern1;
	Pattern2 pattern2;
	Pattern3 pattern3;

public:
	Boss1(const std::string& name = "");
	~Boss1() = default;

	virtual void SetPosition(const sf::Vector2f& pos) override;
	virtual void SetRotation(float angle) override;
	virtual void SetScale(const sf::Vector2f& scale) override;

	virtual void SetOrigin(Origins preset) override;
	virtual void SetOrigin(const sf::Vector2f& newOrigin) override;

	virtual void Init() override;

	virtual void Release() override;

	virtual void Reset() override;
	virtual void PatternReset();

	virtual void Update(float dt) override;
	void Pattern1(float dt);
	void Pattern2(float dt);
	void Pattern3(float dt);

	virtual void Draw(sf::RenderWindow& window) override;

	virtual void OnHit(sf::Vector2f pos, int damage);
	virtual void Attack();
	virtual void OnDie();

	sf::Vector2f& GetTargetPos() { return pattern3.targetPos; }

};

