#pragma once
#include "Game.h"
#include "joueur.h"
#include "State.h"
namespace MB
{
	class GameOverState : public State
	{
	public:
		GameOverState(GameDataRef data, joueur& j1, joueur& j2);
		void HandleInput();
		void Update(float dt);
		void loadnextstate()
		{

		}
		void Draw(float dt);
		void init();

	private:

		GameDataRef _data;
		sf::Sprite _background1, _background2;
		joueur* j1, * j2;
		sf::Clock clock;
	};


}