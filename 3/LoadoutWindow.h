#ifndef LOADOUT
#define LOADOUT
#include <SFML/Graphics.hpp>
#include "Button.hpp"
#include "TextField.hpp"
#include "game_headers/Table.hpp"
#include "game_headers/Mission.hpp"
const int LOADOUT_WIDTH = 800;
const int LOADOUT_HEIGHT = 800;
void runLoadoutSetup(sf::RenderWindow&, zasada::Mission&);

#endif