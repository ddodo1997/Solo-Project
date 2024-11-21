#pragma once
#include "SceneGame.h"
class Boss;
class SceneBoss : public SceneGame
{
public:
protected:
	Boss* boss;
public:
	SceneBoss();
	~SceneBoss() = default;
	void Init() override;
	void Enter() override;
	void Exit() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;
	bool isStageClear();

	void UpdateUi()override;

	void SpawnItem(const sf::Vector2f& position) override;
};

