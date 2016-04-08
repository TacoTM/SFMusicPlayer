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
	sf::RectangleShape rect;
	sf::RectangleShape backgroundRect;
	string songID;
	sf::Text Label;

};
