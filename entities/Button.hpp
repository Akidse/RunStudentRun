#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <SFML/Graphics.hpp>
#include <string>
class Button: public sf::Drawable
{
public:
	Button(std::string p_text, sf::Texture& p_texture, sf::Vector2f p_size);
	void setPosition(sf::Vector2f position);
	void setTextColor(sf::Color p_color);
	void setTextSize(int p_size);
	void setTextFont(sf::Font& p_font);
private:
	sf::Sprite* sprite;
	sf::Texture& texture;
	sf::Vector2f size;
	sf::Text* text;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};
#endif