#pragma once
#include <iostream>
#include<SFML\Graphics.hpp>

using namespace std;

class Tile
{
public:
	Tile();
	void setText(string &text);
	void updateTextPosition();
	void setFont(sf::Font &needFont);;
	enum state {HOVERED, NORMAL};
	void Update(sf::RenderWindow &wnd, sf::Event &e);
	sf::RectangleShape rect;
	sf::RectangleShape backgroundRect;
	sf::FloatRect bBox;
	string songID;
	sf::Text Label;
	bool inView;
	bool playMusic;
private:
	state mButtonStates;

};
