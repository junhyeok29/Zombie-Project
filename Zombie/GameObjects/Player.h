#pragma once
#include "SpriteGo.h"

//�ٶ󺸴� ���� 6Vector
//taget - ������ 
/*

*/
class Player : public SpriteGo
{
protected:
	sf::Vector2f player;
	sf::Vector2f direction = { 0.f, 0.f };		//����
	sf::Vector2f look = { 1.0f, 0.f };			//ȸ��  
	float speed = 500.f;

	std::string textureId;

public:
	Player(const std::string& name = "");
	~Player() override = default; //�ֽ� �Ҹ��� ����

	void Init() override;
	void Release() override;

	void Reset() override;

	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;
};

