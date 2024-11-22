#pragma once
class Vause;
class SceneGame;
class Boss;
class Laser : public GameObject
{
public:
	enum class Direction
	{
		Left,
		Right,
	};
protected:
	sf::Sprite body;

	std::string texId = "graphics/vause_sheet.png";
	sf::IntRect tex = {148, 48, 10, 20};
	sf::IntRect temp = { 0,0, 48, 66 };
	sf::Vector2f direction = { 0.f,-1.f };
	float speed = 300.f;

	float movableTop;
	Vause* vause;
	Boss* boss;
	SceneGame* sceneGame;

	bool isFire = false;

	int damage = 1;
public:
	Laser(const std::string& name = "");
	~Laser() = default;

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

	void Fire(const sf::Vector2f& position, float s);
	void SetFire(bool isFire) { this->isFire = isFire; }
};
