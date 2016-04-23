#pragma once

#include<iostream>
#include<SFML\Window.hpp>
#include<SFML\Audio.hpp>
#include<SFML\Graphics.hpp>
#include<SFML\System.hpp>
#include<boost\filesystem.hpp>
#include<boost\foreach.hpp>
#include "Tile.h"
using namespace std;

class Player
{
public:
	Player();
	~Player();

	void LoadFiles(vector<string> &FileNames);
	void createList();
	void Start();
	void scrollTiles(bool Up); // If Up is true move move tiles up, ifnot move down
	void createHeader();
	void drawObjects(sf::Event &event);
	void inputChecks(sf::Event &event, sf::RenderWindow &window);
private:
	vector<std::string> Files;
	vector <Tile> Tiles;
	sf::RenderWindow window;
	float initialY = 100;
	sf::Font mFont;
	sf::Music currentSong;
	sf::RectangleShape infoBox;
	sf::CircleShape playButton;
	sf::Texture playTexture;
	sf::Texture pauseTexture;
	sf::RectangleShape volumeBar;
	sf::CircleShape volumeSlider;
	sf::ContextSettings settings;
	int nextSong;
};

