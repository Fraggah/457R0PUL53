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

	renderTexture.create(WIDTH, HEIGHT);

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

	gameover.setFont(font);
	gameover.setFillColor(sf::Color::White);
	gameover.setCharacterSize(24);
	gameover.setString(gotext);
	gameover.setPosition(430, 450);

	wintext.setFont(font);
	wintext.setFillColor(sf::Color::White);
	wintext.setCharacterSize(24);
	wintext.setString(winstring);
	wintext.setPosition(124, 450);

	pauseText.setFont(font);
	pauseText.setFillColor(sf::Color::White);
	pauseText.setCharacterSize(24);
	pauseText.setString(pauseString);
	pauseText.setPosition(460, 445);

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

	pauserect.setSize(sf::Vector2f(WIDTH, HEIGHT));
	pauserect.setFillColor(sf::Color(0, 0, 0, 180));

	maintheme.openFromFile("assets/music/Intro.ogg");
	level1music.openFromFile("assets/music/Level1.ogg");
	bossmusic.openFromFile("assets/music/BossAries.ogg");
	maintheme.play();

	level1music.setLoop(true);
	bossmusic.setLoop(true);

	shootbuffer.loadFromFile("assets/sounds/shoot.wav");
	deathbuffer.loadFromFile("assets/sounds/death.wav");
	enemyboombuffer.loadFromFile("assets/sounds/enemyboom.wav");
	bosshitbuffer.loadFromFile("assets/sounds/hitboss.wav");
	startbuffer.loadFromFile("assets/music/Start.ogg");
	powerUpbuffer.loadFromFile("assets/sounds/powerUp.ogg");
	energyChargebuffer.loadFromFile("assets/sounds/energyCharge.ogg");
	energyShieldbuffer.loadFromFile("assets/sounds/energyShield.ogg");
	energyBulletbuffer.loadFromFile("assets/sounds/energyBullet.ogg");

	shootsound.setBuffer(shootbuffer);
	deathsound.setBuffer(deathbuffer);
	enemyboomsound.setBuffer(enemyboombuffer);
	bosshitsound.setBuffer(bosshitbuffer);
	startsound.setBuffer(startbuffer);
	powerUpsound.setBuffer(powerUpbuffer);
	energyChargesound.setBuffer(energyChargebuffer);
	energyShieldsound.setBuffer(energyShieldbuffer);
	energyBulletsound.setBuffer(energyBulletbuffer);

}

