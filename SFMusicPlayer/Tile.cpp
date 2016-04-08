#include "Tile.h"




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

bool Tile::mouseIntersects(sf::Vector2f position, sf::Vector2f size, sf::RenderWindow  &wnd)
{
	if (sf::Mouse::getPosition(wnd).x >= position.x && sf::Mouse::getPosition(wnd).x <= size.x
		&& sf::Mouse::getPosition(wnd).y >= position.y && sf::Mouse::getPosition(wnd).y <= size.y)
	{
		return true;
	}
	return false;
}
