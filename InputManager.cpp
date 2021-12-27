#include "InputManager.h"

namespace MB
{
	bool InputManager::isSpriteClicked(sf::Sprite& sprite, sf::Mouse::Button mbutton, sf::RenderWindow& window)
	{
		if (sf::Mouse::isButtonPressed(mbutton))
		{
			sf::IntRect temprect(sprite.getPosition().x, sprite.getPosition().y, sprite.getGlobalBounds().width, sprite.getGlobalBounds().height);
			if (temprect.contains(sf::Mouse::getPosition(window)))
			{
				return true;
			}
		}
		return false;
	}

	sf::Vector2i InputManager::MousePosition(sf::RenderWindow& window)
	{
		return sf::Mouse::getPosition(window);
	}
}
