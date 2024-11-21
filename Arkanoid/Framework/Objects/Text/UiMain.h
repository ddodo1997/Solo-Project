#pragma once

class UiMain : public GameObject
{
private:
	enum class Select
	{
		Normal,
		Infinity,
		Boss,
		Exit,
	};
	static const int TotalSelect = 2;
protected:
	sf::Text txtDev;
	sf::Text txtmainTitle;
	sf::Text txtNormal;
	sf::Text txtInfinity;
	sf::Text txtBoss;
	sf::Text txtExit;

	sf::Text txtArrow;

	Select currentSelect = Select::Normal;
public:
	UiMain(const std::string& name = "");
	~UiMain() = default;

	void SetPosition(const sf::Vector2f& pos) override;
	void SetRotation(float angle) override;
	void SetScale(const sf::Vector2f& scale) override;

	void SetOrigin(Origins preset) override;
	void SetOrigin(const sf::Vector2f& newOrigin) override;

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;
};