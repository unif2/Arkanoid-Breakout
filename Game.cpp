#include "Game.h"
#include <iostream>

using std::cout;
using std::endl;

Game::Game()
{
    gameOver = false;
    numLives = 3;
    startOfPlay = true;
    gameOver = false;
    initialBallVelocity = sf::Vector2f(1.f, -1.f);
}

void Game::movePaddle(sf::RenderWindow& window, sf::Event& event)
{
    sf::RectangleShape paddle = board.getPaddle().paddle;
    int windowWidth = window.getSize().x;

    if (event.type == sf::Event::KeyPressed)
    {
        if (event.key.code == sf::Keyboard::Right)
        {
            if (paddle.getPosition().x < windowWidth - 200)
            {
                board.getPaddle().paddle.move(20.f, 0.f);
                if (startOfPlay)
                {
                    board.getBall()->ball.move(20.f, 0.f);
                }
            }
        }

        else if (event.key.code == sf::Keyboard::Left)
        {
            if (paddle.getPosition().x > 0)
            {
                board.getPaddle().paddle.move(-20.f, 0.f);
                if (startOfPlay)
                {
                    board.getBall()->ball.move(-20.f, 0.f);
                }
            }
        }

        else if (startOfPlay && (event.key.code == sf::Keyboard::Enter))
        {
            board.setBallVelocity(initialBallVelocity, board.getBall());
            startOfPlay = false;
        }
    }
}

void Game::moveBall()
{
    board.getBall()->ball.move(board.getBall()->getBallVelocity());
}

void Game::ballCollision(sf::RenderWindow& window)
{
    unsigned int rows = board.getNumRows();
    float lowerBrickBoundary = rows * (54.f);
    sf::FloatRect paddleBoundary = board.getPaddle().paddle.getGlobalBounds();
    sf::FloatRect ballBoundary = board.getBall()->ball.getGlobalBounds();
    sf::CircleShape ball = board.getBall()->ball;
    sf::Vector2f currentBallVelocity = board.getBall()->getBallVelocity();
    int windowWidth = window.getSize().x;
    int windowHeight = window.getSize().y;
    vector<Brick*> bricks = board.getBoardBricks();

    if (ball.getPosition().y == 0)
    {
        board.setBallVelocity(sf::Vector2f(currentBallVelocity.x, -1.f * currentBallVelocity.y), board.getBall());
    }
    
    else if (ball.getPosition().y < rows * 54.f)
    {
        for (unsigned int i = 0; i < bricks.size(); i++)
        {
            if (!(bricks[i]->get_hit_status()) && ballBoundary.intersects(bricks[i]->get_brick_boundary()))
            {
                if ((ball.getPosition().y < (bricks[i]->get_brick_boundary().top + bricks[i]->get_brick_boundary().height)) || (ball.getPosition().y < (bricks[i]->get_brick_boundary().top - ballBoundary.height)))
                {
                    board.setBallVelocity(sf::Vector2f(currentBallVelocity.x, -1.f * currentBallVelocity.y), board.getBall());
                    bricks[i]->set_hit_status(true);
                }

                else if ((ballBoundary.left < (bricks[i]->get_brick_boundary().left + bricks[i]->get_brick_boundary().width)) || (ballBoundary.left < (bricks[i]->get_brick_boundary().left - 10)))
                {
                    board.setBallVelocity(sf::Vector2f(-1.f * currentBallVelocity.x, currentBallVelocity.y), board.getBall());
                    bricks[i]->set_hit_status(true);
                }
            }
        }
        
        //board.setBallVelocity(sf::Vector2f(currentBallVelocity.x, -1.f * currentBallVelocity.y), board.getBall());
    }

    if (ballBoundary.intersects(paddleBoundary))
    {
        ball.setPosition(ball.getPosition().x, ball.getPosition().y - 2.f);
        board.setBallVelocity(sf::Vector2f(currentBallVelocity.x, -1.f * currentBallVelocity.y), board.getBall());
    }

    //if (ballBoundary.left == 0)
    //    board.setBallVelocity(sf::Vector2f(-1.f * currentBallVelocity.x, currentBallVelocity.y), board.getBall());

    //if (ballBoundary.left == 1910)
    //    board.setBallVelocity(sf::Vector2f(-1.f * currentBallVelocity.x, currentBallVelocity.y), board.getBall());
    
    if (ball.getPosition().x == 0 || ball.getPosition().x == windowWidth - 10)
        board.setBallVelocity(sf::Vector2f(-1.f * currentBallVelocity.x, currentBallVelocity.y), board.getBall());

    if (ball.getPosition().y == 1080.f)
    {
        resetBallPaddle();
        if (numLives == 0)
        {
            gameOver = true;
        }
    }

}

void Game::playGame(sf::RenderWindow& window)
{
    while (window.isOpen())
    {
        window.clear();
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            movePaddle(window, event);
        }
        board.displayBoard(window);
        window.display();
        moveBall();
        ballCollision(window);
        if (gameOver)
            window.close();
    }
}

sf::Vector2f Game::getballvelo()
{
    return board.getBall()->getBallVelocity();
}

void Game::resetBallPaddle()
{
    sf::CircleShape ball = board.getBall()->ball;
    sf::RectangleShape paddle = board.getPaddle().paddle;

    board.getBall()->setBallPosition(sf::Vector2f(950.f, 980.f));
    board.getPaddle().setPaddlePosition(sf::Vector2f(860.f, 1000.f));
    board.setBallVelocity(sf::Vector2f(0.f, 0.f), board.getBall());
    startOfPlay = true;
    numLives--;
}