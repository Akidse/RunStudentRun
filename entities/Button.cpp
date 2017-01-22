#include "Button.hpp"

Button::Button(std::string p_text, sf::Texture& p_texture, sf::Vector2f p_size) :texture(p_texture)
{
	sprite = new sf::Sprite();
	sprite->setTexture(p_texture);
	sprite->setPosition(0, 0);
	sprite->setScale(p_size.x / sprite->getLocalBounds().width, p_size.y / sprite->getLocalBounds().height);
	text = new sf::Text();
	text->setString(p_text);
	text->setFillColor(sf::Color::White);
	text->setCharacterSize(20);
}

void Button::setPosition(sf::Vector2f position)
{
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
void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(*sprite, states);
	target.draw(*text, states);
}