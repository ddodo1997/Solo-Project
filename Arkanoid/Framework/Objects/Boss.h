#pragma once

class Boss : public GameObject
{
protected:
	sf::Sprite body;

	Animator animator;

	int hp = 30;

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
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	void OnHit();
	void Attack();
	void OnDie();

	bool isDie()const { return hp > 0 ? false : true; }
};
