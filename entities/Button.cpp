#include "Button.hpp"
#include "../managers/SceneManager.hpp"
#include <iostream>
Button::Button(std::string p_text, sf::Texture& p_texture, sf::Vector2f p_size) :texture(p_texture)
{
	this->size = p_size;
	this->stringText = p_text;
	sprite = new sf::Sprite();
	text = new sf::Text();
	this->normalEffect();
	currentState = States::INACTIVE;
}

void Button::setPosition(sf::Vector2f p_position)
{
	position = p_position;
	sprite->setPosition(position);
	sf::FloatRect textRect = text->getLocalBounds();
	text->setOrigin(textRect.left + textRect.width / 2.f, textRect.top + textRect.height / 2.f);
	text->setPosition(sprite->getPosition().x + sprite->getGlobalBounds().width / 2, sprite->getPosition().y + sprite->getGlobalBounds().height / 2);
}

void Button::setTextColor(sf::Color p_color)
{
	text->setFillColor(p_color);
}
void Button::setTextSize(int p_size)
{
	text->setCharacterSize(p_size);
}
void Button::setTextFont(sf::Font& p_font)
{
	text->setFont(p_font);
}
void Button::pressedEffect()
{
	sprite->setScale(size.x*0.8 / sprite->getLocalBounds().width, size.y*0.8 / sprite->getLocalBounds().height);
	text->setCharacterSize((int)COMMON_TEXT_SIZE*0.8);
}
void Button::normalEffect()
{
	sprite->setTexture(texture);
	sprite->setPosition(0, 0);
	sprite->setScale(size.x / sprite->getLocalBounds().width, size.y / sprite->getLocalBounds().height);
	text->setString(stringText);
	text->setFillColor(sf::Color::White);
	text->setCharacterSize(COMMON_TEXT_SIZE);
}
void Button::update()
{
	sf::Vector2i mousePosition = sf::Mouse::getPosition(*SceneManager::getInstance()->getWindow());
	if (isCollised(mousePosition))
	{
		if (currentState == States::INACTIVE)
		{
			std::cout << "HOVER" << std::endl;
			currentState = States::HOVERED;
			dispatchEvent(Event::HOVER);
		}
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && currentState != States::PRESSED)
		{
			std::cout << "PRESSED" << std::endl;
			currentState = States::PRESSED;
			dispatchEvent(Event::PRESSED);
		}
		else if (!sf::Mouse::isButtonPressed(sf::Mouse::Left) && currentState == States::PRESSED)
		{
			std::cout << "UNPRESSED" << std::endl;
			currentState = States::HOVERED;
			dispatchEvent(Event::UNPRESSED);
		}
	}
	else if(currentState != States::INACTIVE)
	{
		std::cout << "INACTIVE" << std::endl;
		currentState = States::INACTIVE;
		dispatchEvent(Event::UNHOVER);
	}
}
bool Button::isCollised(sf::Vector2i mousePosition)
{
	if (mousePosition.x > position.x && mousePosition.x < position.x + size.x
		&& mousePosition.y > position.y && mousePosition.y < position.x + size.y)
		return true;
	return false;
}
void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(*sprite, states);
	target.draw(*text, states);
}