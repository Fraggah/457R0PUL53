#include "Game.h"

Game::Game() 
{
	init();
}

void Game::init() 
{
	//Iniciacion Final: Utilizar una base de datos en txt que cargue las configuraciones

	m_window.create(sf::VideoMode(WIDTH, HEIGHT), "AstroPulse", sf::Style::Close);
	m_window.setFramerateLimit(60);
}

void Game::sRender() 
{
	m_window.clear();
	if (texturize)
	{
		m_window.draw(player->sprite);
		for (size_t i = 0; i < aliveEntities.size(); ++i) {
			m_window.draw(aliveEntities[i]->sprite);
		}
	}
	if (debug)
	{
		for (size_t i = 0; i < aliveEntities.size(); ++i) {
			m_window.draw(aliveEntities[i]->boundingBox);
		}
		m_window.draw(player->boundingBox);
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
				else if (event.key.code == sf::Keyboard::K) { shootBSimple(); }
				else if (event.key.code == sf::Keyboard::L) { shootBLaser(); }
				else if (event.key.code == sf::Keyboard::T) { shootBTriple(); }
				else if (event.key.code == sf::Keyboard::Num1) { spawnAssault(); }
				else if (event.key.code == sf::Keyboard::Num2) { spawnCannon(); }
				else if (event.key.code == sf::Keyboard::Num3) { enemySpawn(); }
				else if (event.key.code == sf::Keyboard::F1)
				{
					texturize ? texturize = false : texturize = true;
				}
				else if (event.key.code == sf::Keyboard::F2)
				{
					debug ? debug = false : debug = true;
				}

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
		if (enemy->getX() > WIDTH + 100 || enemy->getX() < -100 || enemy->getY() > HEIGHT + 100 || enemy->getY() < - 100)
		{
			enemy->is_active = false;
		}
	}

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
			//inb time
		}
	}

	for (auto enemyb : getEntities("enemybullet"))
	{
		sf::Vector2f diff(player->boundingBox.getPosition().x - enemyb->boundingBox.getPosition().x,
			player->boundingBox.getPosition().y - enemyb->boundingBox.getPosition().y);

		double collisionRadiusSQ = (player->boundingBox.getRadius() + enemyb->boundingBox.getRadius()) *
			(player->boundingBox.getRadius() + enemyb->boundingBox.getRadius());

		double distSQ = (diff.x * diff.x) + (diff.y * diff.y);

		if (distSQ < collisionRadiusSQ)
		{
			enemyb->is_active = false; 
			DynamicEntity* boom = new EntityBoom(player->getX(), player->getY(), true);
			toAdd.push_back(boom);
			player->setX(500); player->setY(900);
			//inb time
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
				DynamicEntity* boom = new EntityBoom(enemy->getX(), enemy->getY(), false);
				toAdd.push_back(boom);
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
		sMovement();
		sCollisions();
		sRender();
		enemySpawn();
		enemyShoot();
		boomSpamTime();
		update();
		frameCount++;
	}
}

void Game::shootBSimple()
{
	Bullet* bullet = new BSimple(player->boundingBox.getPosition().x, player->boundingBox.getPosition().y - 32, 2);
	toAdd.push_back(bullet);
}

void Game::shootBLaser()
{
	Bullet* bulletL = new BLaser(player->boundingBox.getPosition().x - 16, player->boundingBox.getPosition().y, 18);
	Bullet* bulletR = new BLaser(player->boundingBox.getPosition().x + 16, player->boundingBox.getPosition().y, 18);
	toAdd.push_back(bulletR);
	toAdd.push_back(bulletL);
}

void Game::shootBTriple()
{
	float angle = rand() % 5;
	Bullet* bulletC = new BTriple(player->boundingBox.getPosition().x, player->boundingBox.getPosition().y - 32,0, 20);
	Bullet* bulletL = new BTriple(player->boundingBox.getPosition().x, player->boundingBox.getPosition().y - 32, -angle, 20);
	Bullet* bulletR = new BTriple(player->boundingBox.getPosition().x, player->boundingBox.getPosition().y - 32, angle, 20);
	toAdd.push_back(bulletC);
	toAdd.push_back(bulletL);
	toAdd.push_back(bulletR);
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

void Game::spawnAssault()
{
	Enemy* enemy = new EAssault(rand() % 1000 + 40, rand() % 5 - 3);
	toAdd.push_back(enemy);

}

void Game::spawnCannon()
{
	Enemy* enemy = new ECannon(true, cannonIterator);
	toAdd.push_back(enemy);
	if (cannonIterator != 4)
	{
		cannonIterator++;
	}
	else
	{
		cannonIterator = 0;
	}

}

void Game::removeDeadEntities(std::vector<DynamicEntity*>& vec)
{
	vec.erase(std::remove_if(vec.begin(), vec.end(),
		[](Entity* entity) { return !entity->is_active; }),
		vec.end());

}

void Game::boomSpamTime()
{
	for (auto boom : getEntities("explosion"))
	{
		if (boom->animationState == 3 )
		{
			boom->is_active = false;
			printf("boom");
		}
	}
}

const std::vector<DynamicEntity*>& Game::getEntities(const std::string& tag)
{
	return entityMap[tag];
}

void Game::update()
{
	/*
		Despu�s de enfrentar una falla cr�tica durante las pruebas de colisiones,
		donde ocurr�a un mal funcionamiento del sistema, averigu� e
		estudi� lo que se conove como "Iterator Invalidation".

		Para abordar este problema, implement� un enfoque de dos pasos para la adici�n
		y eliminaci�n de entidades. Primero, se agregan las entidades nuevas al vector
		de entidades vivas y al mapa de entidades. Luego, se eliminan las entidades
		marcadas como inactivas. Esto garantiza una gesti�n segura de los
		iteradores y previene la invalidez durante la eliminaci�n de entidades.

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
		int i = 0;
		if (enemy->type == 1)
		{
			if (enemy->clock.getElapsedTime() > sf::seconds(rand() % 3 + 1))
			{
				Bullet* bullet = new BEnemy(enemy->getX() + 44, enemy->getY() + 48, 12, 0);
				toAdd.push_back(bullet);
				enemy->clock.restart();
			}
		}
		if (enemy->type == 2)
		{
			sf::Vector2f direction(player->getX() - enemy->getX(), player->getY() - enemy->getY());
			float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
			if (length != 0)
			{
				direction /= length;
			}
			if (enemy->speed == 0)
			{
				if (enemy->clock.getElapsedTime() > sf::seconds(0.5) && i < 4)
				{
					Bullet* bullet = new BEnemy(enemy->getX() + 44, enemy->getY() + 48, direction.y*10, direction.x*10);
					toAdd.push_back(bullet);
					enemy->clock.restart();
					i++;
				}
			}
		}
	}
}

void Game::sMovement()
{
	player->movement();
	for (size_t i = 0; i < aliveEntities.size(); ++i) {
		aliveEntities[i]->movement();
	}
}
