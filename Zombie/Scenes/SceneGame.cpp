#include "pch.h"
#include "SceneGame.h"
#include "Player.h"
#include "TileMap.h"
#include "Zombie.h"
SceneGame::SceneGame(SceneIds id)
	:Scene(id)
{
}

void SceneGame::Init()
{
	AddGo(new TileMap("Background"));

	player = new Player("Player");
	AddGo(player);
	Scene::Init();
}

void SceneGame::Release()
{
	Scene::Release();
}

void SceneGame::Enter()
{
	Scene::Enter();

	sf::Vector2f windowSize = (sf::Vector2f)FRAMEWORK.GetWindowSize();//������
	sf::Vector2f centerPos = windowSize * 0.5f;
	worldView.setSize(windowSize);
	worldView.setCenter({ 0.f, 0.f });
	uiView.setSize(windowSize);
	uiView.setCenter(centerPos);

	TileMap* tileMap = dynamic_cast<TileMap*>(FindGo("Background"));
	
	tileMap->SetPosition({ 0.f, 0.f });
	tileMap->SetOrigin(Origins::MC);
	player->SetPosition({ 0.f, 0.f });
	//tileMap->SetScale({ 0.5f, 0.5f });
	//tileMap->SetRotation(45);
	//tileMap->UpdateTransform();
	
}

void SceneGame::Exit()
{
	Scene::Exit();
}

void SceneGame::Update(float dt)
{
	Scene::Update(dt);
	worldView.setCenter(player->GetPosition());

	if (InputMgr::GetKeyDown(sf::Keyboard::Space))
	{
		Zombie::Types zombieType = (Zombie::Types)Utils::RandomRange(0, Zombie::TotalTyps);
		Zombie* zombie = Zombie::Create(zombieType);
		zombie->Init();
		zombie->Reset();
		zombie->SetPosition(Utils::RandomInUnitCircle() * 500.f);
		AddGo(zombie);
	}

	std::vector<GameObject*> crashzombie;
	for (auto obj : gameObjects)
	{
		Zombie* zombie = dynamic_cast<Zombie*>(obj);
		if (zombie == obj)
		{
			//�Ÿ� ���
			float distance = Utils::Distance(player->GetPosition(), zombie->GetPosition());
			if (distance < 50.f)
			{
				crashzombie.push_back(zombie);
			}
		}
	}
	for (auto obj : crashzombie)
	{
		gameObjects.erase(std::remove(gameObjects.begin(), gameObjects.end(), obj), gameObjects.end());
		delete obj;
	}
	
}

void SceneGame::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
	window.setView(worldView);
}


/*
std::vector<GameObject*> toRemove;
	for (auto obj : gameObjects) // gameObjects�� ��� ���� ������Ʈ�� �����ϰ� �ִ� �����̳�
	{
		Zombie* zombie = dynamic_cast<Zombie*>(obj);
		if (zombie != nullptr) // ������Ʈ�� ������ ���
		{
			float distance = Utils::Distance(player->GetPosition(), zombie->GetPosition()); // �÷��̾�� ���� ������ �Ÿ� ���
			if (distance < 50.f) // someThreshold�� �÷��̾�� ���� �浹�ߴٰ� �����ϴ� �Ÿ�
			{
				toRemove.push_back(zombie); // ���� ��� �߰�
			}
		}
	}
	// �浹�� ���� ����
	for (auto obj : toRemove)
	{
		gameObjects.erase(std::remove(gameObjects.begin(), gameObjects.end(), obj), gameObjects.end());
		delete obj; // �޸� ����
	}
	*/