#pragma once
class Vause;
class Boss;
class FireBall : public GameObject
{
protected:
	sf::Sprite body;

	Animator animator;
	Vause* vause;
	Boss* boss;

	sf::Vector2f direction;
	float speed = 1500.f;
public:
	FireBall(const std::string& name = "");
	~FireBall() = default;

	void SetPosition(const sf::Vector2f& pos) override;
	void SetRotation(float angle) override;
	void SetScale(const sf::Vector2f& scale) override;

	void SetOrigin(Origins preset) override;
	void SetOrigin(const sf::Vector2f& newOrigin) override;

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void FixedUpdate(float dt)override;
	void Draw(sf::RenderWindow& window) override;

	void Shoot(sf::Vector2f targetDirection);
};
