#include "Button.hpp"
#include "../managers/SceneManager.hpp"
#include <iostream>
Button::Button(sf::Texture& p_texture, sf::Vector2f p_size, sf::Vector2f p_position) :texture(p_texture)
{
	this->size = p_size;
	this->position = p_position;
	clickableArea = new sf::RectangleShape(size);
	clickableArea->setPosition(position);
	sprite = new sf::Sprite();
	sprite->setTexture(texture);
	sprite->setTextureRect(sf::IntRect(0, 0, texture.getSize().x, texture.getSize().y/2));
	sprite->setPosition(position);
	resizeSprite();

	currentState = States::INACTIVE;
	haveText = false;
}
void Button::setText(std::string p_text, sf::Font& p_font, int p_size, sf::Color p_color)
{
	haveText = true;

	this->textSize = p_size;
	this->stringText = p_text;

	this->text = new sf::Text();
	text->setString(this->stringText);

	text->setFont(p_font);
	text->setCharacterSize(p_size);
	text->setFillColor(p_color);

	centerText();
}

void Button::setPosition(sf::Vector2f p_position)
{
	this->position = p_position;
	sprite->setPosition(position);
}
void Button::resizeSprite(float factor)
{
	sprite->setScale(size.x*factor / sprite->getLocalBounds().width, size.y*factor / sprite->getLocalBounds().height);
	sprite->setPosition(sf::Vector2f(this->position.x + (size.x - size.x*factor)/2, this->position.y + (size.y - size.y*factor)/2));
}
void Button::centerText()
{
	sf::FloatRect textRect = text->getLocalBounds();
	text->setOrigin(textRect.left + textRect.width / 2.f, textRect.top + textRect.height / 2.f);
	text->setPosition(sprite->getPosition().x + sprite->getGlobalBounds().width / 2, sprite->getPosition().y + sprite->getGlobalBounds().height / 2);
}
void Button::pressedEffect()
{
	sprite->setTextureRect(sf::IntRect(0, texture.getSize().y / 2, texture.getSize().x, texture.getSize().y / 2));
}
void Button::normalEffect()
{
	sprite->setTextureRect(sf::IntRect(0, 0, texture.getSize().x, texture.getSize().y / 2));
}
void Button::setActive()
{
	currentState = States::ACTIVE;
	pressedEffect();
}
void Button::setInActive()
{
	currentState = States::INACTIVE;
	normalEffect();
}
void Button::update()
{
	mousePosition = sf::Mouse::getPosition(*SceneManager::getInstance()->getWindow());
	mappedMousePosition = SceneManager::getInstance()->getWindow()->mapPixelToCoords(mousePosition);
	transformedMousePosition = sprite->getInverseTransform().transformPoint(mappedMousePosition);
	if (isCollised(transformedMousePosition) && currentState != States::ACTIVE)
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && currentState == States::INACTIVE)
		{
			currentState = States::INACTIVE;
			normalEffect();
		}
		else if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && currentState != States::PRESSED)
		{
			currentState = States::PRESSED;
			pressedEffect();
			dispatchEvent(Event::PRESSED);
		}
		else if (!sf::Mouse::isButtonPressed(sf::Mouse::Left) && currentState == States::PRESSED)
		{
			dispatchEvent(Event::UNPRESSED);
			currentState = States::HOVERED;
			normalEffect();
			dispatchEvent(Event::HOVER);
		}
		else if (!sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			currentState = States::HOVERED;
			normalEffect();
			dispatchEvent(Event::HOVER);
		}
	}
	else if (currentState != States::INACTIVE && currentState != States::ACTIVE)
	{
		currentState = States::INACTIVE;
		dispatchEvent(Event::UNHOVER);
		normalEffect();
	}
}
bool Button::isCollised(sf::Vector2f mousePosition)
{
	if (sprite->getLocalBounds().contains(mousePosition))
		return true;
	return false;
}
void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(*sprite, states);
	if (haveText)target.draw(*text, states);
}