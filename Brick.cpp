#include "Brick.h"

Brick::Brick(sf::Color color, sf::Color outline_color)
{
	brick.setSize(brick_size);
	brickColor = color;
	outlineColor = outline_color;
	is_hit = false;
	brick.setFillColor(brickColor);
	brick.setOutlineColor(outlineColor);
	brick.setOutlineThickness(outline_thickness);
}

void Brick::set_brick_color(sf::Color color)
{
	brickColor = color;
	brick.setFillColor(brickColor);
}

void Brick::set_outline_color(sf::Color outline_color)
{
	outlineColor = outline_color;
	brick.setOutlineColor(outlineColor);
}

void Brick::set_brick_position(sf::Vector2f position)
{
	brickPosition = position;
	brick.setPosition(brickPosition);
}

void Brick::set_hit_status(bool hit_status)
{
	is_hit = hit_status;
}

sf::Vector2f Brick::get_brick_size()
{
	return brick_size;
}

sf::Color Brick::get_brick_color()
{
	return brickColor;
}

sf::Color Brick::get_outline_color()
{
	return outlineColor;
}

float Brick::get_outline_thickness()
{
	return outline_thickness;
}

sf::Vector2f Brick::get_brick_position()
{
	return brick.getPosition();
}

bool Brick::get_hit_status()
{
	return is_hit;
}

void Brick::displayBrick(sf::RenderWindow& window)
{
	if (!is_hit)
		window.draw(brick);
}

sf::FloatRect Brick::get_brick_boundary()
{
	return brick.getGlobalBounds();
}