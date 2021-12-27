#include "MainMenuState.h"
#include "GameState.h"
#include <sstream>
#include "Definitions.h"
#include <iostream>
namespace MB
{
	MainMenuState::MainMenuState(GameDataRef data) : _data(data)
	{

	}
	void MainMenuState::loadnextstate()
	{
		nextstate = new GameState(_data);
	}
	void MainMenuState::init()
	{
		LoadNext();
		_QuitButton.setTexture(_data->assets.GetTexture("Quit Button"));
		_QuitButton2.setTexture(_data->assets.GetTexture("Quit Button 2"));
		_PlayButton.setTexture(_data->assets.GetTexture("Play Button"));
		_PlayButton2.setTexture(_data->assets.GetTexture("Play Button 2"));
		_Background.setTexture(_data->assets.GetTexture("Main Menu Background"));
		_QuitButton.setPosition(450, 350);
		_QuitButton2.setPosition(450, 350);
		_PlayButton.setPosition(450, 150);
		_PlayButton2.setPosition(450, 150);
	}
	void MainMenuState::HandleInput()
	{
		sf::Event e;
		while (_data->window.pollEvent(e))
		{
			if (e.type == sf::Event::Closed)
			{
				_data->window.close();
			}
			else if (_data->input.isSpriteClicked(_PlayButton, sf::Mouse::Left, _data->window))
				pressed_play = true;
			else if (e.type == sf::Event::MouseButtonReleased)
			{
				sf::Vector2i p = _data->input.MousePosition(_data->window);
				if ((p.x > 450) && (p.x < 748) && (p.y > 150) && (p.y < 217))
					released_play = true;
				else if ((p.x > 450) && (p.x < 748) && (p.y > 350) && (p.y < 417))
					released_quit = true;
			}
			else if (_data->input.isSpriteClicked(_QuitButton, sf::Mouse::Left, _data->window))
				pressed_quit = true;
		}
	}
	void MainMenuState::Update(float dt)
	{
		if (released_play == true)
		{
			nextstateloader.join();
			_data->machine.AddState(StateRef(nextstate));
		}
		if (released_quit == true)
		{
			_data->window.close();
		}
	}
	void MainMenuState::Draw(float dt)
	{
		_data->window.clear();
		_data->window.draw(_Background);
		if (pressed_play == true)
		{
			_data->window.draw(_PlayButton2);
		}
		else
			_data->window.draw(_PlayButton);
		if (pressed_quit == true)
		{
			_data->window.draw(_QuitButton2);
		}
		else
			_data->window.draw(_QuitButton);
		_data->window.display();
	}
}
