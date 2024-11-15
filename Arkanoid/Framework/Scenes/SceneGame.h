#pragma once
#include "Scene.h"
class Vause;
class TileMap;
class Ball;
class UiInGame;
class Bricks;
class SceneGame : public Scene
{
protected:
	TileMap* tileMap;
	Vause* vause;
	Ball* ball;
	sf::Vector2i bricksSize = { 10,10 };
	std::vector<std::vector<Bricks*>> bricks;
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

	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	void UpdateUi();
	void SetStage();
};