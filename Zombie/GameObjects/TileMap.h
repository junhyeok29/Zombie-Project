#pragma once
#include "GameObject.h"
class TileMap : public GameObject
{

protected:
	sf::VertexArray va;
	std::string spriteSheetId; //아틀라스,spriteSheetId라 불린다.
	//여러개 시트를 모아둔 것
	sf::Texture* texture;

	int rows = 10;
	int cols = 10;

	sf::Vector2i cellCount; //가로 갯수
	sf::Vector2f cellSize; // 사이즈
	sf::Transform transform;

public:
	TileMap(const std::string& name = "");

	void Set(const sf::Vector2i& count, const sf::Vector2f& size);
	void SetSpriteSheeId(const std::string& id);
	void UpdateTransform();

	void SetOrigin(Origins preset) override;
	void SetOrigin(const sf::Vector2f& newOrigin)override;
	
	void SetPosition(const sf::Vector2f& pos)override;

	void SetScale(const sf::Vector2f& scale)override;

	void Translate(const sf::Vector2f& delta)override;

	void SetFlipX(bool flip)override;
	void SetFlipY(bool flip)override;
	void SetRotation(float r)override;

	void Init() override;
	void Release() override;

	void Reset() override;

	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	
};

