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

	if (!font.loadFromFile("assets/16/nes.otf"))
		printf("cannot load font");

	frametest.setFont(font);
	frametest.setFillColor(sf::Color::White);
	frametest.setString(tframe);
	frametest.setCharacterSize(24);
	frametest.setPosition(30, HEIGHT - 40);

	if (!btexture.loadFromFile("assets/16/bg1.png"))
		printf("cannot load bgtexture");
	if (!btexture2.loadFromFile("assets/16/bg2.png"))
		printf("cannot load bg2texture");

	background.setTexture(btexture);
	background.scale(4, 4);
	backgroundmirror.setTexture(btexture);
	backgroundmirror.scale(4, 4);
	backgroundmirror.setPosition(0, -HEIGHT);

	background2.setTexture(btexture2);
	background2.scale(4, 4);
	backgroundmirror2.setTexture(btexture2);
	backgroundmirror2.scale(4, 4);
	backgroundmirror2.setPosition(0, -HEIGHT);
}

void Game::sRender() 
{
	m_window.clear();
	m_window.draw(background);
	m_window.draw(backgroundmirror);
	m_window.draw(background2);
	m_window.draw(backgroundmirror2);
	if (m_texturize)
	{
		m_window.draw(m_player->sprite);
		for (size_t i = 0; i < m_aliveEntities.size(); ++i) {
			m_window.draw(m_aliveEntities[i]->sprite);
		}
	}
	if (m_debug)
	{
		for (size_t i = 0; i < m_aliveEntities.size(); ++i) {
			m_window.draw(m_aliveEntities[i]->boundingBox);
		}
		m_window.draw(m_player->boundingBox);
	}
	m_window.draw(frametest);
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
				else if (event.key.code == sf::Keyboard::A) { m_player->left  = true; }
				else if (event.key.code == sf::Keyboard::D) { m_player->right = true; }
				else if (event.key.code == sf::Keyboard::W) { m_player->up    = true; }
				else if (event.key.code == sf::Keyboard::S) { m_player->down  = true; }
				else if (event.key.code == sf::Keyboard::K && !m_paused) { shootBSimple(); }
				else if (event.key.code == sf::Keyboard::L && !m_paused) { shootBLaser(); }
				else if (event.key.code == sf::Keyboard::T && !m_paused) { shootBTriple(); }
				else if (event.key.code == sf::Keyboard::Num1 && !m_paused) { spawnAssault(); }
				else if (event.key.code == sf::Keyboard::Num2 && !m_paused) { spawnCannon(); }
				else if (event.key.code == sf::Keyboard::Num3 && !m_paused) { spawnDoubleCannon(true); }
				else if (event.key.code == sf::Keyboard::Num4 && !m_paused) { spawnBomber(2); }
				else if (event.key.code == sf::Keyboard::F1)
				{
					m_texturize ? m_texturize = false : m_texturize = true;
				}
				else if (event.key.code == sf::Keyboard::F2)
				{
					m_debug ? m_debug = false : m_debug = true;
				}
				else if (event.key.code == sf::Keyboard::P)
				{
					m_paused ? m_paused = false : m_paused = true;
				}

				break;
			}
			case sf::Event::KeyReleased:
			{
				     if (event.key.code == sf::Keyboard::A) { m_player->left  = false; }
				else if (event.key.code == sf::Keyboard::D) { m_player->right = false; }
				else if (event.key.code == sf::Keyboard::W) { m_player->up    = false; }
				else if (event.key.code == sf::Keyboard::S) { m_player->down  = false; }

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
	for (auto bullet : getEntities("bullet"))
	{
		if (bullet->getY() < -100)
		{
			bullet->is_active = false;
		}
	}

	for (auto ebullet : getEntities("enemybullet"))
	{
		if (ebullet->getY() > HEIGHT + 100)
		{
			ebullet->is_active = false;
		}
	}

	for (auto enemy : getEntities("enemy"))
	{
		sf::Vector2f diff(m_player->boundingBox.getPosition().x - enemy->boundingBox.getPosition().x,
						  m_player->boundingBox.getPosition().y - enemy->boundingBox.getPosition().y);

		double collisionRadiusSQ = (m_player->boundingBox.getRadius() + enemy->boundingBox.getRadius()) *
								   (m_player->boundingBox.getRadius() + enemy->boundingBox.getRadius());

		double distSQ = (diff.x * diff.x) + (diff.y * diff.y);

		if (distSQ < collisionRadiusSQ)
		{
			//enemy->is_active = false; //ver si es conveniente o no destruir al enemigo....
			m_player->setX(500); m_player->setY(900);
			//inb time
		}
	}

	for (auto enemyb : getEntities("enemybullet"))
	{
		sf::Vector2f diff(m_player->boundingBox.getPosition().x - enemyb->boundingBox.getPosition().x,
			m_player->boundingBox.getPosition().y - enemyb->boundingBox.getPosition().y);

		double collisionRadiusSQ = (m_player->boundingBox.getRadius() + enemyb->boundingBox.getRadius()) *
			(m_player->boundingBox.getRadius() + enemyb->boundingBox.getRadius());

		double distSQ = (diff.x * diff.x) + (diff.y * diff.y);

		if (distSQ < collisionRadiusSQ)
		{
			enemyb->is_active = false; 
			DynamicEntity* boom = new EntityBoom(m_player->getX(), m_player->getY(), true);
			m_toAdd.push_back(boom);
			m_player->setX(500); m_player->setY(900);
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
				if (enemy->lifes == 1) {
					enemy->is_active = false;
					DynamicEntity* boom = new EntityBoom(enemy->getX(), enemy->getY(), false);
					m_toAdd.push_back(boom);
				}
				else
				{
					enemy->lifes--; //crear alguna animacion para indicar que recibió el impacto
				}
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
		if (!m_paused)
		{
			sMovement();
			sCollisions();
			enemyShoot();
			boomSpamTime();
			m_currentFrame++;
			level1(); //funcionaaaaaaa :D
		}
		interface();
		sUserInput();
		sRender();
		update();
	}
}

void Game::shootBSimple()
{
	Bullet* bullet = new BSimple(m_player->boundingBox.getPosition().x, m_player->boundingBox.getPosition().y - 32, 2);
	m_toAdd.push_back(bullet);
}

void Game::shootBLaser()
{
	Bullet* bulletL = new BLaser(m_player->boundingBox.getPosition().x - 16, m_player->boundingBox.getPosition().y, 18);
	Bullet* bulletR = new BLaser(m_player->boundingBox.getPosition().x + 16, m_player->boundingBox.getPosition().y, 18);
	m_toAdd.push_back(bulletR);
	m_toAdd.push_back(bulletL);
}

void Game::shootBTriple()
{
	float angle = rand() % 5;
	Bullet* bulletC = new BTriple(m_player->boundingBox.getPosition().x, m_player->boundingBox.getPosition().y - 32,0, 20);
	Bullet* bulletL = new BTriple(m_player->boundingBox.getPosition().x, m_player->boundingBox.getPosition().y - 32, -angle, 20);
	Bullet* bulletR = new BTriple(m_player->boundingBox.getPosition().x, m_player->boundingBox.getPosition().y - 32, angle, 20);
	m_toAdd.push_back(bulletC);
	m_toAdd.push_back(bulletL);
	m_toAdd.push_back(bulletR);
}

void Game::spawnDoubleCannon(bool _l)
{
	Enemy* enemy = new EDoubleCannon(_l);
	m_toAdd.push_back(enemy);
}

void Game::spawnAssault()
{
	Enemy* enemy = new EAssault(rand() % 1000 + 40, rand() % 5 - 3);
	m_toAdd.push_back(enemy);

}

void Game::spawnCannon()
{
	Enemy* enemy = new ECannon(cannonLR, cannonIterator);
	m_toAdd.push_back(enemy);
	if (cannonIterator != 4)
	{
		cannonIterator++;
	}
	else
	{
		cannonIterator = 0;
	}
	if(cannonLR == true)
	{
		cannonLR = false;
	}
	else {
		cannonLR = true;
	}
	

}

void Game::spawnBomber(int pos)
{
	pos--;
	Enemy* enemy = new EBomber(pos);
	m_toAdd.push_back(enemy);
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
	return m_entityMap[tag];
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
	for (auto& e : m_toAdd)
	{
		m_aliveEntities.push_back(e);
		m_entityMap[e->tag].push_back(e); //opte por un map con tags, podria haber utilizado un dynamic_cast para filtrar las clases hijas, pero quise utilizar esta arquitectura
	}

	removeDeadEntities(m_aliveEntities);

	for (auto it = m_entityMap.begin(); it != m_entityMap.end(); ++it)
	{
		const std::string& tag = it->first;
		std::vector<DynamicEntity*>& entityVec = it->second;

		removeDeadEntities(entityVec);
	}

	m_toAdd.clear();
}

void Game::enemyShoot() //WORKS
{
	for (auto& enemy : getEntities("enemy"))
	{
		int i = 0;
		if (enemy->type == 1)
		{
			if (enemy->clock.getElapsedTime() > sf::seconds(rand() % 4 + 1))
			{
				Bullet* bullet = new BEnemy(enemy->getX() + 44, enemy->getY() + 48, 12, 0);
				m_toAdd.push_back(bullet);
				enemy->clock.restart();
			}
		}
		if (enemy->type == 2)
		{
			if (enemy->getX() - 50 > m_player->getX())
			{
				enemy->PL = true;
			}
			else
			{
				enemy->PL = false;
			}
			if (enemy->getX() + 50 < m_player->getX())
			{
				enemy->PR = true;
			}
			else
			{
				enemy->PR = false;
			}
			sf::Vector2f direction(m_player->getX() - enemy->getX(), m_player->getY() - enemy->getY());
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
					m_toAdd.push_back(bullet);
					enemy->clock.restart();
					i++;
				}
			}
		}
		if (enemy->type == 4)
		{
			float randomizer = rand() % 10 - 5;
			if (enemy->speed == 0)
			{
				if (enemy->clock.getElapsedTime() > sf::seconds(0.05))
				{
					Bullet* bullet = new BEnemy(enemy->getX() + 44, enemy->getY() + 48, 5, randomizer);
					m_toAdd.push_back(bullet);
					enemy->clock.restart();
				}
			}
		}
	}
}

