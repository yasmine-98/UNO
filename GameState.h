#pragma once
#include "Game.h"
#include "joueur.h"
#include "State.h"
namespace MB
{
	class GameState : public State
	{
	public:
		GameState(GameDataRef data);
		void HandleInput();
		void Update(float dt);
		void loadnextstate()
		{

		}
		void Draw(float dt);
		void init();

	private:

		GameDataRef _data;
		sf::Clock clock, clockuno;
		sf::Sprite _background, changement_de_couleur, vert, bleu, jaune, rouge, verif_uno;
		string coul = "noir";
		UNO* u;
		joueur* j1, * j2;
		bool jeter = false;
		bool piocher = false;
		bool t = true, t1 = false, t2 = false, debut = true, bloquee = false, animation = false, uno = false;
		int pos, pcarte;
		float dx, dy, dxx;
	};
}