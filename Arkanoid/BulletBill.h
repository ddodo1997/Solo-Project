#pragma once
class Vause;
class BulletBill : public GameObject
{
protected:
	sf::Sprite body;
	Animator animator;

	Vause* vause;

	float speed = 500.f;
	sf::Vector2f direction = { 0.f,1.f };
public:
	BulletBill(const std::string& name = "");
	~BulletBill() = default;

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

	void Fire(sf::Vector2f pos);
};
