#pragma once
#include <iostream>
#include<SFML\Graphics.hpp>

using namespace std;

class Tile
{
public:
	void setText(string &text);
	void updateTextPosition();
	void setFont(sf::Font &needFont);
	bool mouseIntersects(sf::Vector2f position, sf::Vector2f size, sf::RenderWindow &wnd);
	sf::RectangleShape rect;
	sf::RectangleShape backgroundRect;
	sf::FloatRect bBox;
	string songID;
	sf::Text Label;

};
