#pragma once
#include <memory>
#include <SFML\Graphics.hpp>
#include "StateMachine.h"
#include "InputManager.h"
#include "AssetManager.h"

namespace MB
{
	struct GameData
	{
		StateMachine machine;
		sf::RenderWindow window;
		AssetManager assets;
		InputManager input;
	};
	typedef std::shared_ptr<GameData> GameDataRef;
	class Game
	{
	public:
		Game(int width, int height, std::string title);

	private:
		const float dt = 1.0f / 6.0f;
		sf::Clock _clock;
		GameDataRef _data = std::make_shared<GameData>();
		void run();

	};
}
