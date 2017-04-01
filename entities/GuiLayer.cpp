#include "GuiLayer.hpp"
#include <iostream>
void GuiLayer::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (int i = 0; i < drawableElements.size(); i++)
	{
		target.draw(*drawableElements[i], states);
	}
}
GuiLayer::GuiLayer()
{
	position.x = 0;
	position.y = 0;
}
GuiLayer::GuiLayer(float x, float y)
{
	position.x = x;
	position.y = y;
}
sf::Vector2f GuiLayer::getPosition()
{
	return position;
}
void GuiLayer::setLayerPosition(float x, float y)
{
	position.x = x;
	position.y = y;
}
void GuiLayer::setLayerPosition(const sf::Vector2f &position)
{
	this->position = position;
}
void GuiLayer::setPosition(float x, float y)
{
	sf::Vector2f entityPosition;
	sf::Vector2f oldPosition = this->getPosition();
	this->setLayerPosition(x, y);

	for (int i = 0; i < transformableElements.size(); i++)
	{
		entityPosition = transformableElements[i]->getPosition();
		transformableElements[i]->setPosition(x - (oldPosition.x - entityPosition.x), y - (oldPosition.y - entityPosition.y));
	}
}
void GuiLayer::setPosition(const sf::Vector2f &position)
{
	sf::Vector2f entityPosition;
	sf::Vector2f oldPosition = this->getPosition();
	this->setLayerPosition(position);

	for (int i = 0; i < transformableElements.size(); i++)
	{
		entityPosition = transformableElements[i]->getPosition();
		transformableElements[i]->setPosition(position.x - (oldPosition.x - entityPosition.x), position.y - (oldPosition.y - entityPosition.y));
	}
}
void GuiLayer::setRotation(float angle)
{
	for (int i = 0; i < transformableElements.size(); i++)
	{
		transformableElements[i]->setRotation(angle);
	}
}
void GuiLayer::setScale(float factorX, float factorY)
{
	for (int i = 0; i < transformableElements.size(); i++)
	{
		transformableElements[i]->setScale(factorX, factorY);
	}
}
void GuiLayer::setScale(const sf::Vector2f &factors)
{
	for (int i = 0; i < transformableElements.size(); i++)
	{
		transformableElements[i]->setScale(factors);
	}
}
void GuiLayer::setOrigin(float x, float y)
{
	this->setOrigin(x, y);
}
void GuiLayer::setOrigin(const sf::Vector2f &origin)
{
	this->setOrigin(origin);
}
void GuiLayer::move(float offsetX, float offsetY)
{
	for (int i = 0; i < transformableElements.size(); i++)
	{
		transformableElements[i]->move(offsetX, offsetX);
	}
}
void GuiLayer::move(const sf::Vector2f &offset)
{
	for (int i = 0; i < transformableElements.size(); i++)
	{
		transformableElements[i]->move(offset);
	}
}
void GuiLayer::rotate(float angle)
{
	for (int i = 0; i < transformableElements.size(); i++)
	{
		transformableElements[i]->rotate(angle);
	}
}
void GuiLayer::scale(float factorX, float factorY)
{
	for (int i = 0; i < transformableElements.size(); i++)
	{
		transformableElements[i]->scale(factorX, factorY);
	}
}
void GuiLayer::scale(const sf::Vector2f &factors)
{
	for (int i = 0; i < transformableElements.size(); i++)
	{
		transformableElements[i]->scale(factors);
	}
}
