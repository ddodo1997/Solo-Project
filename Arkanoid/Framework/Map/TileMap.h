#pragma once

class TileMap : public GameObject
{
protected:
	sf::VertexArray tileBackground;
	sf::VertexArray tileLeftSide;
	sf::VertexArray tileRightSide;
	sf::VertexArray tileUpperSide;

	sf::VertexArray tileLeftEdge;
	sf::VertexArray tileRightEdge;


	sf::Texture* texture;
	std::string texTileMapId = "graphics/Arcade - Arkanoid - Blocks & Backgrounds.png";

	sf::Vector2i cellcount;
	sf::Vector2f cellsize;

	sf::Vector2f sideCellSize = { 8.f,40.f };
	sf::Vector2f upperCellSize = { 32.f, 8.f };

	sf::Transform transform;
	sf::Transform transformLeft;
	sf::Transform transformRight;
public:
	TileMap(const std::string& name = "");
	~TileMap() = default;

	void SetPosition(const sf::Vector2f& pos) override;
	void SetRotation(float angle) override;
	void SetScale(const sf::Vector2f& scale) override;

	void SetOrigin(Origins preset) override;
	void SetOrigin(const sf::Vector2f& newOrigin) override;

	sf::FloatRect GetLocalBounds()const override;
	sf::FloatRect GetGlobalBounds()const override;


	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	void SetBackGround(sf::Vector2i count, sf::Vector2f size);
	void SetSideLine(sf::Vector2i count, sf::Vector2f sideSize);
	void SetUpperLine(sf::Vector2i count, sf::Vector2f upperSize);

	sf::Vector2i GetCellCount() const { return cellcount; }
	sf::Vector2f GetCellSize() const { return cellsize; }
	void UpdateTransform();
};
