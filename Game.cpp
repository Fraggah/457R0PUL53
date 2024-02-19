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

	menutext.setFont(font);
	menutext.setFillColor(sf::Color::White);
	menutext.setString(press);
	menutext.setCharacterSize(24);
	menutext.setPosition(415, 550);

	leveltext.setFont(font);
	leveltext.setFillColor(sf::Color::White);
	leveltext.setString(leveln);
	leveltext.setCharacterSize(24);
	leveltext.setPosition(440, 450);

	copy.setFont(font);
	copy.setFillColor(sf::Color::White);
	copy.setString(copystring);
	copy.setCharacterSize(24);
	copy.setPosition(300, 800);

	hiscore.setFont(font);
	hiscore.setFillColor(sf::Color::White);
	hiscore.setString(histring);
	hiscore.setCharacterSize(24);
	hiscore.setPosition(430, 50);

	nlifes.setFont(font);
	nlifes.setFillColor(sf::Color::White);
	nlifes.setCharacterSize(26);
	nlifes.setPosition(780, 43);

	points.setFont(font);
	points.setFillColor(sf::Color::White);
	points.setCharacterSize(26);
	points.setPosition(440, 63);

	energyShieldInterface.setFont(font);
	energyShieldInterface.setFillColor(sf::Color::White);
	energyShieldInterface.setCharacterSize(26);
	energyShieldInterface.setString(esstring);
	energyShieldInterface.setPosition(200, 43);

	if (!titletexture.loadFromFile("assets/16/title.png"))
		printf("cannot load titletexture");
	if (!btexture.loadFromFile("assets/16/bg1.png"))
		printf("cannot load bgtexture");
	if (!btexture2.loadFromFile("assets/16/bg2.png"))
		printf("cannot load bg2texture");
	if (!lifeTexture.loadFromFile("assets/16/lifeinterface.png"))
		printf("cannot load bg2texture");
	if (!estexture.loadFromFile("assets/16/esinterface.png"))
		printf("cannot load bg2texture");

	titlesprite.setTexture(titletexture);
	titlesprite.scale(4, 4);

	lifeInterface.setTexture(lifeTexture);
	lifeInterface.scale(4, 4);
	lifeInterface.setPosition(750, 50);

	essprite.setTexture(estexture);
	essprite.scale(6, 6);
	essprite.setPosition(240, 50);

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
	if (m_menu)
	{
		m_window.draw(titlesprite);
		m_window.draw(copy);
		m_window.draw(hiscore);
		if (pressonoff.getElapsedTime() > sf::seconds(0.5))
		{
			m_window.draw(menutext);
		}
		if (pressonoff.getElapsedTime() > sf::seconds(1))
		{
			pressonoff.restart();
		}

	}
	if (m_sceneChange)
	{
		m_window.draw(leveltext);
	}
	if (!m_menu && !m_sceneChange)
	{
		m_window.draw(background);
		m_window.draw(backgroundmirror);
		m_window.draw(background2);
		m_window.draw(backgroundmirror2);
		if (m_texturize)
		{
			for (size_t i = 0; i < m_aliveEntities.size(); ++i) {
				m_window.draw(m_aliveEntities[i]->sprite);
			}
			m_window.draw(m_player->sprite);
		}
		if (m_debug)
		{
			for (size_t i = 0; i < m_aliveEntities.size(); ++i) {
				m_window.draw(m_aliveEntities[i]->boundingBox);
			}
			for (size_t i = 0; i < m_aliveEntities.size(); ++i) {
				m_window.draw(m_aliveEntities[i]->boundingBox2);
			}
			for (size_t i = 0; i < m_aliveEntities.size(); ++i) {
				m_window.draw(m_aliveEntities[i]->boundingBox3);
			}
			m_window.draw(m_player->boundingBox);
			m_window.draw(frametest);
		}
		m_window.draw(lifeInterface);
		m_window.draw(nlifes);
		m_window.draw(points);
		m_window.draw(energyShieldInterface);
		m_window.draw(essprite);
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
				else if (event.key.code == sf::Keyboard::A) { m_player->left  = true; }
				else if (event.key.code == sf::Keyboard::D) { m_player->right = true; }
				else if (event.key.code == sf::Keyboard::W) { m_player->up    = true; }
				else if (event.key.code == sf::Keyboard::S) { m_player->down  = true; }
				else if (event.key.code == sf::Keyboard::K && !m_paused) { shoot(); }
				else if (event.key.code == sf::Keyboard::L && !m_paused) { shootBLaser(); }
				else if (event.key.code == sf::Keyboard::T && !m_paused) { shootBTriple(); }
				else if (event.key.code == sf::Keyboard::Num1 && !m_paused) { spawnAssault(); }
				else if (event.key.code == sf::Keyboard::Num2 && !m_paused) { spawnCannon(); }
				else if (event.key.code == sf::Keyboard::Num3 && !m_paused) { spawnBoss(); }
				else if (event.key.code == sf::Keyboard::Num4 && !m_paused) { spawnBomber(2); }
				else if (event.key.code == sf::Keyboard::Num6 && !m_paused) { spawnPowerUp(300,300); }
				else if (event.key.code == sf::Keyboard::J && !m_paused && energyShieldTime.getElapsedTime() > sf::seconds(2)) { energyShield(); }
				else if (event.key.code == sf::Keyboard::Enter && m_menu)
				{
					m_menu = false;
					sceneChange();
				}
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
			DynamicEntity* boom = new EntityBoom(m_player->getX(), m_player->getY(), true);
			m_toAdd.push_back(boom);
			m_player->setX(1500); m_player->setY(1900);
			m_laserOn = false;
			m_tripleOn = false;
			m_inDead = true;
			deathTime.restart();
		}
	}

	for (auto enemy : getEntities("boss"))
	{
		sf::Vector2f diff(m_player->boundingBox.getPosition().x - enemy->boundingBox3.getPosition().x -120,
			m_player->boundingBox.getPosition().y - enemy->boundingBox3.getPosition().y-120);

		double collisionRadiusSQ = (m_player->boundingBox.getRadius() + enemy->boundingBox3.getRadius()) *
			(m_player->boundingBox.getRadius() + enemy->boundingBox3.getRadius());

		double distSQ = (diff.x * diff.x) + (diff.y * diff.y);

		if (distSQ < collisionRadiusSQ)
		{
			DynamicEntity* boom = new EntityBoom(m_player->getX(), m_player->getY(), true);
			m_toAdd.push_back(boom);
			m_player->setX(1500); m_player->setY(1900);
			m_laserOn = false;
			m_tripleOn = false;
			m_inDead = true;
			deathTime.restart();
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
			m_player->setX(1500); m_player->setY(1900);
			m_player->lifes--;
			m_laserOn = false;
			m_tripleOn = false;
			m_inDead = true;
			deathTime.restart();
		}
	}

	for (auto pup : getEntities("powerup"))
	{
		sf::Vector2f diff(m_player->boundingBox.getPosition().x - pup->boundingBox.getPosition().x,
			m_player->boundingBox.getPosition().y - pup->boundingBox.getPosition().y);

		double collisionRadiusSQ = (m_player->boundingBox.getRadius() + pup->boundingBox.getRadius()) *
			(m_player->boundingBox.getRadius() + pup->boundingBox.getRadius());

		double distSQ = (diff.x * diff.x) + (diff.y * diff.y);

		if (distSQ < collisionRadiusSQ)
		{
			pup->is_active = false;
			if (pup->type == 1)
			{
				m_laserOn = true;
				m_tripleOn = false;
			}
			else if (pup->type == 2)
			{
				m_laserOn = false;
				m_tripleOn = true;
			}
			else if (pup->type == 3)
			{
				m_player->lifes++;
			}
			else if (pup->type == 4)
			{
				//x blast
			}
			else if (pup->type == 5)
			{
				if (energyLevel != 3)
				{
					energyLevel++;
				}
			}
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
					m_player->points += enemy->points;
					npoints = m_player->points;
					int RNG = rand() % 100 + 1;
					if (RNG < 4)
					{
						spawnPowerUp(enemy->getX(), enemy->getY());
					}
					enemiesKilled++;
					if (enemiesKilled == 15)
					{	//Energy charge
						DynamicEntity* power = new PULaser(enemy->getX(), enemy->getY(), 5);
						m_toAdd.push_back(power);
						enemiesKilled = 0;
					}
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

	for (auto bullet : getEntities("bullet"))
	{
		for (auto enemy : getEntities("boss"))
		{
			sf::Vector2f diff(enemy->boundingBox.getPosition().x + 120 - bullet->boundingBox.getPosition().x,
				enemy->boundingBox.getPosition().y + 120 - bullet->boundingBox.getPosition().y);

			double collisionRadiusSQ = (enemy->boundingBox.getRadius() + bullet->boundingBox.getRadius()) *
				(enemy->boundingBox.getRadius() + bullet->boundingBox.getRadius());

			double distSQ = (diff.x * diff.x) + (diff.y * diff.y);

			if (distSQ < collisionRadiusSQ)
			{
				bullet->is_active = false;
			}

			sf::Vector2f diff2(enemy->boundingBox2.getPosition().x +32 - bullet->boundingBox.getPosition().x,
				enemy->boundingBox2.getPosition().y +28- bullet->boundingBox.getPosition().y);

			double collisionRadiusSQ2 = (enemy->boundingBox2.getRadius() + bullet->boundingBox.getRadius()) *
				(enemy->boundingBox2.getRadius() + bullet->boundingBox.getRadius());

			double distSQ2 = (diff2.x * diff2.x) + (diff2.y * diff2.y);


			if (distSQ2 < collisionRadiusSQ2)
			{
				if (enemy->lifes == 1) {
					enemy->is_active = false;
					DynamicEntity* boom = new EntityBoom(enemy->getX(), enemy->getY(), false);
					m_toAdd.push_back(boom);
					m_player->points += enemy->points;
					npoints = m_player->points;
				}
				else
				{
					DynamicEntity* boom = new EntityBoom(enemy->getX()+120, enemy->getY()+120, false);
					boom->sprite.setColor(sf::Color::Blue);
					m_toAdd.push_back(boom);
					enemy->lifes--; //crear alguna animacion para indicar que recibió el impacto
					printf("Yes");
				}
				bullet->is_active = false;
				printf("CRASH\n");
			}
		}
	}

	for (auto shield : getEntities("shield"))
	{
		for (auto ebullet : getEntities("enemybullet"))
		{	//A causa de que el el movimiento del shield funciona diferente tuve que sumarle un offset para que coinsida con el centro de la BB
			sf::Vector2f diff(shield->boundingBox.getPosition().x + (esOffset*2)- ebullet->boundingBox.getPosition().x,
								shield->boundingBox.getPosition().y + (esOffset*2)- ebullet->boundingBox.getPosition().y);

			double collisionRadiusSQ = (shield->boundingBox.getRadius() + ebullet->boundingBox.getRadius()) *
										(shield->boundingBox.getRadius() + ebullet->boundingBox.getRadius());

			double distSQ = (diff.x * diff.x) + (diff.y * diff.y);

			if (distSQ < collisionRadiusSQ)
			{
				ebullet->is_active = false;
			}
		}
	}

	for (auto shield : getEntities("shield"))
	{
		for (auto enemy : getEntities("enemy"))
		{	//A causa de que el el movimiento del shield funciona diferente tuve que sumarle un offset para que coinsida con el centro de la BB
			sf::Vector2f diff(shield->boundingBox.getPosition().x + (esOffset * 2) - enemy->boundingBox.getPosition().x,
				shield->boundingBox.getPosition().y + (esOffset * 2) - enemy->boundingBox.getPosition().y);

			double collisionRadiusSQ = (shield->boundingBox.getRadius() + enemy->boundingBox.getRadius()) *
				(shield->boundingBox.getRadius() + enemy->boundingBox.getRadius());

			double distSQ = (diff.x * diff.x) + (diff.y * diff.y);

			if (distSQ < collisionRadiusSQ)
			{
				enemy->is_active = false;
				DynamicEntity* boom = new EntityBoom(enemy->getX(), enemy->getY(), false);
				m_toAdd.push_back(boom);
				m_player->points += enemy->points;
				npoints = m_player->points;
			}
		}
	}
}

void Game::run() 
{
	while (m_running)
	{
		if (!m_paused && !m_menu)
		{
			sMovement();
			sCollisions();
			enemyShoot();
			boomSpamTime();
			playerRespawn();
			m_currentFrame++;
			//level1(); //funcionaaaaaaa :D
		}
		sRender();
		interface();
		sceneChanger();
		sUserInput();
		update();
	}
}

void Game::boosDamaged()
{

}

void Game::spawnBoss()
{
	BossAries* boss = new BossAries();
	m_toAdd.push_back(boss);
}

void Game::playerRespawn()
{
	if (m_inDead)
	{
		if (deathTime.getElapsedTime() > sf::seconds(1))
		{
			sceneChange();
			m_player->setX(480);m_player->setY(800);
			m_inDead = false;
		}
	}

}

void Game::shoot()
{
	if (!m_laserOn && !m_tripleOn)
	{
		Bullet* bullet = new BSimple(m_player->boundingBox.getPosition().x, m_player->boundingBox.getPosition().y - 32, 2);
		m_toAdd.push_back(bullet);
	}

	if (m_laserOn)
	{
		Bullet* bulletL = new BLaser(m_player->boundingBox.getPosition().x - 16, m_player->boundingBox.getPosition().y, 18);
		Bullet* bulletR = new BLaser(m_player->boundingBox.getPosition().x + 16, m_player->boundingBox.getPosition().y, 18);
		m_toAdd.push_back(bulletR);
		m_toAdd.push_back(bulletL);
	}

	if (m_tripleOn)
	{
		float angle = rand() % 5;
		Bullet* bulletC = new BTriple(m_player->boundingBox.getPosition().x, m_player->boundingBox.getPosition().y - 32, 0, 20);
		Bullet* bulletL = new BTriple(m_player->boundingBox.getPosition().x, m_player->boundingBox.getPosition().y - 32, -angle, 20);
		Bullet* bulletR = new BTriple(m_player->boundingBox.getPosition().x, m_player->boundingBox.getPosition().y - 32, angle, 20);
		m_toAdd.push_back(bulletC);
		m_toAdd.push_back(bulletL);
		m_toAdd.push_back(bulletR);
	}

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
	for (auto boss : getEntities("boss"))
	{
		if (boss->type == 10)
		{
			if (boss->clock.getElapsedTime() > sf::seconds(1))
			{
				for (int i = 0; i < 24; ++i) {
					float angle = i * (360.0f / 24) * (3.14159f / 180.0f);
					float bulletSpeed = 5;
					float dx = bulletSpeed * cos(angle);
					float dy = bulletSpeed * sin(angle);
					Enemy* bullet = new EBossBullet(boss->getX() +120, boss->getY()+120, dx, dy);
					m_toAdd.push_back(bullet);
				}
				boss->clock.restart();
			}
		}
	}
}

void Game::energyShield()
{
	if (energyLevel != 0)
	{
		energyShieldTime.restart();
		DynamicEntity* shield = new PEnergyShield(m_player->speed);
		m_toAdd.push_back(shield);
		energyLevel--;
	}
}


void Game::spawnPowerUp(float _x, float _y)
{
	int RNG = rand() % 50 + 1;

	 if (RNG > 20)
	{
		DynamicEntity* power = new PULaser(_x, _y, 1);
		m_toAdd.push_back(power);
	}
	//Triple
	else if (RNG > 10 && RNG < 20)
	{
		DynamicEntity* power = new PULaser(_x, _y, 2);
		m_toAdd.push_back(power);
	}
	//X Blast
	else if (RNG > 4 && RNG < 10)
	{
		DynamicEntity* power = new PULaser(_x, _y, 4);
		m_toAdd.push_back(power);
	}
	//Life Up
	else if (RNG > 0 && RNG < 4)
	{
		DynamicEntity* power = new PULaser(_x, _y, 3);
		m_toAdd.push_back(power);
	}
}

void Game::sMovement()
{
	m_player->movement();
	for (size_t i = 0; i < m_aliveEntities.size(); ++i) {
		m_aliveEntities[i]->movement();
	}

	for (auto shield : getEntities("shield"))
	{
		shield->sprite.setPosition(m_player->getX()-esOffset, m_player->getY()-esOffset);
		shield->boundingBox.setPosition(m_player->getX()-esOffset, m_player->getY()-esOffset);
		if (shield->clock.getElapsedTime() > sf::seconds(2))
		{
			shield->is_active = false;
		}
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


void Game::sceneChange()
{
	m_sceneChange = true;
	m_currentFrame = -60;
	entityKiller();
}

void Game::sceneChanger()
{
	if (m_currentFrame >= 0 && m_sceneChange)
	{
		background.setPosition(0, 0);
		background2.setPosition(0, 0);
		backgroundmirror.setPosition(0, -HEIGHT);
		backgroundmirror2.setPosition(0, -HEIGHT);
		m_sceneChange = false;
	}
}

void Game::interface()
{
	frametest.setString(tframe + std::to_string(m_currentFrame));
	nlifes.setString(std::to_string(m_player->lifes));
	points.setString(std::to_string(npoints));
	if (energyLevel == 0)
	{
		essprite.setTextureRect(estextureRect0);
	}
	else if (energyLevel == 1)
	{
		essprite.setTextureRect(estextureRect1);
	}
	else if (energyLevel == 2)
	{
		essprite.setTextureRect(estextureRect2);
	}
	else if (energyLevel == 3)
	{
		essprite.setTextureRect(estextureRect3);
	}

}

void Game::entityKiller()
{
	for (auto entity : m_aliveEntities)
	{
		entity->is_active = false;
	}
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

/*Por hacer:
- Sistema de Puntuacion
- Bandera para no sobrecargar el escudo
- X Blast
- Interfaz
- Vidas del jugador, gameover
- Checkpoints
- 2 Enemigos nuevos
- Boss
- Misiles Boss
- Completar menu Inicio
- Agregar capa final de Bg
- Sonidos y Musica
*/