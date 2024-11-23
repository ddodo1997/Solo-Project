#include "stdafx.h"
#include "Boss2.h"
#include "Vause.h"
#include "Bricks.h"
#include "SceneGame.h"
#include "SceneBoss2.h"
#include "TileMap.h"
#include "HeiHo.h"
Boss2::Boss2(const std::string& name)
	:Boss(name)
{
}

void Boss2::SetPosition(const sf::Vector2f& pos)
{
	Boss::SetPosition(pos);
}

void Boss2::SetRotation(float angle)
{
	Boss::SetRotation(angle);
}

void Boss2::SetScale(const sf::Vector2f& scale)
{
	Boss::SetScale(scale);
}

void Boss2::SetOrigin(Origins preset)
{
	Boss::SetOrigin(preset);
}

void Boss2::SetOrigin(const sf::Vector2f& newOrigin)
{
	Boss::SetOrigin(newOrigin);
}

void Boss2::Init()
{
	Boss::Init();
}

void Boss2::Release()
{
	Boss::Release();
}

void Boss2::Reset()
{
	Boss::Reset();
	animator.Play("animations/Boss2/boss2_spawn.json");

	SetOrigin(Origins::MC);

	SetPosition({ 0.f, -300.f });
	SetScale({ 5.5f, 5.5f });
	PatternReset();
	hp = 30;
}

void Boss2::PatternReset()
{
	pattern1.dropTimer = 0.f;
	pattern1.patternTimer = 0.f;
	pattern1.isButt = false;

	pattern2.accelTimer = 0.f;
	pattern2.isAccel = false;
	pattern2.isDecel = false;

	pattern3.isJumping = false;
	pattern3.jumpCnt = 0;
	pattern3.jumpTimer = 0.f;
}

void Boss2::Update(float dt)
{
	Boss::Update(dt);
	if (isDie())
		return;
	hitBox.UpdateTr(body, body.getLocalBounds());

	if (InputMgr::GetKey(sf::Keyboard::Num1))
		animator.Play("animations/Boss2/boss2_attack_left.json");
	if (InputMgr::GetKey(sf::Keyboard::Num2))
		animator.Play("animations/Boss2/boss2_attack_right.json");
	if (InputMgr::GetKey(sf::Keyboard::Num3))
		animator.Play("animations/Boss2/boss2_die.json");

	switch (currentPattern)
	{
	case Boss2::Pattern::None:
		//LookVause();
		patternTimer += dt;
		if (patternTimer >= patternDelay)
		{
			//SetPattern((Pattern)Utils::RandomRange(1, position.y < -200.f ? 2 : 3));
			SetPattern((Pattern)Utils::RandomRange(1, 1));
			patternTimer = 0.f;
		}
		break;
	case Boss2::Pattern::Pattern1:
		Pattern1(dt);
		break;
	case Boss2::Pattern::Pattern2:
		Pattern2(dt);
		break;
	case Boss2::Pattern::Pattern3:
		Pattern3(dt);
		break;
	}
}

void Boss2::Pattern1(float dt)
{
	if (!pattern1.isButt)
	{
		velocity += dt * 1000;
		return;
	}
	pattern1.patternTimer += dt;
	pattern1.dropTimer += dt;
	if (pattern1.patternDelay <= pattern1.patternTimer)
	{
		pattern1.isButt = false;
		SetPattern(Pattern::None);
		return;
	}
	if (pattern1.dropDelay <= pattern1.dropTimer)
	{
		pattern1.distance += body.getPosition().x > 0 ? -40.f : 40.f;
		auto xPos = body.getPosition().x > 0 ? body.getGlobalBounds().left + body.getGlobalBounds().width: body.getGlobalBounds().left;
		pattern1.dropTimer = 0.f;
		dynamic_cast<SceneBoss2*>(sceneGame)->SpawnHeiHo()->Drop({ xPos + pattern1.distance,-415.f },Utils::RandomRange(1,3));
	}
}

void Boss2::Pattern2(float dt)
{
	if (pattern2.isAccel)
	{
		pattern2.accelTimer += dt;
		if (pattern2.accelTimer >= pattern2.accelDelay)
		{
			pattern2.accelTimer = 0.f;
			pattern2.isDecel = true;
			pattern2.isAccel = false;
		}
		velocity += dt * 500;
	}

	if (pattern2.isDecel)
		velocity -= dt * 800;

	if (velocity < 0.f)
	{
		velocity = 0.f;
		SetPattern(Pattern::None);
	}
}

