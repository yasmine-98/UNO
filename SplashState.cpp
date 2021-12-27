#include <sstream>
#include "SplashState.h"
#include "MainMenuState.h"
#include "Definitions.h"
#include <iostream>
namespace MB
{
	SplashState::SplashState(GameDataRef data) : _data(data)
	{

	}
	SplashState::~SplashState()
	{

	}
	void SplashState::init()
	{
		_data->assets.AddTexture("bg", SPLASH_SCENE_BACKGROUND_FILEPATH);
		_background.setTexture(_data->assets.GetTexture("bg"));
	}
	void SplashState::HandleInput()
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
	void SplashState::Update(float dt)
	{
		if (draw == true)
		{
			_data->assets.AddTexture("Couleur De Couleur", CHANGEMENT_DE_COULEUR_FILEPATH);
			_data->assets.AddTexture("UNO Button", UNO_BUTTON);
			_data->assets.AddTexture("Game Background", GAME_BACKGROUND_FILEPATH);
			_data->assets.AddTexture("UNO Cartes", UNO_CARTES_FILEPATH);
			_data->assets.AddTexture("Carte Vert", VERT_FILEPATH);
			_data->assets.AddTexture("Carte Jaune", JAUNE_FILEPATH);
			_data->assets.AddTexture("Carte Bleu", BLEU_FILEPATH);
			_data->assets.AddTexture("Carte Rouge", ROUGE_FILEPATH);
			_data->assets.AddTexture("Carte +4Vert", VERT4_FILEPATH);
			_data->assets.AddTexture("Carte +4Jaune", JAUNE4_FILEPATH);
			_data->assets.AddTexture("Carte +4Bleu", BLEU4_FILEPATH);
			_data->assets.AddTexture("Carte +4Rouge", ROUGE4_FILEPATH);
			_data->assets.AddTexture("Game Over 1 Background", GAME_OVER1_BACKGROUND_FILEPATH);
			_data->assets.AddTexture("Game Over 2 Background", GAME_OVER2_BACKGROUND_FILEPATH);
			_data->assets.AddTexture("Carte Cachee", CARTE_CACHEE_FILEPATH);
			_data->assets.AddTexture("Main Menu Background", MAIN_MENU_BACKGROUND_FILEPATH);
			_data->assets.AddTexture("Play Button", PLAY_BUTTON_FILEPATH);
			_data->assets.AddTexture("Play Button 2", PLAY_BUTTON2_FILEPATH);
			_data->assets.AddTexture("Quit Button", QUIT_BUTTON_FILEPATH);
			_data->assets.AddTexture("Quit Button 2", QUIT_BUTTON2_FILEPATH);
			_data->assets.AddTexture("Pause Background", PAUSE_BACKGROUND_FILEPATH);
		}
		if (_clock.getElapsedTime().asSeconds() > SPLASH_STATE_SHOW_TIME)
		{
			_data->machine.AddState(StateRef(new MainMenuState(_data)));
		}
	}
	void SplashState::Draw(float dt)
	{
		draw = true;
		_data->window.clear();
		_data->window.draw(_background);
		_data->window.display();
	}
}
