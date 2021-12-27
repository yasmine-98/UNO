#include <sstream>
#include "PauseState.h"
#include "GameState.h"
#include "Definitions.h"
#include <iostream>
namespace MB
{
	PauseState::PauseState(GameDataRef data) : _data(data)
	{

	}
	void PauseState::init()
	{
		Pause_background.setTexture(_data->assets.GetTexture("Pause Background"));
	}
	void PauseState::HandleInput()
	{
		sf::Event e;
		while (_data->window.pollEvent(e))
		{
			if (e.type == sf::Event::Closed)
			{
				_data->window.close();
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			{
				_data->machine.RemoveState();
			}
		}
	}
	void PauseState::Update(float dt)
	{

	}
	void PauseState::Draw(float dt)
	{
		_data->window.clear();
		_data->window.draw(Pause_background);
		_data->window.display();
	}
}
