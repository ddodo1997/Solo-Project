#pragma once
#include "SceneBoss.h"
class VauseFire;
class HeiHo;
class SceneBoss2 :
    public SceneBoss
{
protected:
	sf::Vector2i bricksSize = { 1,10 };

	ObjectPool<VauseFire> vauseFirePool;
	std::list<VauseFire*> activeVauseFire;

	ObjectPool<HeiHo> heiHoPool;
	std::list<HeiHo*> activeHeiHo;

	bool shaking = false;
public:
	SceneBoss2();
	~SceneBoss2() = default;
	void Init() override;
	void InitBricks();
	void Enter() override;
	void SetStage();
	void Exit() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	void UpdateUi()override;

	void ViewShake(float duration, float dt);
	void Shake() { shaking = true; }

	void ReturnAllObj()override;

	VauseFire* SpawnVauseFire();
	void ReturnVauseFire(VauseFire* val);

	HeiHo* SpawnHeiHo();
	void ReturnHeiHo(HeiHo* val);
};

