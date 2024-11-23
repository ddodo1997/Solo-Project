#include "stdafx.h"
#include "Boss1.h"
#include "SceneBoss1.h"
#include "Shuriken.h"
#include "Vause.h"
Boss1::Boss1(const std::string& name)
	: Boss(name)
{
}

void Boss1::SetPosition(const sf::Vector2f& pos)
{
	Boss::SetPosition(pos);
}

void Boss1::SetRotation(float angle)
{
	Boss::SetRotation(angle);
}

void Boss1::SetScale(const sf::Vector2f& s)
{
	Boss::SetScale(s);
}

void Boss1::SetOrigin(Origins preset)
{
	Boss::SetOrigin(preset);
}

void Boss1::SetOrigin(const sf::Vector2f& newOrigin)
{
	Boss::SetOrigin(newOrigin);
}

void Boss1::Init()
{
	Boss::Init();
}

void Boss1::Release()
{
	Boss::Release();
}

void Boss1::Reset()
{
	Boss::Reset();

	animator.Play("animations/Boss1/boss1_spawn.json");
	animator.PlayQueue("animations/Boss1/boss1_idle.json");
	SetOrigin({ body.getLocalBounds().width * 0.5f, body.getLocalBounds().height * 0.8f });

	SetScale({ 5.5f,5.5f });
	hitBox.UpdateBoss(body, body.getLocalBounds());
	PatternReset();
}

void Boss1::PatternReset()
{
	pattern1.attackTimer = 0.f;
	pattern1.attackingTimer = 0.f;
	pattern1.rapidTimer = 0.f;
	pattern1.attack = false;
	pattern1.attacking = false;
	pattern1.rapid = false;

	pattern2.rapidTimer = 0.f;

	pattern3.attackTimer = 0.f;
	pattern3.fireTimer = 0.f;
	pattern3.attack = false;
	pattern3.isReady = false;
}

void Boss1::Update(float dt)
{
	Boss::Update(dt);
	if (isDie())
		return;

	Pattern1(dt);

	if (hp > 25)
		return;

	Pattern2(dt);

	if (hp > 10)
		return;

	Pattern3(dt);
}

void Boss1::Pattern1(float dt)
{
	if (!pattern1.attack)
		pattern1.attackTimer += dt;
	else
	{
		pattern1.attackingTimer += dt;
		pattern1.rapidTimer += dt;
		if (pattern1.rapid)
		{
			dynamic_cast<SceneBoss1*>(sceneGame)->FireShuriken();
			pattern1.rapid = false;
		}
		if (pattern1.rapidDelay <= pattern1.rapidTimer)
		{
			pattern1.rapidTimer = 0.f;
			pattern1.rapid = true;
		}
		if (pattern1.attackingDelay <= pattern1.attackingTimer)
		{
			pattern1.rapid = false;
			pattern1.attacking = false;
			pattern1.attack = false;

			pattern1.attackingTimer = 0.f;
			pattern1.rapidTimer = 0.f;

			animator.Play("animations/Boss1/boss1_attack_rev.json");
			animator.PlayQueue("animations/Boss1/boss1_idle.json");
		}
	}
	if (pattern1.attackDelay <= pattern1.attackTimer)
	{
		pattern1.attackTimer = 0.f;
		Attack();
		pattern1.attack = true;
	}
}

void Boss1::Pattern2(float dt)
{
	pattern2.rapidTimer += dt;
	if (pattern2.rapidDelay <= pattern2.rapidTimer)
	{
		//공격
		dynamic_cast<SceneBoss1*>(sceneGame)->RainDrop();
		pattern2.rapidTimer = 0.f;
	}
}

void Boss1::Pattern3(float dt)
{
	if (!pattern3.attack)
		pattern3.attackTimer += dt;
	else
	{
		pattern3.fireTimer += dt;

		if (pattern3.fireTimer >= 1.5f)
			pattern3.isReady = true;

		if (pattern3.fireDelay <= pattern3.fireTimer)
		{
			//공격
			dynamic_cast<SceneBoss1*>(sceneGame)->ShootFireBall();
			pattern3.fireTimer = 0.f;
			pattern3.isReady = false;
			pattern3.attack = false;

			animator.Play("animations/Boss1/boss1_attack_rev.json");
			animator.PlayQueue("animations/Boss1/boss1_idle.json");
		}
	}

	if (pattern3.attackDelay <= pattern3.attackTimer)
	{
		pattern3.attackTimer = 0.f;
		Attack();
		pattern3.attack = true;
	}
}

void Boss1::Draw(sf::RenderWindow& window)
{
	Boss::Draw(window);
	if (pattern3.attack)
	{
		sf::VertexArray line(sf::Lines, 2);
		line[0].position = { position.x, position.y - 150.f };
		if (!pattern3.isReady)
		{
			pattern3.targetPos = dynamic_cast<SceneGame*>(SCENE_MGR.GetCurrentScene())->GetVause()->GetPosition();
		}
		line[1].position = pattern3.targetPos;

		line[0].color = sf::Color::White;
		line[1].color = sf::Color::White;

		window.draw(line);
	}
}

void Boss1::OnHit(sf::Vector2f pos, int damage)
{
	Boss::OnHit(pos, damage);
	animator.Play("animations/Boss1/boss1_hit.json");
	animator.PlayQueue("animations/Boss1/boss1_idle.json");
	animator.SetSpeed(1.f);

	if (isDie())
		OnDie();
}

void Boss1::Attack()
{
	animator.Play("animations/Boss1/boss1_attack.json");
	animator.SetSpeed(1.f);
}

void Boss1::OnDie()
{
	animator.Play("animations/Boss1/boss1_spawn.json");
	animator.SetSpeed(-1.f);
}