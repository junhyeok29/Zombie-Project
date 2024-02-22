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

	int hp; //���� hp

	//�÷��� �������� ��� �޾ƿ;��Ѵ�.

	Player* player;
	Zombie(const std::string& name = "");

	sf::Vector2f direction; //���� �Լ�

public:
	~Zombie() override = default;
	
	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

};

