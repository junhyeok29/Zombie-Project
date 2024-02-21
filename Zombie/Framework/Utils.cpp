#include "pch.h"
#include "Utils.h"

float Utils::Clamp(float v, float min, float max)
{
	if (v < min)
		return min;
	if (v > max)
		return max;
	return v;
}

float Utils::RandomValue()
{
	return (float)rand() / RAND_MAX;
}

float Utils::RandomRange(float min, float max)
{
	float value = RandomValue();
	value *= max - min;	
	value += min;
	return value;
}

sf::Vector2f Utils::RandomOnUnitCircle()
{
	sf::Transform rotation;
	rotation.rotate(RandomRange(0.f, 360.f));
	return rotation * sf::Vector2f (1.f, 0.f);
}

sf::Vector2f Utils::RandomInUnitCircle()
{
	return RandomOnUnitCircle() * RandomValue();
}

int Utils::RandomRange(int min, int maxExclude)
{
	int range = maxExclude - min;
	int rand = std::rand() % range;
	rand += min;
	return rand;
}

sf::Vector2f Utils::SetOrigin(sf::Transformable& obj, Origins originPreset, const sf::FloatRect& rect)
{
	// Rect Width, Height
	sf::Vector2f newOrigin(rect.width, rect.height);
	newOrigin.x *= ((int)originPreset % 3) * 0.5f; // 0 1 2 => 0 0.5 1
	newOrigin.y *= ((int)originPreset / 3) * 0.5f; // 0 1 2 => 0 0.5 1
	obj.setOrigin(newOrigin);

	return newOrigin;
}

sf::Vector2f Utils::SetOrigin(sf::Sprite& obj, Origins originPreset)
{
	return SetOrigin(obj, originPreset, obj.getLocalBounds());
}

sf::Vector2f Utils::SetOrigin(sf::Text& obj, Origins originPreset)
{
	return SetOrigin(obj, originPreset, obj.getLocalBounds());
}

sf::Vector2f Utils::SetOrigin(sf::Shape& obj, Origins originPreset)
{
	return SetOrigin(obj, originPreset, obj.getLocalBounds());
}

float Utils::SprMagnitude(const sf::Vector2f& vec)
{
	return vec.x * vec.x + vec.y * vec.y;
}

float Utils::Magnitude(const sf::Vector2f& vec)
{
	return std::sqrt(vec.x * vec.x + vec.y * vec.y); //sqrt 루트  
}

void Utils::Normalize(sf::Vector2f& vec) //정규화
{ //스칼라 나누기 길이를 1로 만드는 방법
	float mag = Magnitude(vec);
	if (mag != 0.f)
	{
		vec /= mag;
	}
	//return vec / Magnitude(vec); //0으로 나오면 예외라 예외처리를 해야한다.
}

sf::Vector2f Utils::GetNormal(const sf::Vector2f& vec)
{
	float mag = Magnitude(vec);
	if (mag == 0.f)
		return vec;
	return vec / mag;
}

float Utils::Distance(const sf::Vector2f& p1, const sf::Vector2f& p2) 
{
	return Magnitude(p2 - p1); 
	//몬스터와 플레이어의 거리를 구한다.
	//몬스터와 플레이어의 거리가 가까우면 몬스터가 따라오게 만들 것이다.
}

float Utils::RadianToDegree(float radian)
{
	return radian * (180.f / M_PI);
}

float Utils::DegreeToRadian(float degree)
{
	return degree * (M_PI / 180.f);
}

float Utils::Angle(const sf::Vector2f& vec)
{
	return RadianToDegree(std::atan2f(vec.y , vec.x)); 
	//std::atan2f(vec.y , vec.x) 나온 값을 RadianToDegree로 변환
}
