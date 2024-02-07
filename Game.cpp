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
	for (size_t i = 0; i < bullets.size(); ++i) {
		m_window.draw(bullets[i]->sprite);
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
				else if (event.key.code == sf::Keyboard::K) { shoot(); }

				break;
			}
			case sf::Event::KeyReleased:
			{
				     if (event.key.code == sf::Keyboard::A) { player->left = false; }
				else if (event.key.code == sf::Keyboard::D) { player->right = false; }
				else if (event.key.code == sf::Keyboard::W) { player->up = false; }
				else if (event.key.code == sf::Keyboard::S) { player->down = false; }

			    break;
			}
		}
	}
}

void Game::run() 
{
	while (m_running)
	{
		sUserInput();
		player->movement();
		for (size_t i = 0; i < bullets.size(); ++i) {
			bullets[i]->movement();
		}
		sRender();
	}
}

void Game::shoot()
{
	Bullet* bullet = new Bullet(player->getX() + 43 , player->getY(), 10);
	bullets.push_back(bullet);
}