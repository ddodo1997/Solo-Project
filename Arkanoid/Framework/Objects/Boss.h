#pragma once
class SceneGame;
class Shuriken;
class Vause;
class Boss : public GameObject
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
	sf::Sprite body;

	SceneGame* sceneGame;
	Animator animator;

	int hp = 50;

	Pattern1 pattern1;
	Pattern2 pattern2;
	Pattern3 pattern3;

public:
	Boss(const std::string& name = "");
	~Boss() = default;

	void SetPosition(const sf::Vector2f& pos) override;
	void SetRotation(float angle) override;
	void SetScale(const sf::Vector2f& scale) override;

	void SetOrigin(Origins preset) override;
	void SetOrigin(const sf::Vector2f& newOrigin) override;

	void Init() override;
	void Release() override;
	void Reset() override;
	void PatternReset();
	void Update(float dt) override;
	void Pattern1(float dt);
	void Pattern2(float dt);
	void Pattern3(float dt);
	void Draw(sf::RenderWindow& window) override;

	void OnHit(sf::Vector2f pos, int damage);
	void Attack();
	void OnDie();

	bool isDie()const { return hp >= 0 ? false : true; }

	sf::Vector2f& GetTargetPos() { return pattern3.targetPos; }
};
