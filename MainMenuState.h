#pragma once
#include "State.h"
#include "Game.h"
#include "Definitions.h"
namespace MB
{
	class MainMenuState : public State
	{
	public:
		MainMenuState(GameDataRef data);
		void HandleInput();
		void Update(float dt);
		void loadnextstate();
		void Draw(float dt);
		void init();
	private:
		sf::Sprite _PlayButton, _PlayButton2;
		sf::Sprite _QuitButton, _QuitButton2;
		sf::Sprite _Background;
		GameDataRef _data;
		bool pressed_play = false, released_play = false, pressed_quit = false, released_quit = false;
	};

}
