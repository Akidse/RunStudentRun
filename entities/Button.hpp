#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <SFML/Graphics.hpp>
#include <string>
#include "../SFMEngine/Eventable.hpp"
class Button: public sf::Drawable, public Eventable
{
	const int COMMON_TEXT_SIZE = 20;
public:
	static enum Event
	{
		PRESSED = 0,
		UNPRESSED = 1,
		HOVER = 2,
		UNHOVER = 3
	};
	enum class States
	{
		INACTIVE = 0,
		PRESSED = 1,
		HOVERED = 2
	};
	States currentState;
	Button(std::string p_text, sf::Texture& p_texture, sf::Vector2f p_size);
	void setPosition(sf::Vector2f position);
	void setTextColor(sf::Color p_color);
	void setTextSize(int p_size);
	void setTextFont(sf::Font& p_font);
	void update();
private:
	sf::Sprite* sprite;
	sf::Texture& texture;
	sf::Vector2f size;
	sf::Text* text;
	sf::String stringText;
	sf::Vector2f position;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void pressedEffect();
	bool isCollised(sf::Vector2i mousePosition);
	void normalEffect();
};
#endif