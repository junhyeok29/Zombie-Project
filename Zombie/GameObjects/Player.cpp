#include "pch.h"
#include "Player.h"

Player::Player(const std::string& name)
	:SpriteGo(name)
{
}

void Player::Init()
{
	SpriteGo::Init();
	SetTexture("graphics/player.png");
	SetOrigin(Origins::MC);
}

void Player::Release()
{
	SpriteGo::Release();
	

}

void Player::Reset()
{
	SpriteGo::Reset();
}

void Player::Update(float dt)
{
	SpriteGo::Update(dt);

	//�÷��̾ �ٶ󺸴� ������ vector

	sf::Vector2i mousePos = (sf::Vector2i)InputMgr::GetMousePos();
	sf::Vector2f mouseWorldPos = SCENE_MGR.GetCurrentScene()->ScreenoWorld(mousePos);
	look = mouseWorldPos - position;
	Utils::Normalize(look);  //lookVector�� ���� ȸ���Ѵ�.

	SetRotation(Utils::Angle(look));
	//float angle = Utils::Angle(look); //��׸��� �Ѿ�� ������ angle�� ����.
	//sprite.setRotation(angle);


	direction.x = InputMgr::GetAxis(Axis::Horizontal);
	direction.y = InputMgr::GetAxis(Axis::Vertical);
	if (Utils::Magnitude(direction) > 1.f)
	{
		Utils::Normalize(direction);
	}
	Translate(direction * speed * dt);

	//float h = InputMgr::GetAxis(Axis::Horizontal);  //�Է��� ������ 0
	//float y = InputMgr::GetAxis(Axis::Vertical);	//�Է��� ������ 0	
	//sf::Vector2f pos = sprite.getPosition();
	//pos.x += h * speed * dt;
	//pos.y += y * speed * dt;
	//sprite.setPosition(pos);

	//direction = mousePos - position;
	//Utils::Normalize(direction);
	//position += direction * speed * dt;
	//sprite.setPosition(position);

}

void Player::Draw(sf::RenderWindow& window)
{
	SpriteGo::Draw(window);
}
