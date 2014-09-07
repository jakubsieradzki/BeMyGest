#include "UiButtonFactory.h"
#include "ResourceManager.h"

Button* UiButtonFactory::createButton(UiButtonProperties properties, UiButtonId btn_id)
{
	Button* result = new Button(properties.position, properties.size);
	result->setText(properties.text);
	switch (btn_id)
	{
	case MENU_BUTTON:		
		{
			result->setTexture(ResourceManager::instance().getImage("menu_button.png"));		
			result->setTextColor(sf::Color::White);
			result->setCharacterSize(properties.size.y * 0.4);
			sf::Vector2f text_position(
				properties.position.x + (properties.size.x - result->getTextSize().x)/2,
				properties.position.y + (properties.size.y - result->getTextSize().y*1.3)/2
			);
			result->setTextPosition(text_position);

			return result;
		}
	case LEVEL_SELECT_BUTTON:
		{
			result->setTexture(ResourceManager::instance().getImage("select_lvl_button.png"));		
			result->setTextColor(sf::Color::White);
			result->setCharacterSize(properties.size.y * 0.2);
			sf::Vector2f text_position(
				properties.position.x + (properties.size.x - result->getTextSize().x)/2,
				properties.position.y + properties.size.y - result->getTextSize().y*1.3
			);
			result->setTextPosition(text_position);

			return result;
		}
	default:
		std::cout << "ERROR: unknown button id: " << btn_id << std::endl;		
	}
	return result;
}