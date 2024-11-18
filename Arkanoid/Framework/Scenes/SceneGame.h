#pragma once
#include "Scene.h"
class Vause;
class TileMap;
class Ball;
class UiInGame;
class Bricks;
class Item;
class Laser;
class SceneGame : public Scene
{
protected:
	TileMap* tileMap;
	Vause* vause;
	std::vector<Laser*> lasers;

	std::list<Ball*> activeBalls;
	ObjectPool<Ball> ballsPool;
	Ball* mainBall;
	sf::Vector2i bricksSize = { 10,10 };
	std::vector<std::vector<Bricks*>> bricks;

	std::list<Item*> activeItems;
	ObjectPool<Item> itemPool;

	UiInGame* uiInGame;

	int score = 0;
public:
	SceneGame();
	~SceneGame() = default;

	void Init() override;
	void InitBricks();
	void Enter() override;
	void Exit() override;

	TileMap* GetMap() const { return tileMap; }
	Vause* GetVause() const { return vause; }
	const std::list<Ball*>& GetActiveBall() const { return activeBalls; }
	const std::vector<std::vector<Bricks*>>& GetBricks() const { return bricks; }

	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	void UpdateUi();
	void SetStage(const std::string& key);
	void SpawnItem(const sf::Vector2f& position);
	void ReturnItem(Item* item);
	Ball* SpawnBall(const sf::Vector2f& position, bool isMoving = false);
	void ReturnBall(Ball* ball);
	Ball*& GetMainBall() { return mainBall; }
	std::vector<Laser*>& GetLaser() { return lasers; }
	const std::list<Item*>& GetActiveItems() { return activeItems; }

	void AddScore(int score) {
		this->score += score;
		if (this->score >= highScore)
			highScore = this->score;
	}
};