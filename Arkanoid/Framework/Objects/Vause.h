#pragma once
class SceneGame;
class Vause : public GameObject
{
protected:
	sf::Sprite body;
	Animator animator;

	sf::Vector2f direction;
	float speed = 700.f;

	sf::Vector2f initPos;

	float minX = 0.f;
	float maxX = 0.f;
	int life = 3;
	bool isGameover = false;

	SceneGame* sceneGame;
public:
	Vause(const std::string& name = "");
	~Vause() = default;

	void SetPosition(const sf::Vector2f& pos) override;
	void SetRotation(float angle) override;
	void SetScale(const sf::Vector2f& scale) override;

	void SetOrigin(Origins preset) override;
	void SetOrigin(const sf::Vector2f& newOrigin) override;

	void ChangeAni(const std::string& id, const std::string& nextId = "");

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	bool IsGameover() const { return isGameover; }
	void SetGameover(bool isGameover) { 
		if (life > 0)
		{
			life--;
			return;
		}
		this->isGameover = isGameover;
	}
	sf::FloatRect GetBatBounds() { return body.getGlobalBounds(); }
};
