#pragma once
#include "SceneGame.h"
class SceneInfinity : public SceneGame
{
protected:
	sf::Vector2i bricksSize = { 28,10 };

	int currentWave = 0;

	float waveTimer = 0.f;
	float waveDelay = 5.f;
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

	void AddWave() {
		currentWave++;
		if (currentWave > BestRecordWave)
			BestRecordWave = currentWave;
	}

	void SpawnItem(const sf::Vector2f& position)override;
	bool GameOver();

	void PushWave();
};