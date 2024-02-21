#pragma once
#include "Scene.h"
class Player;

class SceneGame : public Scene
{
protected:

	Player* player = nullptr;

public:

	SceneGame(SceneIds id);
	void Init() override;
	void Release() override;

	void Enter() override;
	void Exit() override;

	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;
};

