#pragma once

#include <SFML/Graphics.hpp>

namespace UI {

	class Button {
	private:
		sf::RectangleShape button;
		sf::Text text;

	public:


		Button(sf::Vector2f size, std::string t, sf::Color bgColor, sf::Color textColor, sf::Font& font) : text(font)
		{

			text.setString(t);
			text.setFillColor(textColor);

			button.setFillColor(bgColor);
			button.setSize(size);
		};

		~Button() {};

		void setFont(const sf::Font& font)
		{
			text.setFont(font);
		}
		void setTextColor(sf::Color color)
		{
			text.setFillColor(color);
		}

		void setBackColor(sf::Color color)
		{
			button.setFillColor(color);
		}



		void setPosition(sf::Vector2f pos)
		{
			float xPos = (pos.x + button.getLocalBounds().size.x / 2) - (text.getLocalBounds().size.x / 2);
			float yPos = (pos.y + button.getLocalBounds().size.y / 2) - (text.getLocalBounds().size.y / 2);

			button.setPosition(pos);
			text.setPosition({ xPos, yPos });
		}

		bool isMouseOver(sf::RenderWindow& window)
		{
			float mouseX = sf::Mouse::getPosition(window).x;
			float mouseY = sf::Mouse::getPosition(window).y;

			if (mouseX < button.getPosition().x + button.getLocalBounds().size.x &&
				mouseX > button.getPosition().x &&
				mouseY < button.getPosition().y + button.getLocalBounds().size.y &&
				mouseY > button.getPosition().y)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		void draw(sf::RenderWindow& window)
		{
			window.draw(button);
			window.draw(text);
		}
	};

}