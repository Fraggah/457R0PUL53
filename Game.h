#pragma once
#include <SFML/Graphics.hpp>
#include "classes/Player.h"
#include "classes/PEnergyShield.h"
#include "classes/Bullet.h"
#include "classes/Enemy.h"
#include "classes/EDoubleCannon.h"
#include "classes/EAssault.h"
#include "classes/ECannon.h"
#include "classes/EBomber.h"
#include "classes/BSimple.h"
#include "classes/Blaser.h"
#include "classes/BTriple.h"
#include "classes/BEnemy.h"
#include "classes/EntityBoom.h"
#include "classes/PULaser.h"
#include "classes/BossAries.h"
#include "classes/EBossBullet.h"
#include <vector>
#include <map>
#include <algorithm>
#include <type_traits>
#include <ctime>
#include <cstdlib>

#define WIDTH 1024
#define HEIGHT 960

class Game
{
	sf::RenderWindow m_window;
	Player* m_player = new Player(480, 800, 6);
	bool m_running = true;
	std::map < std::string, std::vector<DynamicEntity*>> m_entityMap;
	std::vector<DynamicEntity*> m_aliveEntities;
	std::vector<DynamicEntity*> m_toAdd;
	int m_currentFrame = 0;
	sf::Clock clock;
	bool m_debug = false;
	bool m_texturize = true;
	bool m_paused = false;
	float esOffset = 32;
	int enemiesKilled = 0;
	int energyLevel = 0;
	bool m_laserOn = false;
	bool m_tripleOn = false;
	bool m_sceneChange = false;
	bool m_menu = true;
	bool m_inDead = false;
	bool m_eson;
	sf::Clock deathTime;
	sf::Clock pressonoff;
	sf::Clock energyShieldTime;

	int cannonIterator = 0;         //enemy manager
	bool cannonLR = true;           //enemy manager


	sf::Font font;
	sf::Text frametest;
	std::string tframe = "F: ";
	sf::Text menutext;
	std::string press = "Press Start";
	sf::Text leveltext;
	std::string leveln = "Level 1";
	sf::Text copy;
	std::string copystring = "© 2024 Silvio Stefanucci";
	sf::Text hiscore;
	std::string histring = "Hi 100000";
	sf::Text nlifes;
	sf::Text energyShieldInterface;
	std::string esstring = "ES";
	sf::Text points;
	int npoints;
	sf::Sprite background;
	sf::Sprite backgroundmirror;
	sf::Texture btexture;
	sf::Sprite background2;
	sf::Sprite backgroundmirror2;
	sf::Texture btexture2;
	sf::Sprite titlesprite;
	sf::Texture titletexture;
	sf::Sprite lifeInterface;
	sf::Texture lifeTexture;
	sf::Sprite essprite;
	sf::Texture estexture;
	sf::IntRect estextureRect0{0, 0, 0, 0};
	sf::IntRect estextureRect1{0, 0, 5, 3};
	sf::IntRect estextureRect2{0, 0, 10, 3};
	sf::IntRect estextureRect3{0, 0, 15, 3};

	void init();
	void sRender();
	void sUserInput();
	void sCollisions();
	void sMovement();

	void playerRespawn();
	void spawnPowerUp(float _x, float _y);
	void energyShield();
	void shoot();
	void shootBLaser();
	void shootBTriple();
	void spawnDoubleCannon(bool _l);
	void spawnAssault();
	void spawnCannon();
	void spawnBomber(int pos);
	void enemyShoot();
	void boomSpamTime();
	void removeDeadEntities(std::vector<DynamicEntity*>& vec);
	void update();
	const std::vector<DynamicEntity*>& getEntities(const std::string& tag);

	void boosDamaged();
	void spawnBoss();
	void entityKiller();
	void sceneChange();
	void sceneChanger();
	void interface();
	void level1();

public:
	Game();
	void run();
};

