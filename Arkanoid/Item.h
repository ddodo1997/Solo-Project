#pragma once

class Item : public GameObject
{
public:
	enum class Types
	{
		Slow,
		Catch,
		Laser,
		Enlarge,
		Disruption,
		Player
	};
	static const int TotalTypes = 6;
protected:
	sf::Sprite body;
	Types currentType;
	std::string texId = "graphics/Arcade - Arkanoid - Powerups.png";

	sf::Texture texture;
	Animator animator;

	sf::Vector2f direction = { 0.f,1.f };
	float speed = 100.f;
public:
	Item(const std::string& name = "");
	~Item() = default;

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

	void SetType(Types type);
	Types GetType() const { return currentType; }
};
