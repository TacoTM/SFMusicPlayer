#include "Tile.h"




Tile::Tile()
{
	mButtonStates = state::NORMAL;
}

void Tile::setText(string & text)
{
	this->Label.setString(text);
}

//Only will be called on app loading
void Tile::updateTextPosition()
{
	Label.setPosition(rect.getPosition().x + 10, (rect.getPosition().y) + (rect.getSize().y)/(3));
	backgroundRect.setPosition(rect.getPosition());
}

void Tile::setFont(sf::Font &needFont)
{
	this->Label.setFont(needFont);
}

void Tile::setPosition(float x, float y)
{
	rect.setPosition(x, y);
	Label.setPosition(rect.getPosition().x + 10, (rect.getPosition().y) + (rect.getSize().y) / (3));
	backgroundRect.setPosition(rect.getPosition());
}


void Tile::Update(sf::RenderWindow & wnd, sf::Event &e)
{
	sf::Vector2i m_mousePosition = sf::Mouse::getPosition(wnd);

	if (rect.getPosition().y < 100)
		active = false;
	else
		active = true;

	int mouseX = sf::Mouse::getPosition(wnd).x;
	int mouseY = sf::Mouse::getPosition(wnd).y;

	bool mouseInButton = rect.getGlobalBounds().contains(mouseX, mouseY);

		/*(mouseX > rect.getPosition().x && mouseY > rect.getPosition().y &&
		mouseX < (rect.getPosition().x + rect.getSize().x) &&
		mouseY < (rect.getPosition().y + rect.getSize().y));
		*/

	if (e.type == sf::Event::MouseMoved)
		if (mouseInButton)
			mButtonStates = state::HOVERED;
		else
			mButtonStates = state::NORMAL;
	if (e.type == sf::Event::MouseButtonPressed)
		if(active == true)
		if (mButtonStates == HOVERED)
			Play = true;
}
