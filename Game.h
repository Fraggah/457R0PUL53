#pragma once
#include <SFML/Graphics.hpp>
#include "classes/Player.h"

class Game
{
	sf::RenderWindow m_window;
	Player* player = new Player(100, 100, 0);
	bool			 m_running = true;

	void init();
	void sRender();
	void sUserInput();

public:
	Game();
	void run();
};

