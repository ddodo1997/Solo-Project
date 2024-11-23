#pragma once
#include "SceneGame.h"
class Boss;
class Shuriken;
class LavaRain;
class FireBall;
class SceneBoss : public SceneGame
{
public:
protected:
	Boss* boss;
public:
	SceneBoss(SceneIds id);
	~SceneBoss() = default;
	virtual void Init() override;
	virtual void Enter() override;
	virtual void Exit() override;
	virtual void Update(float dt) override;
	virtual void Draw(sf::RenderWindow& window) override;
	virtual bool isStageClear();

	virtual void UpdateUi()override;

	virtual void SpawnItem(const sf::Vector2f& position) override;

	virtual Boss* GetBoss() { return boss; }

	virtual void OnUpgrade(UiDevMode::DevMenu menu)override;
};

