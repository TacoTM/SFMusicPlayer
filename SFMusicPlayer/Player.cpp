#include "Player.h"

Player::Player()
{
	//Load our font
	if (!mFont.loadFromFile("Mido.otf"))
		cout << "Failed loading font!" << endl;

	if (!playTexture.loadFromFile("play.png"))
		cout << "Can not load play button texture" << endl;

	if (!pauseTexture.loadFromFile("pause.png"))
		cout << "Can not load pause button texture" << endl;

	playTexture.setSmooth(true);
	pauseTexture.setSmooth(true);
	currentSong.setVolume(50);
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
		newTile.rect.setSize(sf::Vector2f(300, 50));
		newTile.rect.setPosition(1, initialY);
		newTile.rect.setFillColor(sf::Color::White);
		newTile.Label.setPosition(newTile.rect.getPosition().x, (newTile.rect.getPosition().y) / (3));
		newTile.setFont(mFont);
		newTile.setText(*i);
		newTile.updateTextPosition();
		newTile.Label.setCharacterSize(10);
		newTile.Label.setColor(sf::Color::Black);
		newTile.backgroundRect.setSize(sf::Vector2f(300, 52));
		newTile.backgroundRect.setFillColor(sf::Color(33, 150, 243));
		newTile.bBox.height = newTile.rect.getSize().y;
		newTile.bBox.width = newTile.rect.getSize().x;

		initialY += 52; //Spacing of 52 between this tile and the next in the Y direction

		Tiles.push_back(newTile);
	}
}

void Player::Start(sf::RenderWindow &window)
{
	
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
	infoBox.setFillColor(sf::Color(33, 150, 243));

	volumeBar.setSize(sf::Vector2f(100, 5));
	volumeBar.setOrigin(50, 2.5);
	volumeBar.setPosition(150, 20);
	volumeBar.setFillColor(sf::Color::White);

	volumberBarBG.setSize(sf::Vector2f(102, 7));
	volumberBarBG.setOrigin(51, 3.5);
	volumberBarBG.setPosition(150, 20);
	volumberBarBG.setFillColor(sf::Color(0, 0, 0, 70));

	volumeSlider.setRadius(10);
	volumeSlider.setOrigin(10, 10);
	volumeSlider.setPosition(volumeBar.getPosition().x + 50, 20);
	volumeSlider.setFillColor(sf::Color(255, 235, 59));

	volumeSliderBG.setRadius(11);
	volumeSliderBG.setOrigin(11, 11);
	volumeSliderBG.setPosition(volumeSlider.getPosition());
	volumeSliderBG.setFillColor(sf::Color(0, 0, 0, 70));

	playButton.setRadius(20);
	playButton.setOrigin(20, 20);
	playButton.setPosition((infoBox.getSize().x) / 2, (infoBox.getSize().y) / 2);
	playButton.setFillColor(sf::Color::White);

	playButtonBG.setRadius(21);
	playButtonBG.setOrigin(21, 21);
	playButtonBG.setPosition((infoBox.getSize().x) / 2, (infoBox.getSize().y) / 2);
	playButtonBG.setFillColor(sf::Color(0, 0, 0, 70));

	divider.setSize(sf::Vector2f(300, 2));
	divider.setFillColor(sf::Color(13, 71, 161));
	divider.setPosition(0, 100);
}

//Draw all of our elements
void Player::drawObjects(sf::Event &event, sf::RenderWindow &window)
{
	for (unsigned int i = 0; i < Tiles.size(); i++)
	{
		window.draw(Tiles[i].backgroundRect);
		window.draw(Tiles[i].rect);
		window.draw(Tiles[i].Label);
		Tiles[i].Update(window, event);
	}
	window.draw(infoBox);

	window.draw(divider);

	window.draw(volumberBarBG);
	window.draw(volumeBar);

	window.draw(volumeSliderBG);
	window.draw(volumeSlider);

	window.draw(playButtonBG);
	window.draw(playButton);
	window.draw(overlapPlay);
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
				volumeSlider.setPosition(mouseX, 20);
				volumeSliderBG.setPosition(volumeSlider.getPosition());
				currentSong.setVolume((volumeSlider.getPosition().x) - (volumeBar.getPosition().x - 50));
			}
			if (playButton.getGlobalBounds().contains(mouseX, mouseY))
			{
				if (currentSong.getStatus() == currentSong.Playing)
				{
					playButton.setTexture(&playTexture);
					playButton.setTextureRect(sf::IntRect(-50, 0, 900, 900));
					currentSong.pause();
				}
				else
				{
					playButton.setTexture(&pauseTexture);
					playButton.setTextureRect(sf::IntRect(0, 0, 900, 900));
					currentSong.play();
				}
			}

		}

	}


