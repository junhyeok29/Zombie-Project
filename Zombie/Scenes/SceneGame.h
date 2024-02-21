#pragma once
#include "Scene.h"
class Player;
//class Zombie;

class SceneGame : public Scene
{
protected:

	Player* player = nullptr;
	//Zombie* zombie = nullptr;

	

public:

	SceneGame(SceneIds id);
	void Init() override;
	void Release() override;

	void Enter() override;
	void Exit() override;

	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;
};

