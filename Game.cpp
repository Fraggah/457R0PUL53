#include "Game.h"

Game::Game() 
{
	init();
}

void Game::init() 
{
	m_window.create(sf::VideoMode(1080, 1080), "AstroPulse", sf::Style::Close);
	m_window.setFramerateLimit(60);
}

void Game::sRender() 
{
	m_window.clear();
	m_window.draw(player->sprite);
	for (size_t i = 0; i < dentities.size(); ++i) {
		m_window.draw(dentities[i]->sprite);
	}
	m_window.display();
}


void Game::sUserInput()
{
	sf::Event event;
	while (m_window.pollEvent(event))
	{
		switch (event.type)
		{
			case sf::Event::Closed:
			{
				m_running = false;
				break;
			}
			case sf::Event::KeyPressed:
			{
				if (event.key.code == sf::Keyboard::Escape)
				{
					m_running = false;
				}
				else if (event.key.code == sf::Keyboard::A) { player->left  = true; }
				else if (event.key.code == sf::Keyboard::D) { player->right = true; }
				else if (event.key.code == sf::Keyboard::W) { player->up    = true; }
				else if (event.key.code == sf::Keyboard::S) { player->down  = true; }
				else if (event.key.code == sf::Keyboard::K) {		 shoot();		}
				else if (event.key.code == sf::Keyboard::I) { enemySpawn(); }

				break;
			}
			case sf::Event::KeyReleased:
			{
				     if (event.key.code == sf::Keyboard::A) { player->left  = false; }
				else if (event.key.code == sf::Keyboard::D) { player->right = false; }
				else if (event.key.code == sf::Keyboard::W) { player->up    = false; }
				else if (event.key.code == sf::Keyboard::S) { player->down  = false; }

			    break;
			}
		}
	}
}

void Game::sCollisions()
{

	for (auto bullet : getEntities("bullet"))
	{
		for (auto enemy : getEntities("enemy"))
		{

			if (bullet->sprite.getPosition().x > enemy->sprite.getPosition().x && bullet->sprite.getPosition().x + 3 < enemy->sprite.getPosition().x + 30 &&
				bullet->sprite.getPosition().y > enemy->sprite.getPosition().y && bullet->sprite.getPosition().y + 3 < enemy->sprite.getPosition().y + 30)
			{
				enemy->is_active = false;
				bullet->is_active = false;
				printf("CRASH\n");
			}		
		}
	}
}


void Game::run() 
{
	while (m_running)
	{
		sUserInput();
		player->movement();
		for (size_t i = 0; i < dentities.size(); ++i) {
			dentities[i]->movement();
		}
		enemySpawn();
		sCollisions();
		sRender();
		update();
		frameCount++;
	}
}

void Game::shoot()
{
	Bullet* bullet = new Bullet(player->getX() + 43 , player->getY(), 2);
	toAdd.push_back(bullet);
}

void Game::enemySpawn()
{
	if (clock.getElapsedTime() > sf::seconds(2))
	{
		Enemy* enemy = new Enemy();
		toAdd.push_back(enemy);
		clock.restart();
	}
	
}

void Game::removeDeadEntities(std::vector<DynamicEntity*>& vec)
{
	vec.erase(std::remove_if(vec.begin(), vec.end(),
		[](Entity* entity) { return !entity->is_active; }),
		vec.end());

}

const std::vector<DynamicEntity*>& Game::getEntities(const std::string& tag)
{
	return entityMap[tag];
}

void Game::update()
{
	for (auto& e : toAdd)
	{
		dentities.push_back(e);
		entityMap[e->tag].push_back(e);
	}

	removeDeadEntities(dentities);

	for (auto it = entityMap.begin(); it != entityMap.end(); ++it)
	{
		const std::string& tag = it->first;
		std::vector<DynamicEntity*>& entityVec = it->second;

		removeDeadEntities(entityVec);
	}

	toAdd.clear();
}