#pragma once
#include "Board.h"

class Game
{
private:
	bool gameOver;
	unsigned int numLives;
	bool startOfPlay;
	Board board;
	sf::Vector2f initialBallVelocity;

public:
	Game();
	void movePaddle(sf::RenderWindow& window, sf::Event& event);
	void moveBall();
	void ballCollision(sf::RenderWindow& window);
	void playGame(sf::RenderWindow& window);
	sf::Vector2f getballvelo();
	void resetBallPaddle();
};
