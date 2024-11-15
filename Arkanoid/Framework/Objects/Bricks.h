#pragma once

class Bricks : public GameObject
{
public:
	enum class Types
	{
		None = -1,
		White, Orange, Sky, Green,
		Red, Blue, Pink, Yellow,
		Super, Immotal,
	};
	static const int TotalTypes = 10;
protected:
	sf::Sprite body;

	std::string texId = "graphics/Arcade - Arkanoid - Blocks & Backgrounds.png";
	sf::Texture texture;
	Types currentType;
	int score = 0;
	int hp = 0;

	float flickeringTimer = 0.f;
	float flickeringDelay = 3.f;

	Animator animator;
public:
	Bricks(const std::string& name = "");
	~Bricks() = default;

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

	sf::FloatRect GetLocalBounds()const override;

	void SetType(Types type);
};
