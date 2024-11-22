#pragma once
#include "Scene.h"
#include "UiDevMode.h"
class Vause;
class TileMap;
class Ball;
class UiInGame;
class UiCenter;
class Bricks;
class Item;
class Laser;
class Boss;
class SceneGame : public Scene
{
public:

	enum class Stages
	{
		Stage1,
		Stage2,
		Stage3,
	};

	enum class Mode
	{
		Normal,
		Infinity,
		Boss,
	};

protected:
	TileMap* tileMap;
	Vause* vause;
	std::vector<Laser*> lasers;

	std::list<Ball*> activeBalls;
	ObjectPool<Ball> ballsPool;
	Ball* mainBall;
	std::vector<std::vector<Bricks*>> bricks;

	std::list<Item*> activeItems;
	ObjectPool<Item> itemPool;

	UiInGame* uiInGame;
	UiCenter* uiCenter;
	UiDevMode* uiDevMode;
	int score = 0;

	Mode currentMode;
public:
	SceneGame(SceneIds id);
	~SceneGame() = default;

	virtual void Init() override;
	virtual void Enter() override;
	virtual void Exit() override;

	virtual const std::list<Ball*>& GetActiveBall() const { return activeBalls; }
	virtual const std::vector<std::vector<Bricks*>>& GetBricks() const { return bricks; }

	virtual void Update(float dt) override;
	virtual void Draw(sf::RenderWindow& window) override;

	virtual void UpdateUi();
	virtual void SpawnItem(const sf::Vector2f& position) = 0;
	virtual void ReturnItem(Item* item);
	virtual Ball* SpawnBall(const sf::Vector2f& position, bool isMoving = false);
	virtual void ReturnBall(Ball* ball);

	virtual void ReturnAllObj();

	virtual TileMap* GetMap() const { return tileMap; }
	virtual Vause* GetVause() const { return vause; }
	virtual Ball*& GetMainBall() { return mainBall; }
	virtual std::vector<Laser*>& GetLaser() { return lasers; }
	virtual const std::list<Item*>& GetActiveItems() { return activeItems; }

	Mode GetCurrentMode() const { return currentMode; }

	void AddScore(int score) {
		this->score += score;
		if (this->score >= normalHighScore)
			normalHighScore = this->score;
	}

	virtual Boss* GetBoss() { return nullptr; }

	virtual void OnUpgrade(UiDevMode::DevMenu dev);
};