#include "Game.h"
#include "SplashState.h"
#include "Definitions.h"
namespace MB
{
	Game::Game(int width, int height, std::string title)
	{
		_data->window.create(sf::VideoMode(width, height), title, sf::Style::Close | sf::Style::Titlebar | sf::Style::Resize);
		sf::Image icon;
		icon.loadFromFile(ICON_PATH);
		_data->window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
		_data->window.setFramerateLimit(60);
		_data->machine.AddState(StateRef(new SplashState(_data)));
		run();
	}
	void Game::run()
	{
		float accumulateur = 0.0f;
		float newtime;
		float currenttime = _clock.getElapsedTime().asSeconds();
		float frametime;
		float interpolation;
		while (_data->window.isOpen())
		{
			_data->machine.ProcessStateChanges();
			newtime = _clock.getElapsedTime().asSeconds();
			frametime = newtime - currenttime;
			currenttime = newtime;
			if (frametime > 0.25f)
				frametime = 0.25f;
			accumulateur += frametime;
			while (accumulateur >= dt)
			{
				_data->machine.CurrentState()->HandleInput();
				_data->machine.CurrentState()->Update(dt);
				accumulateur -= dt;
			}
			interpolation = accumulateur / dt;
			_data->machine.CurrentState()->Draw(interpolation);


		}
	}
}