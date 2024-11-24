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
		//�� Ȥ�� ��� ������ ���̹����� õ�忡�� �߾ӱ��� ����ü ���̺�
		bool isButt = false;

		float dropTimer = 0.f;
		float dropDelay = 0.08f;

		float patternTimer = 0.f;
		float patternDelay = 1.f;

		float distance = 0.f;
	};
	struct Pattern2
	{
		//�밢������ �����ð����� ������ �ε��� �κп��� ���׸� �Ͷ߸���
		bool isAccel = false;
		bool isDecel = false;

		float accelTimer = 0.f;
		float accelDelay = 3.f;

		int patternCnt = 0;
	};
	struct Pattern3
	{
		//3�� ������ ���� �߻�
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