void Boss2::Pattern3(float dt)
{
	if (pattern3.jumpCnt < 3)
	{
		pattern3.jumpTimer += dt;
		if (pattern3.isJumping)
			velocity += dt * 750.f;
		if (pattern3.jumpDelay <= pattern3.jumpTimer)
		{
			animator.Play("animations/Boss2/boss2_spawn.json");
			animator.PlayQueue("animations/Boss2/boss2_attack_down.json");
			velocity = -500.f;
			pattern3.isJumping = true;
			pattern3.jumpTimer = 0.f;
		}
	}
	else
	{
		pattern3.isJumping = false;
		pattern3.jumpCnt = 0;
		SetPattern(Pattern::None);
	}
}

void Boss2::SetPattern(Pattern pattern)
{
	PatternReset();
	currentPattern = pattern;
	bool direction = Utils::RandomRange(0, 1);
	switch (currentPattern)
	{
	case Boss2::Pattern::None:
		this->direction = { 0.f,1.f };
		break;
	case Boss2::Pattern::Pattern1:
		Fire({ position.x > 0.f ? -1.f : 1.f, 0.f });
		pattern1.distance = 0.f;
		position.x > 0.f ? animator.Play("animations/Boss2/boss2_attack_left.json") : animator.Play("animations/Boss2/boss2_attack_right.json");
		break;
	case Boss2::Pattern::Pattern2:
		pattern2.isAccel = true;
		Fire({ direction ? -1.f : 1.f ,1.f });
		animator.Play("animations/Boss2/boss2_attack_down.json");
		break;
	case Boss2::Pattern::Pattern3:
		Fire({ 0,1.f });
		break;
	}
}

void Boss2::Fire(sf::Vector2f dir)
{
	direction = dir;
}

void Boss2::FixedUpdate(float dt)
{
	if (isDie())
		return;

	TileMap* map = sceneGame->GetMap();
	sf::FloatRect mapBounds = map->GetGlobalBounds();
	sf::FloatRect movableBounds = {
		mapBounds.left + 63.f,
		mapBounds.top + 90.f,
		mapBounds.width + mapBounds.left - 63.f,
		mapBounds.height + mapBounds.top - 95.f
	};


	if (position.x < movableBounds.left)
	{
		position.x = movableBounds.left;
		direction.x *= -1.f;
		Butt();
	}
	else if (position.x > movableBounds.width)
	{
		position.x = movableBounds.width;
		direction.x *= -1.f;
		Butt();
	}

	if (position.y < movableBounds.top)
	{
		position.y = movableBounds.top;
		direction.y *= -1.f;
		Butt();
	}
	for (auto& vec : sceneGame->GetBricks())
	{
		for (auto& brick : vec)
		{
			auto brickBounds = brick->GetGlobalBounds();
			if (hitBox.rect.getGlobalBounds().intersects(brickBounds))
			{
				position.y = brickBounds.top - 91.f;
				direction.y *= -1.f;
				Butt();
				if (currentPattern == Pattern::Pattern3)
				{
					pattern3.isJumping = false;
					pattern3.jumpCnt++;
					pattern3.jumpTimer = 0.f;
					direction.y = 1.f;
					velocity = 0.f;
				}
			}
		}
	}

	SetPosition(position + direction * velocity * dt);
}

void Boss2::Draw(sf::RenderWindow& window)
{
	Boss::Draw(window);
}

void Boss2::OnHit(sf::Vector2f pos, int damage)
{
	Boss::OnHit(pos, damage);
	animator.Play("animations/Boss2/boss2_onhit.json");
	LookVause();
	if (hp < 0)
		OnDie();
}

void Boss2::Attack()
{

}

void Boss2::OnDie()
{
	animator.Play("animations/Boss2/boss2_die.json");
}

void Boss2::LookVause()
{
	auto vauseXpos = sceneGame->GetVause()->GetPosition().x;
	if (vauseXpos > position.x + 60.f)
		animator.PlayQueue("animations/Boss2/boss2_look_right.json");
	else if (vauseXpos < position.x - 60.f)
		animator.PlayQueue("animations/Boss2/boss2_look_left.json");
	else
		animator.PlayQueue("animations/Boss2/boss2_look_down.json");
}

void Boss2::Butt()
{
	dynamic_cast<SceneBoss2*>(sceneGame)->Shake();
	SOUND_MGR.PlaySfx("sounds/Thwomp_Sound.wav");

	switch (currentPattern)
	{
	case Boss2::Pattern::Pattern1:
		velocity = 0;
		pattern1.isButt = true;
		pattern1.dropTimer = 0.f;
		pattern1.patternTimer = 0.f;
		break;
	case Boss2::Pattern::Pattern2:
		break;
	case Boss2::Pattern::Pattern3:
		break;
	default:
		break;
	}
}
