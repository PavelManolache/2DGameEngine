#include "Game.h"

Game::Game()
{
	init();

}

void Game::init()
{

	m_window.create(sf::VideoMode({1280, 720}), "asd");
	m_window.setFramerateLimit(60);

	spawnPlayer();
	
	
};

void Game::run()
{
	
	while (m_running) 
	{
		m_deltaTime = clock.restart().asSeconds();
		

		m_entities.update();
		sUserInput();
		sRender();
		sMovement();
		sEnemySpawner();
		sCollision();
		
	};

};

void Game::spawnPlayer() 
{
	 auto entity = m_entities.addEntity("player");
	 float mx = m_window.getSize().x / 2.f;

	 float my = m_window.getSize().y / 2.f;


	 entity->cShape = std::make_shared<CShape>(10.0f, 5, sf::Color(10, 10, 10), sf::Color(255, 0, 0), 4.0f);
	 entity->cTransform = std::make_shared<CTransform>(Vec2(mx,my), Vec2(0,0), 0);
	 entity->cInput = std::make_shared<CInput>();
	 m_player = entity;

	
};

void Game::spawnBullet(std::shared_ptr<Entity> ,  const Vec2 & target)
{

	auto entity = m_entities.addEntity("bullet");
	Vec2 direction = target - m_player->cTransform->pos;

	
	float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
	Vec2 normalizedDir = (length != 0) ? Vec2(direction.x / length, direction.y / length) : Vec2(0.f, 0.f);

	
	float bulletSpeed = 400.0f;

	entity->cTransform = std::make_shared<CTransform>(m_player->cTransform->pos,normalizedDir * bulletSpeed,0);
	entity->cShape = std::make_shared<CShape>(4.0f, 5, sf::Color(255, 255, 255), sf::Color(255, 0, 0), 2.0f);
}


void Game::spawnEnemy()
{
	if (m_currentFrame % 60 == 0) {
		auto e = m_entities.addEntity("enemy");
		float ex = rand() % m_window.getSize().x;
		float ey = rand() % m_window.getSize().y;

		e->cTransform = std::make_shared<CTransform>(Vec2(ex, ey), Vec2(0, 0), 0);

		e->cShape = std::make_shared<CShape>(10.0f, 3, sf::Color(0, 0, 255), sf::Color(255, 255, 255), 4.0f);
	}
	m_lastEnemySpawnTime = m_currentFrame;

};




void Game::sRender()
{

	m_window.clear();
	for (auto e : m_entities.getEntities())
	{
		
		e->cShape->circle.setPosition({ e->cTransform->pos.x, e->cTransform->pos.y });
		e->cTransform->angle += 40.f * m_deltaTime;
		e->cShape->circle.setRotation( sf::degrees(e->cTransform->angle) );
		m_window.draw(e->cShape->circle);
		

	}


	m_window.display();

};

void Game::sMovement()
{

	if (m_player->cInput->up)
	{
		m_player->cTransform->velocity.y = -150;

	}
	else if (m_player->cInput->down)
	{
		m_player->cTransform->velocity.y = 150;

	}
	else
	{
		m_player->cTransform->velocity.y = 0;

	}

	if (m_player->cInput->left)
	{
		m_player->cTransform->velocity.x = -150;

	}
	else if (m_player->cInput->right)
	{
		m_player->cTransform->velocity.x = 150;

	}
	else
	{
		m_player->cTransform->velocity.x = 0;

	}



	for (auto e : m_entities.getEntities())
	{
		
		
		e->cTransform->pos.x += e->cTransform->velocity.x * m_deltaTime;
		e->cTransform->pos.y += e->cTransform->velocity.y * m_deltaTime;
		
	}
}

void Game::sCollision()
{
    for (auto& bullet : m_entities.getEntities("bullet"))
    {
        for (auto& enemy : m_entities.getEntities("enemy"))
        {
            if (bullet->m_active && enemy->m_active && isColliding(bullet, enemy))
            {
                bullet->m_active = false;
                enemy->m_active = false;
               
            }
        }
    }

    for (auto& enemy : m_entities.getEntities("enemy"))
    {
        if (enemy->m_active && m_player->m_active && isColliding(enemy, m_player))
        {
            enemy->m_active = false;
            
            m_playerlives--;

            if (m_playerlives <= 0)
            {
                m_player->m_active = false;
                m_running = false; 
            }
        }
    }
}


void Game::sEnemySpawner()
{

	m_enemySpawnTimer += m_deltaTime;

	if (m_enemySpawnTimer >= m_enemySpawnInterval)
	{
		spawnEnemy();
		m_enemySpawnTimer = 0.f;
	}

}

void Game::sUserInput()
{
	while (auto event = m_window.pollEvent())
	{
		
		if (event->is<sf::Event::Closed>())
		{
			m_running = false;
			m_window.close();
		}

		if (const auto* key = event->getIf<sf::Event::KeyPressed>())
		{
			using Sc = sf::Keyboard::Scancode;

			if (key->scancode == Sc::Escape)
			{
				m_running = false;
			}
			if (key->scancode == Sc::W) {
				std::cout << "Key pressesd: W\n";
				m_player->cInput->up = true;
			}
			if (key->scancode == Sc::S) { 
				std::cout << "Key pressesd: S\n"; 
				m_player->cInput->down = true;
			}
			if (key->scancode == Sc::A) { 
				std::cout << "Key pressesd: A\n";
				m_player->cInput->left = true;
			}
			if (key->scancode == Sc::D) { 
				std::cout << "Key pressesd: D\n";
				m_player->cInput->right = true;
			}


		}

		if (const auto* key = event->getIf<sf::Event::KeyReleased>())
		{
			using Sc = sf::Keyboard::Scancode;

			if (key->scancode == Sc::W) { 
				std::cout << "Key Released: W\n";
				m_player->cInput->up = false;
			}
			if (key->scancode == Sc::S) { 
				std::cout << "Key Released: S\n";
				m_player->cInput->down = false;
			}
			if (key->scancode == Sc::A) { 
				std::cout << "Key Released: A\n";
				m_player->cInput->left = false;
			}
			if (key->scancode == Sc::D) { 
				std::cout << "Key Released: D\n";
				m_player->cInput->right = false;
			}
		}

		if (const auto* mouseClick = event->getIf<sf::Event::MouseButtonPressed>())
		{
			sf::Vector2i pos = mouseClick->position;
			std::cout << "Mouse clicked at: " << pos.x << ", " << pos.y << "\n";
			spawnBullet(m_player, Vec2(pos.x, pos.y));

		}
	}
}
bool Game::isColliding(const std::shared_ptr<Entity>& a, const std::shared_ptr<Entity>& b)
{
	float dx = a->cTransform->pos.x - b->cTransform->pos.x;
	float dy = a->cTransform->pos.y - b->cTransform->pos.y;
	float distance = std::sqrt(dx * dx + dy * dy);

	float r1 = a->cShape->circle.getRadius();
	float r2 = b->cShape->circle.getRadius();

	return distance < (r1 + r2);
}