#include "stdafx.h"
#include "TileMap.h"
#include <SceneGame.h>

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
	SetBackGround({ 20,35 }, { 32.f,32.f });
	SetSideLine({ 1,30 }, { 8.f,40.f });
	SetUpperLine({ 20,1 }, { 32.f,8.f });
	SetPosition({ 0.f,50.f });
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
	sf::RenderStates stateLeft;
	stateLeft.texture = this->texture;
	stateLeft.transform = this->transformLeft;
	sf::RenderStates stateRight;
	stateRight.texture = this->texture;
	stateRight.transform = this->transformRight;
	window.draw(tileBackground, state);
	window.draw(tileLeftSide, stateLeft);
	window.draw(tileRightSide, stateRight);
	window.draw(tileUpperSide, state);
	window.draw(tileLeftEdge, stateLeft);
	window.draw(tileRightEdge, stateRight);
}

void TileMap::SetBackGround(sf::Vector2i count, sf::Vector2f size)
{
	cellcount = count;
	cellsize = size;

	tileBackground.clear();
	tileBackground.setPrimitiveType(sf::Quads);
	tileBackground.resize(cellcount.x * cellcount.y * 4);
	// 각 사각형의 각 정점의 위치 오프셋
	sf::Vector2f posOffset[4] =
	{
		{0.f, 0.f},
		{size.x, 0.f},
		{size.x, size.y},
		{0.f, size.y}
	};
	// 타일의 텍스처 좌표를 정의
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
			if (dynamic_cast<SceneGame*>(SCENE_MGR.GetCurrentScene())->GetCurrentMode() == SceneGame::Mode::Infinity)
				texIdx = 3;
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
				tileBackground[vertexIdx].position = posOffset[k] + quadPos;
				// 텍스처 좌표 설정
				tileBackground[vertexIdx].texCoords = texCoord[k];
				// 어떤 텍스처 패턴 사용할건지 적용 
				tileBackground[vertexIdx].texCoords.y += texIdx * 32.f;
			}
		}
	}
}

void TileMap::SetSideLine(sf::Vector2i count, sf::Vector2f sideSize)
{
	tileLeftSide.clear();
	tileLeftSide.setPrimitiveType(sf::Quads);
	tileLeftSide.resize(count.x * count.y * 4);

	tileRightSide.clear();
	tileRightSide.setPrimitiveType(sf::Quads);
	tileRightSide.resize(count.x * count.y * 4);
	// 각 사각형의 각 정점의 위치 오프셋

	sf::Vector2f posOffset[4] =
	{
		{0.f, 0.f},
		{sideSize.x, 0.f},
		{sideSize.x,sideSize.y},
		{0.f, sideSize.y}
	};
	// 타일의 텍스처 좌표를 정의
	sf::Vector2f texCoord[4] =
	{
		{0.f, 0.f},
		{8.f, 0.f},
		{8.f,40.f},
		{0.f, 40.f}
	};
	for (int i = 0; i < count.y; i++)
	{
		for (int j = 0; j < count.x; j++)
		{
			//현재 타일의 인덱스
			int quadIdx = i * count.x + j;
			// 현재 타일의 좌표(좌측 상단으로 설정)	
			sf::Vector2f quadPos({ j * sideSize.x, i * sideSize.y });
			// 사각형을 나타내기 위해 4개의 정점을 생성하여 텍스쳐 그림
			for (int k = 0; k < 4; k++)
			{
				int vertexIdx = quadIdx * 4 + k;

				tileLeftSide[vertexIdx].position = posOffset[k] + quadPos;
				tileLeftSide[vertexIdx].texCoords = texCoord[k];
				tileLeftSide[vertexIdx].texCoords.x += 24.f;
				tileLeftSide[vertexIdx].texCoords.y += 128.f;

				tileRightSide[vertexIdx].position = posOffset[k] + quadPos;
				tileRightSide[vertexIdx].texCoords = texCoord[k];
				tileRightSide[vertexIdx].texCoords.x += 24.f;
				tileRightSide[vertexIdx].texCoords.y += 128.f;
			}
		}
	}

}

void TileMap::SetUpperLine(sf::Vector2i count, sf::Vector2f upperSize)
{
	tileUpperSide.clear();
	tileUpperSide.setPrimitiveType(sf::Quads);
	tileUpperSide.resize(count.x * count.y * 4);

	sf::Vector2f posOffset[4] =
	{
		{0.f, 0.f},
		{upperSize.x, 0.f},
		{ upperSize.x, upperSize.y },
		{0.f, upperSize.y}
	};

	sf::Vector2f texCoord[4] =
	{
		{0.f, 0.f},
		{32.f, 0.f},
		{ 32.f, 8.f },
		{0.f, 8.f}
	};

	for (int i = 0; i < count.y; i++)
	{
		for (int j = 0; j < count.x; j++)
		{
			int quadIdx = i * count.y + j;
			sf::Vector2f quadPos({ j * upperSize.x, i * upperSize.y });
			for (int k = 0; k < 4; k++)
			{
				int vertexIdx = quadIdx * 4 + k;

				tileUpperSide[vertexIdx].position = posOffset[k] + quadPos;
				tileUpperSide[vertexIdx].texCoords = texCoord[k];
				tileUpperSide[vertexIdx].texCoords.x += 56.f;
				tileUpperSide[vertexIdx].texCoords.y += 128.f;
			}
		}
	}

	{
		tileLeftEdge.clear();
		tileLeftEdge.setPrimitiveType(sf::Quads);
		tileLeftEdge.resize(4);

		tileRightEdge.clear();
		tileRightEdge.setPrimitiveType(sf::Quads);
		tileRightEdge.resize(4);

		sf::Vector2f posOffset[4] =
		{
			{0.f, 0.f},
			{8.f, 0.f},
			{8.f,8.f},
			{0.f, 8.f}
		};
		// 타일의 텍스처 좌표를 정의
		sf::Vector2f texCoord[4] =
		{
			{0.f, 0.f},
			{8.f, 0.f},
			{8.f,8.f},
			{0.f, 8.f}
		};

		for (int i = 0; i < 1; i++)
		{
			for (int j = 0; j < 1; j++)
			{
				int quadIdx = i * 1 + j;
				sf::Vector2f quadPos({ j * 8.f, i * 8.f });
				for (int k = 0; k < 4; k++)
				{
					int vertexIdx = quadIdx * 4 + k;

					tileLeftEdge[vertexIdx].position = posOffset[k] + quadPos;
					tileLeftEdge[vertexIdx].texCoords = texCoord[k];
					tileLeftEdge[vertexIdx].texCoords.x += 0.f;
					tileLeftEdge[vertexIdx].texCoords.y += 128.f;

					tileRightEdge[vertexIdx].position = posOffset[k] + quadPos;
					tileRightEdge[vertexIdx].texCoords = texCoord[k];
					tileRightEdge[vertexIdx].texCoords.x += 16.f;
					tileRightEdge[vertexIdx].texCoords.y += 128.f;
				}
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

	transformLeft = sf::Transform::Identity;
	transformLeft.translate({ position.x - cellcount.x * 0.4f ,position.y });
	transformLeft.rotate(rotation);
	transformLeft.scale(scale);
	transformLeft.translate(-origin);

	transformRight = sf::Transform::Identity;
	transformRight.translate({ position.x + cellcount.x * cellsize.x,position.y });
	transformRight.rotate(rotation);
	transformRight.scale(scale);
	transformRight.translate(-origin);
}
