#include "Player.h"

Player::Player() : window(sf::VideoMode(300,500), "SFMusic Player", sf::Style::Close, settings)
{
	if (!mFont.loadFromFile("Track.ttf"))
		cout << "Failed loading font!" << endl;
	settings.antialiasingLevel = 8;
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
		if (p.extension() == ".ogg")
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
		initialY += 50;
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
	createHeader();

	int mouseX;
	int mouseY;

	window.setFramerateLimit(60);
	window.setVerticalSyncEnabled(true);
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			else if (event.type == sf::Event::MouseWheelScrolled)
			{
				if (event.mouseWheelScroll.delta > 0)
				{
					scrollTiles(true);

				}
				else if (event.mouseWheelScroll.delta < 0)
				{
					scrollTiles(false);

				}
			}
			else if (event.type == sf::Event::MouseButtonPressed)
			{
			
				mouseX = sf::Mouse::getPosition(window).x;
				mouseY = sf::Mouse::getPosition(window).y;
				if (volumeBar.getGlobalBounds().contains(mouseX, mouseY))
				{

						if (mouseX > (volumeBar.getPosition().x + volumeBar.getSize().x))
						{
							volumeSlider.setPosition(volumeBar.getPosition().x + 100, volumeBar.getPosition().y);
							currentSong.setVolume(100);
						}
						else if (mouseX < volumeBar.getPosition().x)
						{
							volumeSlider.setPosition(volumeBar.getPosition().x, volumeBar.getPosition().y);
							currentSong.setVolume(0);
						}
						else if (mouseX > volumeBar.getPosition().x && mouseX < (volumeBar.getPosition().x + volumeBar.getSize().x))
						{
							volumeSlider.setPosition(mouseX, volumeBar.getPosition().y);
							currentSong.setVolume((volumeSlider.getPosition().x) - volumeBar.getPosition().x);
						}
					
				}
			
		}

		}



		window.clear(sf::Color::White);
		//draw
		for (auto i = Tiles.begin(); i != Tiles.end(); ++i)
		{
			window.draw((*i).backgroundRect);
			window.draw((*i).rect);
			window.draw((*i).Label);
			(*i).Update(window, event);
			if ((*i).Play == true && (*i).isPlaying == false)
			{
				for (auto i = Tiles.begin(); i != Tiles.end(); ++i)
				{
					(*i).isPlaying = false;
					//(*i).Play = false;
				}
				(*i).isPlaying = true;
				if (!currentSong.openFromFile("C:/Users/Tyree/Music/" + (*i).songID))
					cout << "Could not load music" << endl;
				currentSong.play();
				(*i).Play = false;
			}
		}
		window.draw(infoBox);
		window.draw(volumeBar);
		window.draw(volumeSlider);
		
		window.display();

	}
}

void Player::scrollTiles(bool Up)
{
	if (Up == true)
	{
		cout << "Moving tiles up" << endl;
		if (Tiles[0].rect.getPosition().y < 100)
		{
			for (auto i = Tiles.begin(); i != Tiles.end(); ++i)
			{
				(*i).setPosition((*i).rect.getPosition().x, (*i).rect.getPosition().y + 50);
			}
		}

	}
	else if (Up == false)
	{
		cout << "Moving tiles down" << endl;
		if (Tiles.back().rect.getPosition().y >= 100)
		{
			for (auto i = Tiles.begin(); i != Tiles.end(); ++i)
			{
				(*i).setPosition((*i).rect.getPosition().x, (*i).rect.getPosition().y - 50);
			}
		}
	}
}

void Player::createHeader()
{
	infoBox.setSize(sf::Vector2f(300, 100));
	infoBox.setFillColor(sf::Color::Black);

	volumeBar.setSize(sf::Vector2f(100, 5));
	volumeBar.setPosition(50, 10);
	volumeBar.setFillColor(sf::Color::White);

	volumeSlider.setRadius(10);
	volumeSlider.setOrigin(volumeSlider.getPosition().x + 8, volumeSlider.getPosition().y + 8);
	volumeSlider.setPosition(volumeBar.getPosition().x + 100, 10);
	volumeSlider.setFillColor(sf::Color::White);

	playButton.setPosition((infoBox.getPosition().x) / 2, (infoBox.getPosition().y) / 2);
	playButton.setFillColor(sf::Color::White);
	
}


