#include "Card.h"

void Card::DisplayStats(sf::RenderWindow& window)
{
	sf::Font font;
	if (!font.loadFromFile("arial.ttf"))
	{
		std::cout << "Error loading the font" << std::endl;
	}
	sf::Text text1, text2, text3;
	text1.setFont(font);
	text2.setFont(font);
	text3.setFont(font);
	std::string str1 = std::to_string(this->ad);
	std::string str2 = std::to_string(this->hp);
	std::string str3 = std::to_string(this->tokens);
	text1.setString(str1);
	text2.setString(str2);
	text3.setString(str3);
	text1.setStyle(sf::Text::Bold);
	text2.setStyle(sf::Text::Bold);
	text3.setStyle(sf::Text::Bold);
	text1.setFillColor(sf::Color::Black);
	text2.setFillColor(sf::Color::Black);
	text3.setFillColor(sf::Color::Black);

	sf::Vector2f pos1= this->sprite.getPosition();
	pos1.x += 15;
	pos1.y += 137;
	text1.setPosition(pos1);
	window.draw(text1);

	sf::Vector2f pos2 = this->sprite.getPosition();
	pos2.x += 145;
	pos2.y += 137;
	text2.setPosition(pos2);
	window.draw(text2);

	sf::Vector2f pos3 = this->sprite.getPosition();
	pos3.x += 155;
	pos3.y += 5;
	text3.setPosition(pos3);
	window.draw(text3);
}