#pragma once
#include <SFML/Graphics.hpp>
#include "EntityManager.h"
#include "Entity.h"
#include <iostream> 
#include <SFML/Window/Event.hpp>
class Game
{
	sf::RenderWindow m_window;
	EntityManager m_entities;
	bool m_running = true;
	int m_currentFrame = 0;
	int m_lastEnemySpawnTime = 0;
	float m_deltaTime;
	sf::Clock clock;
	int m_playerlives = 3;
	

	void init();
	void sRender();
	void sMovement();
	void sEnemySpawner();
	void sUserInput();
	void sCollision();
	void spawnEnemy();
	void spawnPlayer();
	void spawnBullet(std::shared_ptr<Entity>, const Vec2& target);
	bool isColliding(const std::shared_ptr<Entity>& a, const std::shared_ptr<Entity>& b);
	float m_enemySpawnTimer = 0.f;
	float m_enemySpawnInterval = 1.f;
	
public:
	std::shared_ptr<Entity> m_player;
	Game();

	void run();
};