void Game::sMovement()
{
	m_player->movement();
	for (size_t i = 0; i < m_aliveEntities.size(); ++i) {
		m_aliveEntities[i]->movement();
	}

	if (m_currentFrame < 120)
	{
		background.move(0, 16);
		backgroundmirror.move(0, 16);
		background2.move(0, 24);
		backgroundmirror2.move(0, 24);
	}else if (m_currentFrame < 130)
	{
		background.move(0, 7);
		backgroundmirror.move(0, 7);
		background2.move(0, 10);
		backgroundmirror2.move(0, 10);
	}else if (m_currentFrame < 140)
	{
		background.move(0, 3);
		backgroundmirror.move(0, 3);
		background2.move(0, 4);
		backgroundmirror2.move(0, 4);
	}
	else
	{
		background.move(0, 0.5);
		backgroundmirror.move(0, 0.5);
		background2.move(0, 1);
		backgroundmirror2.move(0, 1);
	}

	if (background.getPosition().y == HEIGHT)
	{
		background.setPosition(0, -HEIGHT);
	}
	if (backgroundmirror.getPosition().y == HEIGHT)
	{
		backgroundmirror.setPosition(0, -HEIGHT);
	}

	if (background2.getPosition().y == HEIGHT)
	{
		background2.setPosition(0, -HEIGHT);
	}
	if (backgroundmirror2.getPosition().y == HEIGHT)
	{
		backgroundmirror2.setPosition(0, -HEIGHT);
	}
}

