#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <SFML/Graphics.hpp>
#include <string>
#include "../SFMEngine/Eventable.hpp"
class Button: public sf::Drawable, public Eventable, public sf::Transformable
{
	const int COMMON_TEXT_SIZE = 20;
public:
	static enum Event
	{
		PRESSED,
		UNPRESSED,
		HOVER,
		UNHOVER
	};
	enum class States
	{
		ACTIVE,
		INACTIVE,
		PRESSED,
		HOVERED
	};
	bool haveText;
	States currentState;
	Button(sf::Texture& p_texture, sf::Vector2f p_size, sf::Vector2f p_position);
	void setText(std::string p_text, sf::Font& p_font, int p_size, sf::Color p_color);
	void setPosition(sf::Vector2f position);
	void update();
	void setActive();
	void setInActive();
private:
	sf::Sprite* sprite;
	sf::Texture& texture;
	sf::Vector2f size;
	sf::Text* text;
	sf::String stringText;
	sf::Vector2f position;
	sf::RectangleShape* clickableArea;
	int textSize;
	void resizeSprite(float factor = 1);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void pressedEffect();
	bool isCollised(sf::Vector2f mousePosition);
	void normalEffect();
	void centerText();
	
	sf::Vector2i mousePosition;
	sf::Vector2f mappedMousePosition;
	sf::Vector2f transformedMousePosition;
};
#endif