#pragma once
class Vause;
class LavaRain : public GameObject
{
protected:
	sf::Sprite body;

	Animator animator;

	float gravity = 1000.f;
	float velocity = 0.f;

	Vause* vause;
public:
	LavaRain(const std::string& name = "");
	~LavaRain() = default;

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

	void Drop(float xPos);
};
