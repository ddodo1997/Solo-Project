#include "stdafx.h"
#include "Boss.h"
#include <SceneBoss.h>
#include "Shuriken.h"
#include "Vause.h"
Boss::Boss(const std::string& name)
	: GameObject(name)
{
}

void Boss::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
	body.setPosition(position);
}

void Boss::SetRotation(float angle)
{
	rotation = angle;
	body.setRotation(rotation);
}

void Boss::SetScale(const sf::Vector2f& s)
{
	scale = s;
	body.setScale(scale);
}

void Boss::SetOrigin(Origins preset)
{
	originPreset = preset;
	if (originPreset != Origins::Custom)
	{
		origin = Utils::SetOrigin(body, originPreset);
	}
}

void Boss::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
	origin = newOrigin;
	body.setOrigin(origin);
}

void Boss::Init()
{
	sortingLayer = SortingLayers::Foreground;
	sortingOrder = -3;
}

void Boss::Release()
{

}

void Boss::Reset()
{
	sceneGame = dynamic_cast<SceneGame*>(SCENE_MGR.GetCurrentScene());
	SetScale({ 5.5f,5.5f });


	animator.SetTarget(&body);
	animator.Play("animations/boss_spawn.json");
	animator.PlayQueue("animations/boss_idle.json");
	SetOrigin({ body.getLocalBounds().width * 0.5f, body.getLocalBounds().height * 0.8f });

	hitBox.UpdateBoss(body, body.getLocalBounds());
	PatternReset();
}

void Boss::PatternReset()
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

void Boss::Update(float dt)
{
	animator.Update(dt);
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

void Boss::Pattern1(float dt)
{
	if (!pattern1.attack)
		pattern1.attackTimer += dt;
	else
	{
		pattern1.attackingTimer += dt;
		pattern1.rapidTimer += dt;
		if (pattern1.rapid)
		{
			dynamic_cast<SceneBoss*>(sceneGame)->FireShuriken();
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

			animator.Play("animations/boss_attack_rev.json");
			animator.PlayQueue("animations/boss_idle.json");
		}
	}
	if (pattern1.attackDelay <= pattern1.attackTimer)
	{
		pattern1.attackTimer = 0.f;
		Attack();
		pattern1.attack = true;
	}
}

void Boss::Pattern2(float dt)
{
	pattern2.rapidTimer += dt;
	if (pattern2.rapidDelay <= pattern2.rapidTimer)
	{
		//공격
		dynamic_cast<SceneBoss*>(sceneGame)->RainDrop();
		pattern2.rapidTimer = 0.f;
	}
}

void Boss::Pattern3(float dt)
{
	if (!pattern3.attack)
		pattern3.attackTimer += dt;
	else
	{
		pattern3.fireTimer += dt;

		if(pattern3.fireTimer >= 1.5f)
			pattern3.isReady = true;

		if (pattern3.fireDelay <= pattern3.fireTimer)
		{
			//공격
			dynamic_cast<SceneBoss*>(sceneGame)->ShootFireBall();
			pattern3.fireTimer = 0.f;
			pattern3.isReady = false;
			pattern3.attack = false;

			animator.Play("animations/boss_attack_rev.json");
			animator.PlayQueue("animations/boss_idle.json");
		}
	}

	if (pattern3.attackDelay <= pattern3.attackTimer)
	{
		pattern3.attackTimer = 0.f;
		Attack();
		pattern3.attack = true;
	}
}

void Boss::Draw(sf::RenderWindow& window)
{
	window.draw(body);
	hitBox.Draw(window);
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

void Boss::OnHit(sf::Vector2f pos)
{
	SOUND_MGR.PlaySfx("sounds/Arkanoid_boss_hit.wav");
	animator.Play("animations/boss_hit.json");
	animator.PlayQueue("animations/boss_idle.json");
	animator.SetSpeed(1.f);
	sceneGame->SpawnItem(pos);
	hp--;

	if (isDie())
		OnDie();
}

void Boss::Attack()
{
	animator.Play("animations/boss_attack.json");
	animator.SetSpeed(1.f);
}

void Boss::OnDie()
{
	animator.Play("animations/boss_spawn.json");
	animator.SetSpeed(-1.f);
}