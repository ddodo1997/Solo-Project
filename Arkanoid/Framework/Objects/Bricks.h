#pragma once
#include "Item.h"
class SceneGame;
class Item;
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

	Item item;

	std::string texId = "graphics/Arcade - Arkanoid - Blocks & Backgrounds.png";
	sf::Texture texture;
	Types currentType;
	int score = 0;
	int hp = 0;

	Animator animator;

	bool isBroken = false;
public:
	Bricks(const std::string& name = "");
	~Bricks() = default;

	void SetPosition(const sf::Vector2f& pos) override;
	void SetRotation(float angle) override;
	void SetScale(const sf::Vector2f& scale) override;

	void SetOrigin(Origins preset) override;
	void SetOrigin(const sf::Vector2f& newOrigin) override;

	sf::FloatRect GetLocalBounds()const override { return body.getLocalBounds(); }
	sf::FloatRect GetGlobalBounds()const override { return body.getGlobalBounds(); }

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	void SetType(Types type);

	void OnHit();

	bool IsBroken() const { return isBroken; }

	Types GetCurrentType()const { return currentType; }

	void SetHp(int hp) { this->hp = hp; }
	int GetHp() { return hp; }
};
