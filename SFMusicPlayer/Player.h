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
	void scrollText();
private:
	vector<std::string> Files;
	vector <Tile> Tiles;
	sf::RenderWindow window;
	float initialY = 100;
	sf::Font mFont;
};

