#pragma once

#include "IInput.h"
#include "SFML/Window.hpp"

using Key = InputCodes::Key;

class SFMLInput
{
public:
	bool KeyPressed(Key key) { return sf::Keyboard::isKeyPressed(sf::Keyboard::Key(key)); }
};