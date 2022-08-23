#pragma once
#include "Brick.h"
#include <vector>
#include <fstream>
#include <string>
#include <iostream>

using std::vector;
using std::ifstream;
using std::string;
using std::cout;
using std::endl;

class Board
{
	struct Ball
	{
		sf::CircleShape ball;
		bool inPlay;
		sf::Vector2f ballVelocity;
		sf::Vector2f ball_size;
		Ball();
		void setBallPosition(sf::Vector2f ballPosition);
		sf::Vector2f getBallVelocity();
	};

	struct Paddle
	{
		sf::RectangleShape paddle;
		sf::Vector2f paddleVelocity;
		Paddle();
		void setPaddlePosition(sf::Vector2f paddlePosition);
		sf::Vector2f getPaddleVelocity();
	};
	
private:
	Ball* ball;
	Paddle paddle;
	vector<Brick*> boardBricks;
	vector<sf::Vector2f> brickPositions;
	unsigned int numRows;
	unsigned int numColumns;
	unsigned int numBricks;
	unsigned int boardLevel;
	
public:
	Board();
	Paddle& getPaddle();
	Ball* getBall();
	void displayBoard(sf::RenderWindow& window);
	void loadBoard();
	void setLevel(unsigned int level);
	unsigned int getLevel();
	void setBallVelocity(sf::Vector2f velocity, Board::Ball* ball);
	unsigned int getNumRows();
	vector<Brick*> getBoardBricks();
};
