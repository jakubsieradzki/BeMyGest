#include "AbstractArea.h"
#include "ResourceManager.h"

Button::Button(sf::Shape* shape) 
	: AbstractArea(shape)
{
	progress_shape_ = new sf::RectangleShape(*((sf::RectangleShape*)shape));
	progress_shape_->setScale(0.5, 1);
	progress_shape_->setFillColor(sf::Color(0.0f, 255.0f, 0.0f, 200.0f));
}

Button::Button(sf::Vector2f position, sf::Vector2f size, std::string text)
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
	
	btn_sprite_.setTexture(ResourceManager::instance().getImage("menu_button.png"));
	btn_sprite_.setPosition(position.x, position.y);
	float x_scale = size.x / btn_sprite_.getTexture()->getSize().x;
	float y_scale = size.y / btn_sprite_.getTexture()->getSize().y;
	btn_sprite_.setScale(x_scale, y_scale);	

	btn_text_.setFont(ResourceManager::instance().getFont("sansation.ttf"));
	btn_text_.setString(text);
	btn_text_.setColor(sf::Color::White);
	btn_text_.setCharacterSize(btn_sprite_.getTextureRect().height*y_scale / 2);
	btn_text_.setPosition(position.x + (btn_sprite_.getTextureRect().width*x_scale - btn_text_.getGlobalBounds().width) / 2,
		position.y + btn_text_.getLocalBounds().height/2);	

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

void Button::draw(sf::RenderWindow *render_window)
{	
  //AbstractArea::draw(render_window);
	render_window->draw(btn_sprite_);
	render_window->draw(btn_text_);
	render_window->draw(*progress_shape_);
	// don't draw progress if not needed
	if (!enabled_ || !inside_)
	{
		return; 
	}

	//float current_width = (progress_ * progress_shape_->getSize().x) / MAX_TIME;
	setProgress(progress_);	
  //sf::RectangleShape rect(sf::Vector2f(current_width, shape_->getScale().y));
	//rect.setPosition(shape_->getPosition());
  //rect.setFillColor(sf::Color(0.0f, 255.0f, 0.0f, 200.0f));    
  //render_window->draw(rect);
}

void Button::setProgress(float percentage)
{
	progress_shape_->setScale(percentage, 1);
}