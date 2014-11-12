#include "AbstractArea.h"
#include "ResourceManager.h"

Button::Button(sf::Shape* shape) 
	: AbstractArea(shape)
{
	progress_shape_ = new sf::RectangleShape(*((sf::RectangleShape*)shape));
	progress_shape_->setScale(0.5, 1);
	progress_shape_->setFillColor(sf::Color(0.0f, 255.0f, 0.0f, 200.0f));
}

Button::Button(sf::Vector2f position, sf::Vector2f size)
	: enabled_(true), enterTime_(0L), progress_(0.0f), MAX_TIME(1.0f)
{	
	sf::RectangleShape *button_shape = new sf::RectangleShape(size);
	button_shape->setPosition(position);
	shape_ = button_shape;

	progress_shape_ = new sf::RectangleShape(size);
	progress_shape_->setPosition(position);
	progress_shape_->setScale(0, 1);
	progress_shape_->setFillColor(sf::Color(212, 237, 252, 120));
	
	btn_sprite_.setPosition(position.x, position.y);
	btn_text_.setFont(ResourceManager::instance().getFont("sansation.ttf"));
	btn_text_.setString("Button");	
}

void Button::onHover(unsigned x, unsigned y, sf::Clock clock)
{
	if (!enabled_) { return; }

	if (!inside_)
	{
		enterTime_ = clock.getElapsedTime().asMilliseconds();		
	}
	else
	{
		progress_ = ( clock.getElapsedTime().asMilliseconds() - enterTime_ ) /  CLOCKS_PER_SEC;		
		if (progress_ > MAX_TIME)
		{
			enabled_ = false;
			action_();
		}
	}
}

void Button::onLeave(unsigned x, unsigned y)
{
	progress_shape_->setScale(0, 1);	
	progress_ = 0.0f;
}

void Button::draw(sf::RenderWindow *render_window)
{	  
	render_window->draw(btn_sprite_);
	render_window->draw(btn_text_);
	render_window->draw(*progress_shape_);
	// don't draw progress if not needed
	if (enabled_ && inside_)
	{
		setProgress(progress_);
	}	
}

void Button::setProgress(float percentage)
{
	progress_shape_->setScale(percentage, 1);
}

void Button::setText(std::string text)
{
	btn_text_.setString(text);
}

void Button::setTextColor(sf::Color color)
{
	btn_text_.setColor(color);
}

void Button::setCharacterSize(float size)
{
	btn_text_.setCharacterSize(size);
}

void Button::setTextScale(sf::Vector2f scale)
{
	btn_text_.setScale(scale);
}

sf::Vector2f Button::getTextSize()
{
	return sf::Vector2f(btn_text_.getLocalBounds().width, btn_text_.getCharacterSize());
}

float Button::getCharacterSize()
{
	return btn_text_.getCharacterSize();
}

void Button::setTexture(sf::Texture& texture)
{
	btn_sprite_.setTexture(texture);
	sf::Vector2f from(btn_sprite_.getTexture()->getSize());
	sf::Vector2f scale = ShapeUtils::scaleFromTo(from, progress_shape_->getSize());		
	btn_sprite_.setScale(scale);	
}

void Button::setTextPosition(sf::Vector2f position)
{
	btn_text_.setPosition(position);
}