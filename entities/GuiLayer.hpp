#ifndef GUI_LAYER_HPP
#define GUI_LAYER_HPP

#include <SFML/Graphics.hpp>

class GuiLayer : public sf::Drawable
{
private:
	bool isActiveLayer;
	sf::Vector2f position;
	sf::Transform transform;
	std::vector<sf::Drawable*> drawableElements;
	std::vector<sf::Transformable*> transformableElements;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
public:
	GuiLayer();
	GuiLayer(float x, float y);
	sf::Vector2f getPosition();
	void setLayerPosition(float x, float y);
	void setLayerPosition(const sf::Vector2f &position);
	void setPosition(float x, float y);
	void setPosition(const sf::Vector2f &position);
	void setRotation(float angle);
	void setScale(float factorX, float factorY);
	void setScale(const sf::Vector2f &factors);
	void setOrigin(float x, float y);
	void setOrigin(const sf::Vector2f &origin);
	void move(float offsetX, float offsetY);
	void move(const sf::Vector2f &offset);
	void rotate(float angle);
	void scale(float factorX, float factorY);
	void scale(const sf::Vector2f &factors);
	template <class T> void removeEntity(T& p_element)
	{
		for (int i = 0; i < drawableElements.size(); i++)
		{
			if (drawableElements[i] == dynamic_cast<sf::Drawable*>(&p_element))
			{
				drawableElements.erase(drawableElements.begin() + i);
			}
		}
	}
	template <class T> void addEntity(T& p_element)
	{
		drawableElements.push_back(dynamic_cast<sf::Drawable*>(&p_element));
		transformableElements.push_back(dynamic_cast<sf::Transformable*>(&p_element));
	}

	void setActive(bool p_active);
	bool isActive();
};


#endif