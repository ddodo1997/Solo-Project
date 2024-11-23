#pragma once
#include "SceneBoss.h"
class Shuriken;
class LavaRain;
class FireBall;
class SceneBoss1 : public SceneBoss
{
public:
protected:

	ObjectPool<Shuriken> shurikenPool;
	std::list<Shuriken*> activeShurikens;

	ObjectPool<LavaRain> rainPool;
	std::list<LavaRain*> activeRains;

	FireBall* fire;
public:
	SceneBoss1();
	~SceneBoss1() = default;
	void Init() override;
	void Enter() override;
	void Exit() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	void UpdateUi()override;

	Shuriken* SpawnShuriken();
	void ReturnShuriken(Shuriken* shuriken);

	void FireShuriken();

	LavaRain* SpawnRain();
	void ReturnRain(LavaRain* rain);
	void RainDrop();

	void ReturnAllObj()override;

	void ShootFireBall();

};

