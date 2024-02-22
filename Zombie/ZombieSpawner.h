#pragma once
#include "GameObject.h"
#include "Zombie.h"

class ZombieSpawner : public GameObject
{
protected:
	std::vector<Zombie::Types> zombieTypes;// ���� Ÿ���� ������ ����

	float interval = 1.f;
	int spawnCount = 1;
	float radius = 250.f; //���� �ݰ�

	float timer = 0.f;
	//float intervalMin;
	//float intervalMax;

	//int spawnCountMin;
	//int spawnCountMax;


public:
	ZombieSpawner(const std::string& name = "");
	~ZombieSpawner() override = default;

	void Init()override;
	void Release()override;

	void Reset()override;

	void Update(float dt)override;

};

