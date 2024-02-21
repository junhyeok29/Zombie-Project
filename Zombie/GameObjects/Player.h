#pragma once
#include "SpriteGo.h"

//바라보는 방향 6Vector
//taget - 시작점 
/*

*/
class Player : public SpriteGo
{
protected:
	sf::Vector2f player;
	sf::Vector2f direction = { 0.f, 0.f };		//방향
	sf::Vector2f look = { 1.0f, 0.f };			//회전  
	float speed = 500.f;

	std::string textureId;

public:
	Player(const std::string& name = "");
	~Player() override = default; //최신 소멸자 문법

	void Init() override;
	void Release() override;

	void Reset() override;

	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;
};

