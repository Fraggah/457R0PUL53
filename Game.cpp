#include "Game.h"

Game::Game() 
{
	init();
}

void Game::init() 
{
	//Iniciacion Final: Utilizar una base de datos en txt que cargue las configuraciones

	m_window.create(sf::VideoMode(1080, 1080), "AstroPulse", sf::Style::Close);
	m_window.setFramerateLimit(60);
}

void Game::sRender() 
{
	m_window.clear();
	m_window.draw(player->sprite);
	for (size_t i = 0; i < aliveEntities.size(); ++i) {
		m_window.draw(aliveEntities[i]->sprite);
		m_window.draw(aliveEntities[i]->boundingBox);
	}
	m_window.draw(player->boundingBox);
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
	//Sistema final: agregar una bounding box circular a las entities y utilizar formula de distancia menos radio


	for (auto enemy : getEntities("enemy"))
	{
		sf::Vector2f diff(player->boundingBox.getPosition().x - enemy->boundingBox.getPosition().x,
						  player->boundingBox.getPosition().y - enemy->boundingBox.getPosition().y);

		double collisionRadiusSQ = (player->boundingBox.getRadius() + enemy->boundingBox.getRadius()) *
								   (player->boundingBox.getRadius() + enemy->boundingBox.getRadius());

		double distSQ = (diff.x * diff.x) + (diff.y * diff.y);

		if (distSQ < collisionRadiusSQ)
		{
			enemy->is_active = false; //ver si es conveniente o no destruir al enemigo....
			player->setX(500); player->setY(900);
			//resto vida, animacion de explosion y set spawn inbulnerable time
		}
	}

	for (auto bullet : getEntities("bullet"))
	{
		for (auto enemy : getEntities("enemy"))
		{
			sf::Vector2f diff (enemy->boundingBox.getPosition().x - bullet->boundingBox.getPosition().x,
							   enemy->boundingBox.getPosition().y - bullet->boundingBox.getPosition().y);

			double collisionRadiusSQ = (enemy->boundingBox.getRadius() + bullet->boundingBox.getRadius()) *
									   (enemy->boundingBox.getRadius() + bullet->boundingBox.getRadius());

			double distSQ = (diff.x * diff.x) + (diff.y * diff.y);

			if (distSQ < collisionRadiusSQ)
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
		for (size_t i = 0; i < aliveEntities.size(); ++i) {
			aliveEntities[i]->movement();
		}
		enemySpawn();
		sCollisions();
		sRender();
		enemyShoot();
		update();
		frameCount++;
	}
}

void Game::shoot()
{
	Bullet* bullet = new Bullet(player->getX() + 28 , player->getY(), 2);
	toAdd.push_back(bullet);
}

void Game::enemySpawn()
{
	if (clock.getElapsedTime() > sf::seconds(2))
	{
		Enemy* enemy = new EDoubleCannon();
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
	/*
		Después de enfrentar una falla crítica durante las pruebas de colisiones,
		donde ocurría un mal funcionamiento del sistema, averigué e
		estudié lo que se conove como "Iterator Invalidation".

		Para abordar este problema, implementé un enfoque de dos pasos para la adición
		y eliminación de entidades. Primero, se agregan las entidades nuevas al vector
		de entidades vivas y al mapa de entidades. Luego, se eliminan las entidades
		marcadas como inactivas. Esto garantiza una gestión segura de los
		iteradores y previene la invalidez durante la eliminación de entidades.

		Luego del proceso se limpia el vector de agregado previo.
	*/
	for (auto& e : toAdd)
	{
		aliveEntities.push_back(e);
		entityMap[e->tag].push_back(e);
	}

	removeDeadEntities(aliveEntities);

	for (auto it = entityMap.begin(); it != entityMap.end(); ++it)
	{
		const std::string& tag = it->first;
		std::vector<DynamicEntity*>& entityVec = it->second;

		removeDeadEntities(entityVec);
	}

	toAdd.clear();
}

void Game::enemyShoot() //WORKS
{
	for (auto& enemy : getEntities("enemy"))
	{
		if (enemy->clock.getElapsedTime() > sf::seconds(3))
		{
			//Bullet* bullet = new Bullet(enemy->getX() + 14, enemy->getY(), -2);
			//toAdd.push_back(bullet);
		}
	}
}