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
	// �� �簢���� �� ������ ��ġ ������
	sf::Vector2f posOffset[4] =
	{
		{0.f, 0.f},
		{size.x, 0.f},
		{size.x, size.y},
		{0.f, size.y}
	};
	// Ÿ���� �ؽ�ó ��ǥ�� ����, �� Ÿ���� �ٸ��� ���̵��� ������ �ؽ�ó ��ǥ�� ���
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

			//���� Ÿ���� �ε���
			int quadIdx = i * cellcount.x + j;
			// ���� Ÿ���� ��ǥ(���� ������� ����)	
			sf::Vector2f quadPos({ j * size.x, i * size.y });
			// �簢���� ��Ÿ���� ���� 4���� ������ �����Ͽ� �ؽ��� �׸�
			for (int k = 0; k < 4; k++)
			{
				//���� ������ �ε���
				int vertexIdx = quadIdx * 4 + k;
				// �� Ÿ�� ���� ��ġ������ ���� ��ġ ����
				va[vertexIdx].position = posOffset[k] + quadPos;
				// �ؽ�ó ��ǥ ����
				va[vertexIdx].texCoords = texCoord[k];
				// � �ؽ�ó ���� ����Ұ��� ���� 
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
