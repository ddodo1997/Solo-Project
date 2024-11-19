#pragma once
#include "SceneGame.h"
class SceneInfinity : public SceneGame
{
protected:
	sf::Vector2i bricksSize = { 10,10 };

public:
	SceneInfinity();
	~SceneInfinity() = default;
	void Init() override;
	void InitBricks();
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
};