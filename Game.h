#pragma once
#include <SFML/Graphics.hpp>
#include "classes/Player.h"
#include "classes/Bullet.h"
#include "classes/Enemy.h"
#include "classes/EDoubleCannon.h"
#include "classes/EAssault.h"
#include "classes/ECannon.h"
#include "classes/BSimple.h"
#include "classes/Blaser.h"
#include "classes/BTriple.h"
#include "classes/BEnemy.h"
#include "classes/EntityBoom.h"
#include <vector>
#include <map>
#include <algorithm>
#include <type_traits>

#define WIDTH 1024
#define HEIGHT 1024

class Game
{
	sf::RenderWindow m_window;
	Player* player = new Player(500, 900, 6);
	bool m_running = true;
	std::map < std::string, std::vector<DynamicEntity*>> entityMap;
	std::vector<DynamicEntity*> aliveEntities;
	std::vector<DynamicEntity*> toAdd;
	int frameCount = 0;
	int lastFrameSpawn = 0;
	sf::Clock clock;
	bool debug = false;
	bool texturize = true;
	int cannonIterator = 0;

	void init();
	void sRender();
	void sUserInput();
	void sCollisions();
	void sMovement();

	void shootBSimple();
	void shootBLaser();
	void shootBTriple();
	void enemySpawn();
	void spawnAssault();
	void spawnCannon();
	void enemyShoot();
	void boomSpamTime();
	void removeDeadEntities(std::vector<DynamicEntity*>& vec);
	void update();
	const std::vector<DynamicEntity*>& getEntities(const std::string& tag);

public:
	Game();
	void run();
};

