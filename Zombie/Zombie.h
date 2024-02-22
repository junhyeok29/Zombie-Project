#pragma once
#include "SpriteGo.h"
#include "Player.h"
class Zombie : public SpriteGo
{
public: 
	enum class Types
	{
		Bloater,
		Chaser,
		Crawler,
	};
	static const int TotalTyps = 3;
	static Zombie* Create(Types zombieType);

protected:
	Types type;

	int maxHp;
	float speed;

	int hp; //현재 hp

	//플레이 포지션을 계속 받아와야한다.

	Player* player;
	Zombie(const std::string& name = "");

	sf::Vector2f direction; //방향 함수

public:
	~Zombie() override = default;
	
	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

};

