#include "pch.h"
#include "Scene.h"

Scene::Scene(SceneIds id) :
	id(id),
	texResMgr(RES_MGR_TEXTURE),
	fontResMgr(RES_MGR_FONT),
	soundResMgr(RES_MGR_SOUND_BUFFER)
{
}

sf::Vector2f Scene::ScreenoWorld(sf::Vector2i screenPos)
{
	return FRAMEWORK.GetWindow().mapPixelToCoords(screenPos, worldView);
}

sf::Vector2i Scene::WorldToScreen(sf::Vector2f worldPos)
{
	return FRAMEWORK.GetWindow().mapCoordsToPixel(worldPos, worldView);
}

sf::Vector2f Scene::ScreenToUi(sf::Vector2i screenPos)
{
	return FRAMEWORK.GetWindow().mapPixelToCoords(screenPos, uiView);
}

sf::Vector2i Scene::UiToScreen(sf::Vector2f uiPos)
{
	return FRAMEWORK.GetWindow().mapCoordsToPixel(uiPos, uiView);
}




void Scene::Init() //���� ������Ʈ���� ��ȸ�ϸ鼭 ����ٰ� Init�����
{
	for (auto obj : gameObjects)
	{
		obj->Init();
	}
	for (auto obj : uiGameObjects)
	{
		obj->Init();
	}
}

void Scene::Release()
{
	for (auto obj : gameObjects)
	{
		delete obj;
	}
	gameObjects.clear();
	for (auto obj : uiGameObjects)
	{
		delete obj;
	}
}

void Scene::Enter()
{
	for (auto obj : gameObjects)
	{
		obj->Reset();
	}
	for (auto obj : uiGameObjects)
	{
		obj->Reset();
	}
}

void Scene::Update(float dt)
{
	for (auto obj : gameObjects)
	{
		if (obj->GetActive())
		{
			obj->Update(dt);
		}
	}
	for (auto obj : uiGameObjects)
	{
		if (obj->GetActive())
		{
			obj->Update(dt);
		}
	}

	for (auto obj : resortingGameObjects)
	{
		auto it = std::find(gameObjects.begin(), gameObjects.end(), obj); //���ͷ�����
		if (it != gameObjects.end())//ã�� ��Ȳ
		{
			gameObjects.remove(obj);
			AddGo(obj, Layers::World);
			continue;
		}
		it = std::find(uiGameObjects.begin(), uiGameObjects.end(), obj); //���ͷ�����
		if (it != uiGameObjects.end())//ã�� ��Ȳ
		{
			uiGameObjects.remove(obj);
			AddGo(obj, Layers::Ui);
			continue;
		}
		resortingGameObjects.clear();
	}

	//��� ������Ʈ�� ���� �Ŀ� ���ο� �ݺ����� ���� �����.
	for (auto obj : removeGameObjects)
	{
		gameObjects.remove(obj);
		uiGameObjects.remove(obj);
		delete obj;
	}
	removeGameObjects.clear();
}

void Scene::Draw(sf::RenderWindow& window)
{
	/*gameObjects.sort([](auto a, auto b) {
		if (a->sortLayer != b->sortLayer)
		{
			return a->sortLayer < b->sortLayer;
		}
		return a->sortOrder < b->sortOrder;
		});
	uiGameObjects.sort([](auto a, auto b) {
		if (a->sortLayer != b->sortLayer)
		{
			return a->sortLayer < b->sortLayer;
		}
		return a->sortOrder < b->sortOrder;
		});*/

	//���ٸ� ������ ���� �߻� ������ ������ ���� ������
	//���ٽ� �̸����� �Լ���  ���ӿ�����Ʈ �ȿ� ���ִ� �ֵ��� �����ϰ� ������ 
	//������ ������ ��� sort�� ���ٽ����� �����ؼ� ���������.
	//���ٽ� ������ �� ���̴�. [](�Ű�����) {�Լ� �ۼ�}�Լ� ����
	//std::sort(gameObjects.begin(), gameObjects.end(),
	//	[](GameObject* a, GameObject* b) {
	//		//a < b
	//		if (a->sortLayer != b->sortLayer)
	//		{
	//			return a->sortLayer < b->sortLayer;
	//		}
	//		return a->sortOrder < b->sortOrder;
	//	}); //sort�����Լ�

	//std::sort(uiGameObjects.begin(), uiGameObjects.end(), //sort�����Լ�
	//	[](GameObject* a, GameObject* b) {
	//		//a < b
	//		if (a->sortLayer != b->sortLayer)
	//		{
	//			return a->sortLayer < b->sortLayer;
	//		}
	//		return a->sortOrder < b->sortOrder;
	//	}); //sort�����Լ�	

	const sf::View& saveView = window.getView();

	window.setView(worldView);
	for (auto obj : gameObjects)
	{
		if (obj->GetActive())
		{
			obj->Draw(window);
		}
	}
	window.setView(uiView);
	for (auto obj : uiGameObjects)
	{
		if (obj->GetActive())
		{
			obj->Draw(window);
		}
	}
	window.setView(saveView);
}

GameObject* Scene::FindGo(const std::string& name, Layers layer)
{
	if ((layer & Layers::World) == Layers::World)
	{
		for (auto obj : gameObjects)
		{
			if (obj->name == name)
			{
				return obj;
			}
		}
	}
	if ((layer & Layers::Ui) == Layers::Ui)
	{
		for (auto obj : uiGameObjects)
		{
			if (obj->name == name)
			{
				return obj;
			}
		}
	}

	return nullptr;
}

int Scene::FindGoAll(const std::string& name, std::list<GameObject*>& list, Layers layer)
{
	list.clear();
	if ((layer & Layers::World) == Layers::World)
	{
		for (auto obj : gameObjects)
		{
			if (obj->name == name)
			{
				list.push_back(obj);
			}
		}
	}
	if ((layer & Layers::Ui) == Layers::Ui)
	{
		for (auto obj : uiGameObjects)
		{
			if (obj->name == name)
			{
				list.push_back(obj);
			}
		}
	}

	return list.size();
}

GameObject* Scene::AddGo(GameObject* obj, Layers layer)
{
	if (layer == Layers::World)
	{
		//���ͷ����� ��ȸ
		if (std::find(gameObjects.begin(), gameObjects.end(), obj) == gameObjects.end())
		{
			auto it = gameObjects.begin();
			while (it != gameObjects.end()) //��� ���鼭 ���� �ڸ� ����
			{
				if (GameObject::CompareDrawOrder(obj, *it))
				{
					gameObjects.insert(it, obj);
					return obj;
				}
				++it;
			}
			gameObjects.push_back(obj);
			return obj;
		}
	}
	if (layer == Layers::Ui)
	{
		if (std::find(uiGameObjects.begin(), uiGameObjects.end(), obj) == uiGameObjects.end())
		{
			auto it = uiGameObjects.begin();
			while (it != uiGameObjects.end()) //��� ���鼭 ���� �ڸ� ����
			{
				if (GameObject::CompareDrawOrder(obj, *it))
				{
					uiGameObjects.insert(it, obj);
					return obj;
				}
				++it;
			}
			uiGameObjects.insert(it, obj);
			return obj;
		}
	}

	return nullptr;
}

void Scene::ResortGo(GameObject* obj)
{
	resortingGameObjects.push_back(obj);
}

void Scene::RemoveGo(GameObject* obj)
{
	//obj->SetActive(false);
	removeGameObjects.push_back(obj);

	//1�� 2�� 3�� �ڵ�
	/*gameObjects.remove(obj);
	uiGameObjects.remove(obj);*/
}
