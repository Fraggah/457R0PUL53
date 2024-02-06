#include "Game.h"

Game::Game() 
{
	init();
}

void Game::init() 
{
	m_window.create(sf::VideoMode(800, 600), "AstroPulse", sf::Style::Close);
	m_window.setFramerateLimit(60);
}

void Game::sRender() 
{
	m_window.clear();
	m_window.draw(player->sprite);
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
		}
	}
}

void Game::run() 
{
	while (m_running)
	{
		sRender();
		sUserInput();
		player->movement();
	}
}