#pragma once
#include <iostream>
#include<SFML\Graphics.hpp>
#include<SFML\Audio.hpp>
using namespace std;

class Tile
{
public:
	Tile();
	void setText(string &text);
	void updateTextPosition();
	void setFont(sf::Font &needFont);
	void setPosition(float x, float y);
	enum state {HOVERED, NORMAL};
	void Update(sf::RenderWindow &wnd, sf::Event &e);
	sf::RectangleShape rect;
	sf::RectangleShape backgroundRect;
	sf::FloatRect bBox;
	string songID;
	sf::Text Label;
	bool inView;
	bool Play;
	bool isPlaying;
	bool active;
	bool finished;
private:
	state mButtonStates;

};
