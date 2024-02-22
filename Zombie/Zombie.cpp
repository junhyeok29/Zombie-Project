#include "pch.h"
#include "Zombie.h"

Zombie* Zombie::Create(Types zombieType)
{
	Zombie* zombie = new Zombie();
	zombie->type = zombieType;
	switch (zombieType)
	{
	case Zombie::Types::Bloater:
		zombie->textureId = "graphics/bloater.png";
		zombie->maxHp = 40;
		zombie->speed = 100;
		break;
	case Zombie::Types::Chaser:
		zombie->textureId = "graphics/chaser.png";
		zombie->maxHp = 70;
		zombie->speed = 75;
		break;
	case Zombie::Types::Crawler:
		zombie->textureId = "graphics/crawler.png";
		zombie->maxHp = 20;
		zombie->speed = 50;
		break;
	}
	return zombie;
}

Zombie::Zombie(const std::string& name)
	:SpriteGo(name)
{
}

void Zombie::Init()
{
	SpriteGo::Init();
	SetTexture(textureId);
	SetOrigin(Origins::MC);
}

void Zombie::Release()
{
	SpriteGo::Release();
}

void Zombie::Reset()
{
	SpriteGo::Reset();
	
	player = dynamic_cast<Player*>(SCENE_MGR.GetCurrentScene()->FindGo("Player"));
}

void Zombie::Update(float dt)
{
	SpriteGo::Update(dt);
	/*SetPosition(GetPosition() + Utils::GetNormal(player->GetPosition() - GetPosition()) * speed * dt);
	SetRotation(Utils::Angle(player->GetPosition() - position));*/

	//±³¼ö´Ô²¨
	direction = player->GetPosition() - position;
	Utils::Normalize(direction);
	Translate(direction * speed * dt);
	SetRotation(Utils::Angle(direction));


	//»èÁ¦ÄÚµå
	/*if (Utils::Distance(position, player->GetPosition()) < 50.f)
	{
		SCENE_MGR.GetCurrentScene()->RemoveGo(this);
	}*/

	//³» ²¨
	/*sf::Vector2f direction = player->GetPosition() - position;
	Utils::Normalize(direction);
	Translate(direction * speed * dt);
	SetRotation(Utils::Angle(direction));*/
}

void Zombie::Draw(sf::RenderWindow& window)
{
	SpriteGo::Draw(window);
}
