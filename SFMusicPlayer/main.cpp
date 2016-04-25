#include <SFML/Graphics.hpp>
#include "Player.h"
int main()
{
	
	
	Player app;
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	sf::RenderWindow window(sf::VideoMode(300, 500), "SFMusic Player", sf::Style::Close, settings);

	//Load all strings into a vector
	app.LoadFiles(app.Files);

	//Debug output all file names
	for (auto i = app.Files.begin(); i != app.Files.end(); ++i)
		cout << "Song: " << *i << endl;

	//Create all of the tiles
	app.createList();

	//Create other elements(e.g. PlayPause button, volume slider, etc.)
	app.createHeader();


	//Set the max framerate of the application to 60 and enable V-Sync
	window.setFramerateLimit(60);
	window.setVerticalSyncEnabled(true);

	while (window.isOpen())
	{
		sf::Event event;

		while (window.pollEvent(event))
			app.inputChecks(event, window); //Checking for inputs on Header(Volume slider, play button, etc) elements, and scrolling



		window.clear(sf::Color(25, 118, 210));

		//Draw all of our objects
		app.drawObjects(event, window);

		window.display();

		//Music business
		for (unsigned int i = 0; i < app.Tiles.size(); i++)
		{
			if (app.Tiles[i].Play == true && app.Tiles[i].isPlaying == false) //If the tile has been clicked and therefore is set to play, but it is not yet playing
			{

				for (unsigned int i = 0; i < app.Tiles.size(); i++)
				{
					app.Tiles[i].isPlaying = false;
					//(*i).Play = false;
				}
				cout << "Playing: " << app.Tiles[i].songID << endl;

				app.Tiles[i].isPlaying = true; //Basically a debounce, song won't restart again when clicked a second time, only until another song is playing

										   //If we can, find the next song after this one, so that way it will loop through all songs in the Tile list
				if (i < app.Tiles.size())
					app.nextSong = i + 1;

				//Try and load the file, if not spit out error
				if (!app.currentSong.openFromFile("C:/Users/Tyree/Music/" + app.Tiles[i].songID))
					cout << "Could not load music" << endl;

				//Finally play the song
				app.currentSong.play();

				//The button is already playing now, so play is set back to false
				app.Tiles[i].Play = false;
			}

			//Move to the next song if the current song is finished
			if (app.currentSong.getStatus() == app.currentSong.Stopped)
			{
				for (unsigned int i = 0; i < app.Tiles.size(); i++)
				{
					app.Tiles[i].isPlaying = false;
					//(*i).Play = false;
				}
				cout << "Going to next song" << endl;
				app.Tiles[app.nextSong].Play = true;
			}

		}

	}
	return 0;
}
