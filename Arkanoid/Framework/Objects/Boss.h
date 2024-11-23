#pragma once
class SceneGame;
class Shuriken;
class Vause;
class Boss : public GameObject
{
public:
protected:
	sf::Sprite body;

	SceneGame* sceneGame;
	Animator animator;

	int hp = 50;

public:
	Boss(const std::string& name = "");
	~Boss() = default;

	virtual void SetPosition(const sf::Vector2f& pos) override;
	virtual void SetRotation(float angle) override;
	virtual void SetScale(const sf::Vector2f& scale) override;

	virtual void SetOrigin(Origins preset) override;
	virtual void SetOrigin(const sf::Vector2f& newOrigin) override;

	virtual void Init() override;

	virtual void Release() override;

	virtual void Reset() override;
	virtual void PatternReset() = 0;

	virtual void Update(float dt) override;

	virtual void Draw(sf::RenderWindow& window) override;

	virtual void OnHit(sf::Vector2f pos, int damage);
	virtual void Attack() = 0;
	virtual void OnDie() = 0;
	virtual bool isDie()const { return hp >= 0 ? false : true; }
};
