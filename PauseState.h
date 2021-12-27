#pragma once
#include "Game.h"
#include "State.h"
namespace MB
{
	class PauseState : public State
	{
	public:
		PauseState(GameDataRef data);
		void HandleInput();
		void Update(float dt);
		void loadnextstate()
		{

		}
		void Draw(float dt);
		void init();

	private:

		GameDataRef _data;
		sf::Sprite Pause_background;


	};


}
