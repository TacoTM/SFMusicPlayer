#include "Tile.h"




Tile::Tile()
{
	mButtonStates = state::NORMAL;
}

void Tile::setText(string & text)
{
	this->Label.setString(text);
}

//Only will be called on app loading, and when scrolling is initiated
void Tile::updateTextPosition()
{
	this->Label.setPosition(this->rect.getPosition().x + 10, (this->rect.getPosition().y) + (this->rect.getSize().y)/(3));
	this->backgroundRect.setPosition(this->rect.getPosition());
}

void Tile::setFont(sf::Font &needFont)
{
	this->Label.setFont(needFont);
}


void Tile::Update(sf::RenderWindow & wnd, sf::Event &e)
{
	sf::Vector2i m_mousePosition = sf::Mouse::getPosition(wnd);

	

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

	//Mouse Event debug
	if (mButtonStates == HOVERED)
		cout << "Button is being hovered on: " << songID << endl;
}
