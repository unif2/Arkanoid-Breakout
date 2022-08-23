#pragma once
#include <SFML/Graphics.hpp>
const sf::Vector2f brick_size(91.9, 50.f);
const float outline_thickness = 2.f;

class Brick
{
private:
	sf::RectangleShape brick;
	sf::Color brickColor;
	sf::Color outlineColor;
	sf::Vector2f brickPosition;
	bool is_hit;

public:
	void set_brick_color(sf::Color color);
	void set_outline_color(sf::Color outline_color);
	void set_brick_position(sf::Vector2f position);
	void set_hit_status(bool hit_status);
	Brick(sf::Color color, sf::Color outline_color);
	sf::Vector2f get_brick_size();
	sf::Color get_brick_color();
	sf::Color get_outline_color();
	float get_outline_thickness();
	sf::Vector2f get_brick_position();
	bool get_hit_status();
	void displayBrick(sf::RenderWindow& window);
	sf::FloatRect get_brick_boundary();
};