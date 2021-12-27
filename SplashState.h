#pragma once
#include "Game.h"
#include "State.h"
namespace MB
{
	class SplashState : public State
	{
	public:
		SplashState(GameDataRef data);
		~SplashState();
		void HandleInput();
		void Update(float dt);
		void loadnextstate()
		{

		}
		void Draw(float dt);
		void init();

	private:

		GameDataRef _data;
		sf::Sprite _background;
		sf::Clock _clock;
		bool draw = false;
	};


}