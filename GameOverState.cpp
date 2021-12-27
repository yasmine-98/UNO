#include <sstream>
#include "GameOverState.h"
#include "MainMenuState.h"
#include "Definitions.h"
#include <iostream>
namespace MB
{
	GameOverState::GameOverState(GameDataRef data, joueur& j3, joueur& j4) : _data(data)
	{
		j1 = &j3;
		j2 = &j4;
		clock.restart();
	}
	void GameOverState::init()
	{
		_background1.setTexture(_data->assets.GetTexture("Game Over 1 Background"));
		_background2.setTexture(_data->assets.GetTexture("Game Over 2 Background"));
	}
	void GameOverState::HandleInput()
	{
		sf::Event e;
		while (_data->window.pollEvent(e))
		{
			if (e.type == sf::Event::Closed)
			{
				_data->window.close();
			}
		}
	}
	void GameOverState::Update(float dt)
	{
		if (clock.getElapsedTime().asSeconds() > 3.0)
			_data->machine.AddState(StateRef(new MainMenuState(_data)));
	}
	void GameOverState::Draw(float dt)
	{
		_data->window.clear();
		if (j1->nbr_de_cartes() == 0)
			_data->window.draw(_background1);
		else if (j2->nbr_de_cartes() == 0)
			_data->window.draw(_background2);
		_data->window.display();
	}
}
