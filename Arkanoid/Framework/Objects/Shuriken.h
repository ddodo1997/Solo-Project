#pragma once
class Boss;
class Vause;
class Shuriken : public GameObject
{
protected:
	sf::Sprite body;

	Animator animator;

	float speed = 300.f;
	sf::Vector2f direction = { 0.f,0.f };
	Boss* boss;
	Vause* vause;
public:
	Shuriken(const std::string& name = "");
	~Shuriken() = default;

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

	void Fire(sf::Vector2f targetPos);
};