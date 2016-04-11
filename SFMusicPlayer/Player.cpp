#include "Player.h"

Player::Player() : window(sf::VideoMode(300,500), "SFMusic Player", sf::Style::Close)
{
	if (!mFont.loadFromFile("Track.ttf"))
		cout << "Failed loading font!" << endl;
}

Player::~Player()
{
}

//Load song names and assign the music tiles an ID to reference the string

void Player::LoadFiles(vector<string> &FileNames)
{
	boost::filesystem::path directory("C:/Users/Tyree/Music");
	boost::filesystem::directory_iterator iter(directory), eod;

	BOOST_FOREACH (boost::filesystem::path const &p, make_pair(iter, eod))
	{
		if (p.extension() == ".mp3")
			FileNames.push_back(p.filename().string());
	}
}

void Player::createList()
{
	for (auto i = Files.begin(); i != Files.end(); ++i)
	{
		Tile newTile;
		newTile.songID = (*i);
		newTile.rect.setSize(sf::Vector2f(298, 50));
		newTile.rect.setPosition(1, initialY);
		newTile.Label.setPosition(newTile.rect.getPosition().x, (newTile.rect.getPosition().y) / (3));
		newTile.setFont(mFont);
		newTile.setText(*i);
		newTile.updateTextPosition();
		newTile.Label.setCharacterSize(10);
		newTile.Label.setColor(sf::Color::Black);
		newTile.rect.setOutlineColor(sf::Color::Black);
		newTile.rect.setOutlineThickness(1);
		newTile.backgroundRect.setSize(sf::Vector2f(270, 60));
		newTile.backgroundRect.setFillColor(sf::Color(0, 0, 0, 50));
		newTile.bBox.height = newTile.rect.getSize().y;
		newTile.bBox.width = newTile.rect.getSize().x;
		initialY += 80;
		Tiles.push_back(newTile);
	}
}

void Player::Start()
{
	//Load all strings into a vector
	LoadFiles(Files);

	//Debug
	for (auto i = Files.begin(); i != Files.end(); ++i)
		cout << "Song: " << *i << endl;
	
	createList();
	

	window.setFramerateLimit(60);
	window.setVerticalSyncEnabled(true);
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

		}



		window.clear(sf::Color::White);
		//draw
		for (auto i = Tiles.begin(); i != Tiles.end(); ++i)
		{
			window.draw((*i).backgroundRect);
			window.draw((*i).rect);
			window.draw((*i).Label);
			(*i).Update(window, event);
		}
		window.display();

	}
}


