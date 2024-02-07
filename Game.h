#pragma once
#include <SFML/Graphics.hpp>
#include "classes/Player.h"
#include "classes/Bullet.h"
#include <vector>

class Game
{
	sf::RenderWindow m_window;
	Player* player = new Player(100, 100, 4);
	bool m_running = true;
	std::vector<Bullet*> bullets;

	void init();
	void sRender();
	void sUserInput();

	void shoot();

public:
	Game();
	void run();
};

