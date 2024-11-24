#pragma once
#include "Boss.h"
class Boss2 : public Boss
{
public:
	enum class Pattern
	{
		None,
		Pattern1,
		Pattern2,
		Pattern3
	};

	struct Pattern1
	{
		//좌 혹은 우로 돌진해 들이받은쪽 천장에서 중앙까지 투사체 웨이브
		bool isButt = false;

		float dropTimer = 0.f;
		float dropDelay = 0.08f;

		float patternTimer = 0.f;
		float patternDelay = 1.f;

		float distance = 0.f;
	};
	struct Pattern2
	{
		//대각선으로 일정시간동안 돌진해 부딪힌 부분에서 마그마 터뜨리기
		bool isAccel = false;
		bool isDecel = false;

		float accelTimer = 0.f;
		float accelDelay = 3.f;

		int patternCnt = 0;
	};
	struct Pattern3
	{
		//3번 점프해 대포 발사
		char jumpCnt = 0;

		float jumpTimer = 0.f;
		float jumpDelay = 2.f;

		bool isJumping = false;
	};
protected:
	Pattern currentPattern = Pattern::None;

	Pattern1 pattern1;
	Pattern2 pattern2;
	Pattern3 pattern3;

	float velocity;
	sf::Vector2f direction;

	float patternTimer = 0.f;
	float patternDelay = 3.f;

public:
	Boss2(const std::string& name = "");
	~Boss2() = default;

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
	virtual void Pattern1(float dt);
	virtual void Pattern2(float dt);
	virtual void Pattern3(float dt);
	void SetPattern(Pattern pattern);
	void Fire(sf::Vector2f dir);

	void FixedUpdate(float dt)override;

	virtual void Draw(sf::RenderWindow& window) override;

	virtual void OnHit(sf::Vector2f pos, int damage);
	virtual void Attack();
	virtual void OnDie();

	void LookVause();

	void Butt(sf::Vector2f pos);
};
