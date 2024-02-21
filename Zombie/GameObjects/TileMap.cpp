#include "pch.h"
#include "TileMap.h"

TileMap::TileMap(const std::string& name)
	: GameObject(name)
{
}

void TileMap::Set(const sf::Vector2i& count, const sf::Vector2f& size)
{
	cellCount = count;
	cellSize = size;

	va.clear(); //값이 들어있을 수 있기 때문에 클리어를 해준다.
	va.setPrimitiveType(sf::Quads); //이게 뭐징
	va.resize(count.x * count.y * 4); //vertex 실제 사이즈의 생성

	sf::Vector2f posOffsets[4] = {
		{ 0, 0 },
		{ size.x, 0 },
		{ size.x, size.y },
		{ 0, size.y },
	};

	sf::Vector2f texCoord0[4] = {
		{ 0, 0 },
		{ 50.f, 0 },
		{ 50.f, 50.f },
		{ 0, 50.f },
	};


	//sf::Vector2f pos = position; //GameObject의 포지션
	for (int i = 0; i < count.y; i++)
	{
		for (int j = 0; j < count.x; j++)
		{
			int texIndex = Utils::RandomRange(0, 3);
			if (i == 0 || i == count.y - 1 || j == 0 || j == count.x - 1)
			{
				texIndex = 3;
			}

			int quadIndex = i * count.x + j; //2차원 배열을 1차원으로?
			sf::Vector2f quadpos(size.x * j, size.y * i); //각 각 사각형의 좌상점
			

			for (int k = 0; k < 4; k++) //사각형의 4개의 정점을 구하는 식
			{
				int vertexIndex = (quadIndex * 4) + k;
				va[vertexIndex].position = quadpos +  posOffsets[k];
				va[vertexIndex].texCoords = texCoord0[k];
				va[vertexIndex].texCoords.y += texIndex * 50.f;
			} // texCoords 그림 코드
			
		}
		
	}
}

void TileMap::SetSpriteSheeId(const std::string& id)
{
	spriteSheetId = id;
	texture = &RES_MGR_TEXTURE.Get(spriteSheetId);

}

void TileMap::UpdateTransform()
{
	transform = sf::Transform::Identity;
	float scaleX = isFlipX ? -scale.x : scale.x;
	float scaleY = isFlipY ? -scale.y : scale.y;
	transform.scale(scaleX, scaleY, position.x, position.y);
	transform.rotate(rotation, position);
	transform.translate(position - origin);
	
}

void TileMap::SetOrigin(Origins preset)
{
	if (preset == Origins::Custom)
		return;
	originPreset = preset;
	//sf::Vector2f prevOrigin = origin;
	sf::FloatRect bound = va.getBounds();
	origin.x = bound.width * ((int)originPreset % 3) * 0.5f; // 0 1 2 => 0 0.5 1
	origin.y = bound.height * ((int)originPreset / 3) * 0.5f; // 0 1 2 => 0 0.5 1
	UpdateTransform();

	/*auto delta = prevOrigin - origin;
	for (int i = 0; i < va.getVertexCount(); i++)
	{
		va[i].position += delta;
	}*/
}

void TileMap::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
	origin = newOrigin;
	UpdateTransform();
}

void TileMap::SetPosition(const sf::Vector2f& pos)
{
	GameObject::Translate(pos);
	UpdateTransform();
}

void TileMap::Translate(const sf::Vector2f& delta)
{
	GameObject::Translate(delta);
	UpdateTransform();
}
void TileMap::SetScale(const sf::Vector2f& scale)
{
	GameObject::SetScale(scale);
	UpdateTransform();
}


void TileMap::SetFlipX(bool flip)
{
	GameObject::SetFlipX(flip);
	UpdateTransform();
}

void TileMap::SetFlipY(bool flip)
{
	GameObject::SetFlipY(flip);
	UpdateTransform();
}
void TileMap::SetRotation(float r)
{
	GameObject::SetRotation(r);
	UpdateTransform();
}
void TileMap::Init()
{
	GameObject::Init();
	SetSpriteSheeId("graphics/background_sheet.png");
	Set({ 10, 10 }, { 50.f, 50.f });
	SetOrigin(Origins::MC);


}

void TileMap::Release()
{
	GameObject::Release();
}

void TileMap::Reset()
{
	GameObject::Reset();
}

void TileMap::Update(float dt)
{
	GameObject::Update(dt);
}

void TileMap::Draw(sf::RenderWindow& window)
{
	//GameObject::Draw(window);
	sf::RenderStates state;
	state.texture = texture;
	state.transform = transform;
	window.draw(va, state);
}
