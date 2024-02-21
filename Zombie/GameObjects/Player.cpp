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

	//플레이어가 바라보는 방향의 vector

	sf::Vector2i mousePos = (sf::Vector2i)InputMgr::GetMousePos();
	sf::Vector2f mouseWorldPos = SCENE_MGR.GetCurrentScene()->ScreenoWorld(mousePos);
	look = mouseWorldPos - position;
	Utils::Normalize(look);  //lookVector에 맞춰 회전한다.

	SetRotation(Utils::Angle(look));
	//float angle = Utils::Angle(look); //디그리로 넘어온 각도가 angle에 담긴다.
	//sprite.setRotation(angle);


	direction.x = InputMgr::GetAxis(Axis::Horizontal);
	direction.y = InputMgr::GetAxis(Axis::Vertical);
	if (Utils::Magnitude(direction) > 1.f)
	{
		Utils::Normalize(direction);
	}
	Translate(direction * speed * dt);

	//float h = InputMgr::GetAxis(Axis::Horizontal);  //입력이 없으면 0
	//float y = InputMgr::GetAxis(Axis::Vertical);	//입력이 없으면 0	
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
