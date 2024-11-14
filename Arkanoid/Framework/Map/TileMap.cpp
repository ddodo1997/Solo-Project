#include "stdafx.h"
#include "TileMap.h"

TileMap::TileMap(const std::string& name)
	: GameObject(name)
{
}

void TileMap::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
	UpdateTransform();
}

void TileMap::SetRotation(float angle)
{
	rotation = angle;
	UpdateTransform();
}

void TileMap::SetScale(const sf::Vector2f& s)
{
	scale = s;
	UpdateTransform();
}

void TileMap::SetOrigin(Origins preset)
{
	originPreset = preset;
	if (originPreset != Origins::Custom)
	{
		auto rect = GetLocalBounds();
		origin.x = rect.width * ((int)originPreset % 3) * 0.5f;
		origin.y = rect.height * ((int)originPreset / 3) * 0.5f;
	}

	UpdateTransform();
}

void TileMap::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;

	UpdateTransform();
}

sf::FloatRect TileMap::GetLocalBounds() const
{
	return { 0.f,0.f,cellsize.x * cellcount.x,cellsize.y * cellcount.y };
}

sf::FloatRect TileMap::GetGlobalBounds() const
{
	auto bounds = GetLocalBounds();
	return transform.transformRect(bounds);
}

void TileMap::Init()
{
	sortingLayer = SortingLayers::Background;
	sortingOrder = -1;
}

void TileMap::Release()
{
}

void TileMap::Reset()
{
	texture = &TEXTURE_MGR.Get(texTileMapId);
	Set({ 20,30 }, { 32.f,32.f });
	SetPosition({ 0.f,0.f });
	SetRotation(0.f);
	SetScale({ 1.f,1.f });
	SetOrigin(Origins::MC);
}

void TileMap::Update(float dt)
{
}

void TileMap::Draw(sf::RenderWindow& window)
{
	sf::RenderStates state;
	state.texture = this->texture;
	state.transform = this->transform;
	window.draw(va, state);
}

void TileMap::Set(sf::Vector2i count, sf::Vector2f size)
{
	cellcount = count;
	cellsize = size;

	va.clear();
	va.setPrimitiveType(sf::Quads);
	va.resize(cellcount.x * cellcount.y * 4);
	// 각 사각형의 각 정점의 위치 오프셋
	sf::Vector2f posOffset[4] =
	{
		{0.f, 0.f},
		{size.x, 0.f},
		{size.x, size.y},
		{0.f, size.y}
	};
	// 타일의 텍스처 좌표를 정의, 각 타일이 다르게 보이도록 임의의 텍스처 좌표를 사용
	sf::Vector2f texCoord[4] =
	{
		{0.f, 0.f},
		{32.f, 0.f},
		{32.f, 32.f},
		{0.f, 32.f}
	};
	for (int i = 0; i < cellcount.y; i++)
	{
		for (int j = 0; j < cellcount.x; j++)
		{
			int texIdx = 2;

			//현재 타일의 인덱스
			int quadIdx = i * cellcount.x + j;
			// 현재 타일의 좌표(좌측 상단으로 설정)	
			sf::Vector2f quadPos({ j * size.x, i * size.y });
			// 사각형을 나타내기 위해 4개의 정점을 생성하여 텍스쳐 그림
			for (int k = 0; k < 4; k++)
			{
				//현재 정점의 인덱스
				int vertexIdx = quadIdx * 4 + k;
				// 각 타일 기준 위치에서의 정점 위치 설정
				va[vertexIdx].position = posOffset[k] + quadPos;
				// 텍스처 좌표 설정
				va[vertexIdx].texCoords = texCoord[k];
				// 어떤 텍스처 패턴 사용할건지 적용 
				va[vertexIdx].texCoords.y += texIdx * 32.f;
			}
		}
	}
}

void TileMap::UpdateTransform()
{
	transform = sf::Transform::Identity;
	transform.translate(position);
	transform.rotate(rotation);
	transform.scale(scale);
	transform.translate(-origin);
}
