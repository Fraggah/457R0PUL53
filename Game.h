#pragma once
#include <SFML/Graphics.hpp>
#include "classes/Player.h"
#include "classes/Bullet.h"
#include "classes/Enemy.h"
#include <vector>
#include <map>
#include <algorithm>
#include <type_traits>


class Game
{
	sf::RenderWindow m_window;
	Player* player = new Player(100, 100, 4);
	bool m_running = true;
	std::map < std::string, std::vector<DynamicEntity*>> entityMap;
	std::vector<DynamicEntity*> dentities;
	std::vector<DynamicEntity*> toAdd;
	int frameCount = 0;
	int lastFrameSpawn = 0;
	sf::Clock clock;

	void init();
	void sRender();
	void sUserInput();
	void sCollisions();
	

	void shoot();
	void enemySpawn();
	void removeDeadEntities(std::vector<DynamicEntity*>& vec);
	void update();
	const std::vector<DynamicEntity*>& getEntities(const std::string& tag);

public:
	Game();
	void run();
};

