#pragma once
#include "Scene.h"
class Vause;
class TileMap;
class Ball;
class UiInGame;
class SceneGame : public Scene
{
protected:
	TileMap* tileMap;
	Vause* vause;
	Ball* ball;
	UiInGame* uiInGame;

	int score = 0;
public:
	SceneGame();
	~SceneGame() = default;

	void Init() override;
	void Enter() override;
	void Exit() override;

	TileMap* GetMap() const { return tileMap; }
	Vause* GetVause() const { return vause; }

	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	void UpdateUi();
};