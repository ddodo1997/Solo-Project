#pragma once
#include "Scene.h"
class UiMain;
class SceneMain : public Scene
{
protected:
	UiMain* uiMain;
public:
	SceneMain();
	~SceneMain() = default;

	void Init() override;
	void Enter() override;
	void Exit() override;

	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;
};

