#include "Player.h"

Player::Player() : window(sf::VideoMode(300, 500), "SFMusic Player", sf::Style::Close, settings)
{
	//Load our font
	if (!mFont.loadFromFile("Mido.otf"))
		cout << "Failed loading font!" << endl;

	//settings.antialiasingLevel = 8;
}

Player::~Player()
{
}

//Load song names into a container

void Player::LoadFiles(vector<string> &FileNames)
{
	boost::filesystem::path directory("C:/Users/Tyree/Music");
	boost::filesystem::directory_iterator iter(directory), eod;

	BOOST_FOREACH(boost::filesystem::path const &p, make_pair(iter, eod))
	{
		if (p.extension() == ".ogg") //If the file is an oggt file load it
			FileNames.push_back(p.filename().string());
	}
}

//Create the list of songs, tiles, and main visuals in the application
void Player::createList()
{
	for (auto i = Files.begin(); i != Files.end(); ++i)
	{
		Tile newTile;
		newTile.songID = (*i); //Assign each tiles its own songID from the container of file names

		//Setup the Tile, text, and back shadow
		newTile.rect.setSize(sf::Vector2f(280, 50));
		newTile.rect.setPosition(1, initialY);
		newTile.Label.setPosition(newTile.rect.getPosition().x, (newTile.rect.getPosition().y) / (3));
		newTile.setFont(mFont);
		newTile.setText(*i);
		newTile.updateTextPosition();
		newTile.Label.setCharacterSize(10);
		newTile.Label.setColor(sf::Color::Black);
		newTile.backgroundRect.setSize(sf::Vector2f(282, 52));
		newTile.backgroundRect.setFillColor(sf::Color(0, 0, 0, 50));
		newTile.bBox.height = newTile.rect.getSize().y;
		newTile.bBox.width = newTile.rect.getSize().x;

		initialY += 75; //Spacing of 75 between this tile and the next in the Y direction

		Tiles.push_back(newTile);
	}
}

void Player::Start()
{
	//Load all strings into a vector
	LoadFiles(Files);

	//Debug output all file names
	for (auto i = Files.begin(); i != Files.end(); ++i)
		cout << "Song: " << *i << endl;

	//Create all of the tiles
	createList();

	//Create other elements(e.g. PlayPause button, volume slider, etc.)
	createHeader();


	//Set the max framerate of the application to 60 and enable V-Sync
	window.setFramerateLimit(60);
	window.setVerticalSyncEnabled(true);

	while (window.isOpen())
	{
		sf::Event event;

		while (window.pollEvent(event))
		inputChecks(event, window); //Checking for inputs on Header(Volume slider, play button, etc) elements, and scrolling



		window.clear(sf::Color::White);

		//Draw all of our objects
		drawObjects(event);

		window.display();

		//Music business
		for (unsigned int i = 0; i < Tiles.size(); i++)
		{
			if (Tiles[i].Play == true && Tiles[i].isPlaying == false) //If the tile has been clicked and therefore is set to play, but it is not yet playing
			{
				
				for (unsigned int i = 0; i < Tiles.size(); i++)
				{
					Tiles[i].isPlaying = false;
					//(*i).Play = false;
				}
				cout << "Playing: " << Tiles[i].songID << endl;

				Tiles[i].isPlaying = true; //Basically a debounce, song won't restart again when clicked a second time, only until another song is playing

				//If we can, find the next song after this one, so that way it will loop through all songs in the Tile list
				if(i < Tiles.size())
				nextSong = i+1;

				//Try and load the file, if not spit out error
				if (!currentSong.openFromFile("C:/Users/Tyree/Music/" + Tiles[i].songID))
					cout << "Could not load music" << endl;

				//Finally play the song
				currentSong.play();

				//The button is already playing now, so play is set back to false
				Tiles[i].Play = false;
			}
			
			//Move to the next song if the current song is finished
			if (currentSong.getStatus() == currentSong.Stopped)
			{
				for (unsigned int i = 0; i < Tiles.size(); i++)
				{
					Tiles[i].isPlaying = false;
					//(*i).Play = false;
				}
				cout << "Going to next song" << endl;
				Tiles[nextSong].Play = true;
			}
			
		}

	}
}

//Main scrolling action
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

//Create all of the header elements
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

//Draw all of our elements
void Player::drawObjects(sf::Event &event)
{
	for (unsigned int i = 0; i < Tiles.size(); i++)
	{
		window.draw(Tiles[i].backgroundRect);
		window.draw(Tiles[i].rect);
		window.draw(Tiles[i].Label);
		Tiles[i].Update(window, event);
	}
	window.draw(infoBox);
	window.draw(volumeBar);
	window.draw(volumeSlider);
}

//Input checking of scrolling and header elements
void Player::inputChecks(sf::Event & event, sf::RenderWindow &window)
{

	int mouseX;
	int mouseY;

		if (event.type == sf::Event::Closed)
			window.close();
		else if (event.type == sf::Event::MouseWheelScrolled)
		{
			if (event.mouseWheelScroll.delta > 0) //Scrolling up
			{
				scrollTiles(true);

			}
			else if (event.mouseWheelScroll.delta < 0) //Scrolling down
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
				else if (mouseX >= volumeBar.getPosition().x && mouseX <= (volumeBar.getPosition().x + volumeBar.getSize().x))
				{
					volumeSlider.setPosition(mouseX, volumeBar.getPosition().y);
					currentSong.setVolume((volumeSlider.getPosition().x) - volumeBar.getPosition().x);
				}

			}

		}

	}