void Game::sRender() 
{
	renderTexture.clear();
	if (m_menu)
	{
		renderTexture.draw(titlesprite);
		renderTexture.draw(copy);
		renderTexture.draw(hiscore);
		if (pressonoff.getElapsedTime() > sf::seconds(0.5))
		{
			renderTexture.draw(menutext);
		}
		if (pressonoff.getElapsedTime() > sf::seconds(1))
		{
			pressonoff.restart();
		}

	}
	if (m_gameOver)
	{
		renderTexture.draw(gameover);
	}
	if (m_bossDefeated)
	{
		renderTexture.draw(wintext);
	}
	if (m_sceneChange && (!m_gameOver || !m_bossDefeated))
	{
		renderTexture.draw(leveltext);
	}
	if (!m_menu && !m_sceneChange && !m_gameOver && !m_bossDefeated)
	{
		renderTexture.draw(background);
		renderTexture.draw(backgroundmirror);
		renderTexture.draw(background2);
		renderTexture.draw(backgroundmirror2);
		if (m_texturize)
		{
			for (size_t i = 0; i < m_aliveEntities.size(); ++i) {
				renderTexture.draw(m_aliveEntities[i]->sprite);
			}
			renderTexture.draw(m_player->sprite);
		}
		if (m_debug)
		{
			for (size_t i = 0; i < m_aliveEntities.size(); ++i) {
				renderTexture.draw(m_aliveEntities[i]->boundingBox);
			}
			for (size_t i = 0; i < m_aliveEntities.size(); ++i) {
				renderTexture.draw(m_aliveEntities[i]->boundingBox2);
			}
			for (size_t i = 0; i < m_aliveEntities.size(); ++i) {
				renderTexture.draw(m_aliveEntities[i]->boundingBox3);
			}
			renderTexture.draw(m_player->boundingBox);
			renderTexture.draw(frametest);
		}
		renderTexture.draw(lifeInterface);
		renderTexture.draw(nlifes);
		renderTexture.draw(points);
		renderTexture.draw(energyShieldInterface);
		renderTexture.draw(essprite);
		if (m_paused)
		{
			renderTexture.draw(pauserect);
			renderTexture.draw(pauseText);
		}
	}
	renderTexture.display();
	renderSprite.setTexture(renderTexture.getTexture(), true);
	m_window.clear();
	m_window.draw(renderSprite);
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
				if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::F11) {

                    if (m_window.getSize().x == WIDTH && m_window.getSize().y == HEIGHT) {
                        sf::VideoMode fullscreenMode = sf::VideoMode::getFullscreenModes()[0];
                        float scale = static_cast<float>(fullscreenMode.height) / static_cast<float>(HEIGHT); //static_cast "convierte" a float los valores para que scale pueda tomar un valor real
                        m_window.create(fullscreenMode, "Astropulse", sf::Style::Fullscreen);
						m_window.setMouseCursorVisible(false);
						m_window.setFramerateLimit(60);
                        renderSprite.setScale(scale, scale);
                        renderSprite.setPosition((fullscreenMode.width - (WIDTH*scale))/2, 0);//al ancho de la pantalla, le resto el ancho de la ventana multiplicada por el factor de escala 
                    }																		  //y ese valor lo divido en 2 para centrar la pantalla, posiciono la x de renderTexture en ese valor resultante
                    else {
                        m_window.create(sf::VideoMode(WIDTH, HEIGHT), "Astropulse");
						m_window.setMouseCursorVisible(true);
						m_window.setFramerateLimit(60);
                        renderSprite.setScale(1.f, 1.f);
                        renderSprite.setPosition(0, 0);
                    }
                
            }
				else if (event.key.code == sf::Keyboard::A) { m_player->left  = true; }
				else if (event.key.code == sf::Keyboard::D) { m_player->right = true; }
				else if (event.key.code == sf::Keyboard::W) { m_player->up    = true; }
				else if (event.key.code == sf::Keyboard::S) { m_player->down  = true; }
				else if (event.key.code == sf::Keyboard::K && !m_paused && !m_goToNextLevel) { shoot(); }
				else if (event.key.code == sf::Keyboard::L && !m_paused && energyShieldTime.getElapsedTime() > sf::seconds(2)) { energyShield(); }
				else if (event.key.code == sf::Keyboard::Enter)
				{
					if (m_gameOver)
					{
						m_menu = true;
						m_gameOver = false;
					}
					else if (m_menu)
					{
						m_menu = false;
						sceneChange();
						maintheme.stop();
						startsound.play();
						m_player->setX(480);m_player->setY(800);

					}
					else if (m_bossDefeated)
					{
						m_menu = true;
						m_bossDefeated = false;
						maintheme.stop();
					}
			
				}
				else if (event.key.code == sf::Keyboard::F1)
				{
					m_texturize ? m_texturize = false : m_texturize = true;
				}
				else if (event.key.code == sf::Keyboard::F2)
				{
					m_debug ? m_debug = false : m_debug = true;
				}
				else if (event.key.code == sf::Keyboard::P && m_currentFrame > 0)
				{
					m_paused ? m_paused = false : m_paused = true;
					if (!m_menu && !m_gameOver && !m_goToNextLevel && !m_sceneChange)
					{
						startsound.play();
					}
				}

				break;
			}
			case sf::Event::KeyReleased:
			{
				     if (event.key.code == sf::Keyboard::A ) { m_player->left  = false; }
				else if (event.key.code == sf::Keyboard::D ) { m_player->right = false; }
				else if (event.key.code == sf::Keyboard::W ) { m_player->up    = false; }
				else if (event.key.code == sf::Keyboard::S ) { m_player->down  = false; }

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
			m_player->lifes--;
			m_laserOn = false;
			m_tripleOn = false;
			m_inDead = true;
			energyLevel = 0;
			level1music.stop();
			bossmusic.stop();
			deathsound.play();
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
			m_player->lifes--;
			m_laserOn = false;
			m_tripleOn = false;
			m_inDead = true;
			energyLevel = 0;
			level1music.stop();
			bossmusic.stop();
			deathsound.play();
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
			energyLevel = 0;
			m_laserOn = false;
			m_tripleOn = false;
			m_inDead = true;   //esto podria servir para el win tambien... revisar o cambiar logica
			level1music.stop();
			bossmusic.stop();
			deathsound.play();
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
				powerUpsound.play();
				m_player->points += 500;
			}
			else if (pup->type == 2)
			{
				m_laserOn = false;
				m_tripleOn = true;
				powerUpsound.play();
				m_player->points += 1000;
			}
			else if (pup->type == 3)
			{
				m_player->lifes++;
				powerUpsound.play();
			}
			else if (pup->type == 4)
			{
				for (auto enemy : getEntities("enemy"))
				{
					enemy->is_active = false;
					DynamicEntity* boom = new EntityBoom(enemy->getX(), enemy->getY(), false);
					m_toAdd.push_back(boom);
					enemyboomsound.play();
				}
				for (auto enemyb : getEntities("enemybullet"))
				{
					enemyb->is_active = false;
				}
				powerUpsound.play();
				m_player->points += 2500;
			}
			else if (pup->type == 5)
			{
				energyChargesound.play();
				m_player->points + 250;
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
					enemyboomsound.play();
					int RNG = rand() % 100 + 1;
					if (RNG < 4 && enemiesKilled != 30 && enemiesKilled != 15)
					{
						spawnPowerUp(enemy->getX(), enemy->getY());
					}
					enemiesKilled++;
					if (enemiesKilled == 30)
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
					enemyboomsound.play();
					m_goToNextLevel = true;
					winTime.restart();
					bossmusic.stop();
					maintheme.play();
					//logica de pasar el nivel deberia estar en otro lado para poder escalar el proyecto
					m_player->setX(1500); m_player->setY(1900);
					energyLevel = 0;
					m_laserOn = false;
					m_tripleOn = false;
					m_checkpoint1 = false;
					m_checkpoint2 = false;
				}
				else
				{
					DynamicEntity* boom = new EntityBoom(enemy->getX()+120, enemy->getY()+120, false);
					boom->sprite.setColor(sf::Color::Blue);
					m_toAdd.push_back(boom);
					enemy->lifes--; //crear alguna animacion para indicar que recibió el impacto
					bosshitsound.play();
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
				energyBulletsound.play();
				m_player->points += 50;
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
		if (!m_paused && !m_menu && !m_goToNextLevel && !m_gameOver)
		{
			sMovement();
			sCollisions();
			enemyShoot();
			boomSpamTime();
			playerRespawn();
			m_currentFrame++;
			level1(); //funcionaaaaaaa :D
		}
		sRender();
		winGame();
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

void Game::shoot()
{
	if (!m_laserOn && !m_tripleOn && !m_menu && !m_sceneChange && !m_gameOver && !m_goToNextLevel)
	{
		Bullet* bullet = new BSimple(m_player->boundingBox.getPosition().x, m_player->boundingBox.getPosition().y - 32, 2);
		m_toAdd.push_back(bullet);
		shootsound.play();
	}

	if (m_laserOn && !m_menu && !m_sceneChange && !m_gameOver && !m_goToNextLevel)
	{
		Bullet* bulletL = new BLaser(m_player->boundingBox.getPosition().x - 16, m_player->boundingBox.getPosition().y, 18);
		Bullet* bulletR = new BLaser(m_player->boundingBox.getPosition().x + 16, m_player->boundingBox.getPosition().y, 18);
		m_toAdd.push_back(bulletR);
		m_toAdd.push_back(bulletL);
		shootsound.play();
	}

	if (m_tripleOn && !m_menu && !m_sceneChange && !m_gameOver && !m_goToNextLevel)
	{
		float angle = rand() % 5;
		Bullet* bulletC = new BTriple(m_player->boundingBox.getPosition().x, m_player->boundingBox.getPosition().y - 32, 0, 20);
		Bullet* bulletL = new BTriple(m_player->boundingBox.getPosition().x, m_player->boundingBox.getPosition().y - 32, -angle, 20);
		Bullet* bulletR = new BTriple(m_player->boundingBox.getPosition().x, m_player->boundingBox.getPosition().y - 32, angle, 20);
		m_toAdd.push_back(bulletC);
		m_toAdd.push_back(bulletL);
		m_toAdd.push_back(bulletR);
		shootsound.play();
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

void Game::spawnEye(int _x)
{
	Enemy* enemy = new Eeye(_x);
	m_toAdd.push_back(enemy);
}

void Game::spawnEyePath(int L, int R)
{
	for (int i = 0; i <= 16; i++) {
		if (i > L && i < R) {}
		else { spawnEye(i * 64); }
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
		energyShieldsound.play();
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

void Game::gameOver()
{
	m_gameOver = true;
	entityKiller();
	m_player->lifes = 3;
	m_player->points = 0;
	m_checkpoint1 = false;
	m_checkpoint2 = false;
	energyLevel = 0;
}

void Game::winGame()
{
	if (winTime.getElapsedTime() > sf::seconds(2) && m_goToNextLevel)
	{
		m_bossDefeated = true;
		winTime.restart();
		m_goToNextLevel = false;
		entityKiller();
		m_player->lifes = 3;
		m_player->points = 0;
		m_checkpoint1 = false;
		m_checkpoint2 = false;
		energyLevel = 0;
		m_laserOn = false;
		m_tripleOn = false;
	}
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

void Game::playerRespawn()
{
	if (m_inDead)
	{
		if (deathTime.getElapsedTime() > sf::seconds(1) && m_player->lifes != 0)
		{
			sceneChange();
			m_player->setX(480);m_player->setY(800);
			m_laserOn = false;
			m_tripleOn = false;
			m_inDead = false;

		}
		else if (deathTime.getElapsedTime() > sf::seconds(1) && m_player->lifes == 0)
		{
			gameOver();
			m_player->setX(480);m_player->setY(800);
			m_laserOn = false;
			m_tripleOn = false;
			m_inDead = false;
		}
	}
}

void Game::interface()
{
	if (m_menu)
	{
		npoints = 0; //acomodar esto luego y setear guardado de hiscore
	}
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
	switch (m_currentFrame) {  //aqui poner logica de checkpoint???
	case 10:  level1music.play();break;
	case 150: if (m_checkpoint1 == true) { m_currentFrame += 2850; }
			  if (m_checkpoint2 == true) { m_currentFrame += 3930; }break;
	case 160:spawnDoubleCannon(true); m_checkpoint1 = false; m_checkpoint2 = false;break;
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
		//checkpoint 1
	case 3000:spawnDoubleCannon(true);spawnDoubleCannon(false); m_checkpoint1 = true; m_checkpoint2 = false; break;
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
	case 3650:spawnBomber(2);spawnBomber(1);spawnBomber(3);break;
	case 3900:spawnCannon();break;
	case 3940:spawnCannon();break;
	case 3980:spawnCannon();break;
	case 4020:spawnCannon();break;
	case 4039:spawnCannon();break;
		//checkpoint 2
	case 4080:spawnEyePath(0, 16);break;
	case 4100:spawnEyePath(0, 15);break;	
	case 4120:spawnEyePath(0, 14);break;
	case 4140:spawnEyePath(0, 13);break;
	case 4160:spawnEyePath(1, 12);break;
	case 4180:spawnEyePath(1, 11);break;
	case 4200:spawnEyePath(2, 11);break;
	case 4220:spawnEyePath(2, 10);break;
	case 4240:spawnEyePath(3, 10);break;
	case 4260:spawnEyePath(3, 9);break;
	case 4280:spawnEyePath(3, 8);break;
	case 4300:spawnEyePath(3, 7);m_checkpoint1 = false; m_checkpoint2 = true; break;
	case 4320:spawnEyePath(3, 7);break;
	case 4340:spawnEyePath(4, 8);break;
	case 4360:spawnEyePath(4, 8);break;
	case 4380:spawnEyePath(5, 9);break;
	case 4400:spawnEyePath(5, 9);break;
	case 4420:spawnEyePath(6, 10);break;
	case 4440:spawnEyePath(6, 10);break;
	case 4460:spawnEyePath(7, 11);break;
	case 4480:spawnEyePath(7, 11);break;
	case 4500:spawnEyePath(8, 12);break;
	case 4520:spawnEyePath(8, 12);break;
	case 4540:spawnEyePath(9, 13);break;
	case 4560:spawnEyePath(9, 13);break;
	case 4580:spawnEyePath(10, 14);break;
	case 4600:spawnEyePath(10, 14);break;
	case 4620:spawnEyePath(10, 14);break;
	case 4640:spawnEyePath(10, 14);break;
	case 4660:spawnEyePath(9, 13);break;
	case 4680:spawnEyePath(9, 13);break;
	case 4700:spawnEyePath(8, 12);break;
	case 4720:spawnEyePath(8, 12);break;
	case 4740:spawnEyePath(7, 11);break;
	case 4760:spawnEyePath(7, 11);break;
	case 4780:spawnEyePath(6, 10);break;
	case 4800:spawnEyePath(6, 10);break;
	case 4820:spawnEyePath(7, 11);break;
	case 4840:spawnEyePath(7, 11);break;
	case 4860:spawnEyePath(8, 12);break;
	case 4880:spawnEyePath(8, 12);break;
	case 4900:spawnEyePath(9, 11);break;
	case 4920:spawnEyePath(3, 12);break;
	case 4940:spawnEyePath(2, 12);break;
	case 4960:spawnEyePath(1, 11);break;
	case 4980:spawnEyePath(1, 10);break;
	case 5000:spawnEyePath(1, 5);break;
	case 5020:spawnEyePath(1, 5);break;
	case 5040:spawnEyePath(1, 5);break;
	case 5060:spawnEyePath(2, 6);break;
	case 5080:spawnEyePath(2, 6);break;
	case 5100:spawnEyePath(2, 6);break;
	case 5120:spawnEyePath(3, 7);break;
	case 5140:spawnEyePath(3, 7);break;
	case 5160:spawnEyePath(4, 8);break;
	case 5180:spawnEyePath(4, 8);break;
	case 5200:spawnEyePath(5, 9);break;
	case 5220:spawnEyePath(5, 9);break;
	case 5240:spawnEyePath(6, 10);break;
	case 5260:spawnEyePath(6, 10);break;
	case 5280:spawnEyePath(7, 11);break;
	case 5300:spawnEyePath(7, 11);break;
	case 5320:spawnEyePath(8, 12);break;
	case 5340:spawnEyePath(8, 12);break;
	case 5360:spawnEyePath(9, 13);break;
	case 5380:spawnEyePath(9, 13);break;
	case 5400:spawnEyePath(10, 14);break;
	case 5420:spawnEyePath(10, 14);break;
	case 5440:spawnEyePath(11, 15);break;
	case 5460:spawnEyePath(11, 15);break;
	case 5480:spawnEyePath(11, 15);break;
	case 5500:spawnEyePath(10, 14);break;
	case 5520:spawnEyePath(10, 14);break;
	case 5540:spawnEyePath(9, 13);break;
	case 5560:spawnEyePath(9, 13);break;
	case 5580:spawnEyePath(8, 12);break;
	case 5600:spawnEyePath(9, 11);break;
	case 5620:spawnEyePath(8, 12);break;
	case 5640:spawnEyePath(7, 12);break;
	case 5660:spawnEyePath(7, 13);break;
	case 5680:spawnEyePath(6, 14);break;
	case 5700:spawnEyePath(6, 13);break;
	case 5720:spawnEyePath(5, 13);break;
	case 5740:spawnEyePath(4, 14);break;
	case 5760:spawnEyePath(3, 14);break;
	case 5780:spawnEyePath(2, 15);break;
	case 5800:spawnEyePath(1, 16);break;
	case 6100:spawnBoss();level1music.stop();bossmusic.play();

	}

}

/*Por hacer:
- Sistema de Puntuacion - HECHO
- Bandera para no sobrecargar el escudo - HECHO
- X Blast - HECHO
- Interfaz - HECHO
- Vidas del jugador, gameover - HECHO
- Checkpoints - HECHO
- 2 Enemigos nuevos - HECHO
- Boss - HECHO
- Completar menu Inicio - HECHO
- Pantalla de victoria - HECHO
- Mejorar pausa - HECHO
- Agregar capa final de Bg
- Sonidos y Musica - HECHO
- Chequear tiempo dedsp del gameover..
- chequear ganar level -HECHO
- sonidos power ups - HECHO
- animacion x blast - HECHO
- sonido colision shiel bullet - HECHO
*/