void Game::interface()
{
	frametest.setString(tframe + std::to_string(m_currentFrame));
}

void Game::level1()
{
	switch (m_currentFrame) {
	case 160:spawnDoubleCannon(true);break;
	case 180:spawnDoubleCannon(true);break;
	case 200:spawnDoubleCannon(true);break;
	case 220:spawnDoubleCannon(true);break;
	case 460:spawnDoubleCannon(false);break;
	case 480:spawnDoubleCannon(false);break;
	case 500:spawnDoubleCannon(false);break;
	case 520:spawnDoubleCannon(false);break;
	case 700:spawnDoubleCannon(true);spawnDoubleCannon(false);break;
	case 720:spawnDoubleCannon(true);spawnDoubleCannon(false);break;
	case 740:spawnDoubleCannon(true);spawnDoubleCannon(false);break;
	case 760:spawnDoubleCannon(true);spawnDoubleCannon(false);break;
	case 1100:spawnAssault();spawnAssault();spawnAssault();spawnAssault();break;
	case 1130:spawnAssault();spawnAssault();spawnAssault();spawnAssault();break;
	case 1160:spawnAssault();spawnAssault();spawnAssault();spawnAssault();break;
	case 1190:spawnAssault();spawnAssault();spawnAssault();spawnAssault();break;
	case 1300:spawnAssault();spawnAssault();spawnAssault();spawnAssault();break;
	case 1330:spawnAssault();spawnAssault();spawnAssault();spawnAssault();break;
	case 1360:spawnAssault();spawnAssault();spawnAssault();spawnAssault();break;
	case 1390:spawnAssault();spawnAssault();spawnAssault();spawnAssault();break;
	case 1500:spawnDoubleCannon(true);break;
	case 1510:spawnDoubleCannon(false);break;
	case 1520:spawnDoubleCannon(true);break;
	case 1530:spawnDoubleCannon(false);break;
	case 1540:spawnDoubleCannon(true);break;
	case 1550:spawnDoubleCannon(false);break;
	case 1560:spawnDoubleCannon(true);break;
	case 1570:spawnDoubleCannon(false);break;
	case 1580:spawnDoubleCannon(true);break;
	case 1590:spawnDoubleCannon(false);break;
	case 1600:spawnDoubleCannon(true);break;
	case 1610:spawnDoubleCannon(false);break;
	case 2000:spawnCannon();break;
	case 2100:spawnCannon();break;
	case 2200:spawnCannon();break;
	case 2300:spawnCannon();break;
	case 2400:spawnCannon();break;
	case 2550:spawnBomber(2);break;
	case 2700:spawnBomber(1);spawnBomber(3);break;
	case 3000:spawnDoubleCannon(true);spawnDoubleCannon(false);break;
	case 3020:spawnDoubleCannon(true);spawnDoubleCannon(false);break;
	case 3040:spawnDoubleCannon(true);spawnDoubleCannon(false);break;
	case 3060:spawnDoubleCannon(true);spawnDoubleCannon(false);break;
	case 3160:spawnDoubleCannon(true);spawnDoubleCannon(false);break;
	case 3180:spawnDoubleCannon(true);spawnDoubleCannon(false);break;
	case 3200:spawnDoubleCannon(true);spawnDoubleCannon(false);break;
	case 3220:spawnDoubleCannon(true);spawnDoubleCannon(false);break;
	case 3300:spawnAssault();spawnAssault();spawnAssault();spawnAssault();spawnAssault();spawnAssault();break;
	case 3330:spawnAssault();spawnAssault();spawnAssault();spawnAssault();spawnAssault();spawnAssault();break;
	case 3360:spawnAssault();spawnAssault();spawnAssault();spawnAssault();spawnAssault();spawnAssault();break;
	case 3390:spawnAssault();spawnAssault();spawnAssault();spawnAssault();spawnAssault();spawnAssault();break;
	case 3400:spawnAssault();spawnAssault();spawnAssault();spawnAssault();spawnAssault();spawnAssault();break;
	case 3430:spawnAssault();spawnAssault();spawnAssault();spawnAssault();spawnAssault();spawnAssault();break;
	case 3460:spawnAssault();spawnAssault();spawnAssault();spawnAssault();spawnAssault();spawnAssault();break;
	case 3490:spawnAssault();spawnAssault();spawnAssault();spawnAssault();spawnAssault();spawnAssault();break;
	case 3550:spawnBomber(2);
	case 3600:spawnCannon();break;
	case 3650:spawnCannon();break;
	case 3700:spawnCannon();break;
	case 3750:spawnCannon();break;
	case 3800:spawnCannon();break;
	}

}