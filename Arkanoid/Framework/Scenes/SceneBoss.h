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

	ObjectPool<Shuriken> shurikenPool;
	std::list<Shuriken*> activeShurikens;

	ObjectPool<LavaRain> rainPool;
	std::list<LavaRain*> activeRains;

	FireBall* fire;
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

	Boss* GetBoss() { return boss; }
	Shuriken* SpawnShuriken();
	void ReturnShuriken(Shuriken* shuriken);

	void FireShuriken();

	LavaRain* SpawnRain();
	void ReturnRain(LavaRain* rain);
	void RainDrop();

	void ReturnAllObj()override;

	void ShootFireBall();

	void OnUpgrade(UiDevMode::DevMenu menu)override;
};

