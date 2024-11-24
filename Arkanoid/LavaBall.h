#pragma once
class SceneGame;
class Vause;
class LavaBall : public GameObject
{
protected:
	sf::Sprite body;

	SceneGame* sceneGame;

	Vause* vause;
	Animator animator;

	sf::Vector2f direction;
	float velocity;
	float gravity = 10.f;;
public:
	LavaBall(const std::string& name = "");
	~LavaBall() = default;

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

	void Scatter(sf::Vector2f pos);
};
