#include "Game.h"

int main()
{
    Game game;
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Arkanoid!");
    game.playGame(window);
    return 0;
}