#pragma once
#include "SceneGame.h"
class SceneInfinity : public SceneGame
{
protected:
	sf::Vector2i bricksSize = { 29,10 };

	int emptySpace = 9;
	int currentWave = 0;
public:
	SceneInfinity();
	~SceneInfinity() = default;
	void Init() override;
	void InitBricks();
	void SetStage();
	void Enter() override;
	void Exit() override;

	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;
	void UpdateUi()override;

	void AddScore(int score) override {
		this->score += score;
		if (this->score >= infinityHighScore)
			infinityHighScore = this->score;
	}

	void SpawnItem(const sf::Vector2f& position)override;
	bool GameOver();
};