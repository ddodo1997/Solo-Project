#pragma once
#include "SceneGame.h"
class SceneNormalGame :
    public SceneGame
{
public:
protected:
	sf::Vector2i bricksSize = { 10,10 };
	Stages currentStage = Stages::Stage1;
public:
	SceneNormalGame();
	~SceneNormalGame() = default;
	void SetStage(Stages stage);
	void Init();
	void InitBricks();
	void Enter();
	void Exit();
	void Update(float dt);
	void Draw(sf::RenderWindow& window);
	bool isStageClear();

	void UpdateUi()override;


	void SpawnItem(const sf::Vector2f& position) override;
};

