#include "Board.h"

Board::Board()
{
	numRows = 0;
	numColumns = 20;
	numBricks = 0;
	this->setLevel(1);
	loadBoard();
	ball = new Ball;
	Paddle paddle;
	
}

Board::Ball::Ball()
{
	inPlay = true;
	ball.setFillColor(sf::Color::Red);
	ball.setRadius(10.f);
	ballVelocity.x = 0.f;
	ballVelocity.y = 0.f;
	ball.setPosition(sf::Vector2f(950.f, 980.f));
}

Board::Ball* Board::getBall()
{
	return ball;
}

Board::Paddle& Board::getPaddle()
{
	return paddle;
}

Board::Paddle::Paddle()
{
	paddle.setSize(sf::Vector2f(200.f, 10.f));
	paddle.setFillColor(sf::Color::Green);
	paddleVelocity.x = 0.f;
	paddleVelocity.y = 0.f;
	paddle.setPosition(sf::Vector2f(860.f, 1000.f));
}

void Board::Paddle::setPaddlePosition(sf::Vector2f paddlePosition)
{
	paddle.setPosition(paddlePosition);
}

sf::Vector2f Board::Paddle::getPaddleVelocity()
{
	return paddleVelocity;
}

void Board::Ball::setBallPosition(sf::Vector2f ballPosition)
{
	ball.setPosition(ballPosition);
}

sf::Vector2f Board::Ball::getBallVelocity()
{
	return ballVelocity;
}

void Board::displayBoard(sf::RenderWindow& window)
{
	for (unsigned int i = 0; i < boardBricks.size(); i++)
	{
		boardBricks[i]->displayBrick(window);
	}

	window.draw(getPaddle().paddle);
	window.draw(getBall()->ball);
}

void Board::loadBoard()
{
	ifstream inputFile("boards/board" + std::to_string(boardLevel) + ".brd");
	if (inputFile.is_open())
	{
		string line;
		while (getline(inputFile, line))
		{
			numRows++;

			for (unsigned int i = 0; i < 20; i++)
			{
				short val = line[i] - '0';
				if (val == 1)
				{
					numBricks++;
					brickPositions.push_back(sf::Vector2f(2.f + i * (91.9 + 4.f), 2.f + (numRows - 1) * (50.f + 4.f)));
				}
			}
		}
	}

	for (unsigned int i = 0; i < brickPositions.size(); i++)
	{
		Brick* brick = new Brick(sf::Color::Green, sf::Color::Magenta);
		brick->set_brick_position(brickPositions[i]);
		boardBricks.push_back(brick);
		cout << "Brick position: " << brick->get_brick_position().x << " and " << brick->get_brick_position().y << endl;
	}
}

void Board::setLevel(unsigned int level)
{
	boardLevel = level;
}

unsigned int Board::getLevel()
{
	return boardLevel;
}

void Board::setBallVelocity(sf::Vector2f velocity, Board::Ball* ball)
{
	ball->ballVelocity = velocity;
}

unsigned int Board::getNumRows()
{
	return numRows;
}

vector<Brick*> Board::getBoardBricks()
{
	return boardBricks;
}