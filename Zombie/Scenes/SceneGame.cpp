#include "pch.h"
#include "SceneGame.h"
#include "Player.h"
#include "TileMap.h"
#include "Zombie.h"
#include "ZombieSpawner.h"
SceneGame::SceneGame(SceneIds id)
	:Scene(id)
{
}

void SceneGame::Init()
{
	

	
	spawners.push_back(new ZombieSpawner());
	spawners.push_back(new ZombieSpawner());

	for (auto s : spawners)
	{
		s->SetPosition(Utils::RandomOnUnitCircle() *  250.f);
		AddGo(s);
	}

	player = new Player("Player");
	AddGo(player);

	TileMap* tilemap = new TileMap("Background");
	tilemap->sortLayer = -1;
	AddGo(tilemap);

	Scene::Init();


}

void SceneGame::Release()
{
	Scene::Release();
}

void SceneGame::Enter()
{
	Scene::Enter();

	sf::Vector2f windowSize = (sf::Vector2f)FRAMEWORK.GetWindowSize();//사이즈
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
		TileMap* tilemap = dynamic_cast<TileMap*>(FindGo("Background"));
		 
		if (tilemap->sortLayer == 1)
		{
			tilemap->sortLayer = -1;
		}

		else {
			tilemap->sortLayer = 1;
		}
		ResortGo(tilemap);
		/*Zombie::Types zombieType = (Zombie::Types)Utils::RandomRange(0, Zombie::TotalTyps);
		Zombie* zombie = Zombie::Create(zombieType);
		zombie->Init();
		zombie->Reset();
		zombie->SetPosition(Utils::RandomInUnitCircle() * 500.f);
		AddGo(zombie);*/
	}

	//교수님꺼로 수정
	//std::vector<GameObject*> crashzombie;
	//for (auto obj : gameObjects)
	//{
	//	Zombie* zombie = dynamic_cast<Zombie*>(obj);
	//	if (zombie == obj)
	//	{
	//		//거리 계산
	//		float distance = Utils::Distance(player->GetPosition(), zombie->GetPosition());
	//		if (distance < 50.f)
	//		{
	//			crashzombie.push_back(zombie);
	//		}
	//	}
	//}
	//for (auto obj : crashzombie)
	//{
	//	//1번
	//	//gameObjects.remove(obj);
	//	
	//	//2번
	//	RemoveGo(obj);

	//	//3번
	//	//gameObjects.erase(std::remove(gameObjects.begin(), gameObjects.end(), obj), gameObjects.end());
	//	//delete obj;
	//}
	
}

void SceneGame::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
	window.setView(worldView);
}


/*
std::vector<GameObject*> toRemove;
	for (auto obj : gameObjects) // gameObjects는 모든 게임 오브젝트를 저장하고 있는 컨테이너
	{
		Zombie* zombie = dynamic_cast<Zombie*>(obj);
		if (zombie != nullptr) // 오브젝트가 좀비인 경우
		{
			float distance = Utils::Distance(player->GetPosition(), zombie->GetPosition()); // 플레이어와 좀비 사이의 거리 계산
			if (distance < 50.f) // someThreshold는 플레이어와 좀비가 충돌했다고 간주하는 거리
			{
				toRemove.push_back(zombie); // 삭제 대상에 추가
			}
		}
	}
	// 충돌한 좀비 제거
	for (auto obj : toRemove)
	{
		gameObjects.erase(std::remove(gameObjects.begin(), gameObjects.end(), obj), gameObjects.end());
		delete obj; // 메모리 해제
	}
	*/