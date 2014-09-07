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
	: inside_(false), enabled_(true), enterTime_(0L), progress_(0.0f), MAX_TIME(1.0f)
{	
	sf::RectangleShape *button_shape = new sf::RectangleShape(size);
	button_shape->setPosition(position);
	//button_shape->setFillColor(sf::Color(0, 0, 255, 200));  
	//button_shape->setOutlineColor(sf::Color(0.0f, 0.0f, 0.0f, 255.0f));
  //button_shape->setOutlineThickness(1.0f);
	shape_ = button_shape;

	progress_shape_ = new sf::RectangleShape(size);
	progress_shape_->setPosition(position);
	progress_shape_->setScale(0, 1);
	progress_shape_->setFillColor(sf::Color(212, 237, 252, 120));
	
	//btn_sprite_.setTexture(ResourceManager::instance().getImage("menu_button.png"));
	btn_sprite_.setPosition(position.x, position.y);
	//float x_scale = size.x / btn_sprite_.getTexture()->getSize().x;
	//float y_scale = size.y / btn_sprite_.getTexture()->getSize().y;
	//btn_sprite_.setScale(x_scale, y_scale);	

	btn_text_.setFont(ResourceManager::instance().getFont("sansation.ttf"));
	btn_text_.setString("Button");	
	//btn_text_.setColor(sf::Color::White);
	//btn_text_.setCharacterSize(btn_sprite_.getTextureRect().height*y_scale / 2);
	//sf::Vector2f from(btn_text_.getLocalBounds().width, btn_text_.getLocalBounds().height);
	//sf::Vector2f to(size.x*0.6, size.y * 0.4);
	//btn_text_.setScale(ShapeUtils::scaleFromTo(from, to));
	//btn_text_.setPosition(position);		

}

void Button::onHover(unsigned x, unsigned y)
{
	if (!enabled_) { return; }

	if (inside_ == false)
	{
		enterTime_ = clock();
	}
	else
	{
		progress_ = float( clock () - enterTime_ ) /  CLOCKS_PER_SEC;
		if (progress_ > MAX_TIME)
		{
			enabled_ = false;
			action_();
		}
	}
	inside_ = true;
}

void Button::onLeave(unsigned x, unsigned y)
{
	progress_shape_->setScale(0, 1);
	inside_ = false;
	progress_ = 0.0f;
}

sf::RectangleShape* createDebug(sf::Vector2f size, sf::Vector2f position)
{
	sf::RectangleShape* debug = new sf::RectangleShape(size);
	debug->setPosition(position);
	debug->setOutlineColor(sf::Color::Red);
	debug->setOutlineThickness(2.0);
	debug->setFillColor(sf::Color::Transparent);
	
	return debug;
}

void Button::draw(sf::RenderWindow *render_window)
{	
  //AbstractArea::draw(render_window);	
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