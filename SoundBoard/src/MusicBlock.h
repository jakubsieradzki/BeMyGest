#pragma once

#include <SFML/Graphics.hpp>

class MusicBlock
{
public:
	float x() { return x_; }
	float y() { return y_; }
	float width() { return width_; }
	float height() { return height_; }
	float note() { return note_; }
	float startTime() { return start_time_; }
	float duration() { return duration_; }
	sf::Vector2f finalPosition() { return final_position_; }

	void setX(float x) { x_ = x; };	
	void setY(float y) { y_ = y; }
	void setWidth(float width) { width_ = width; }
	void setHeight(float h) { height_ = h; }
	void setNote(float note) { note_ = note; }
	void setStartTime(float start_time) { start_time_ = start_time; }
	void setDuration(float duration) { duration_ = duration; }
	void setFinalPosition(sf::Vector2f final_position) { final_position_ = final_position; }

private:
	float x_;
	float y_;
	float width_;
	float height_;
	float note_;
	float start_time_, duration_;
	sf::Vector2f final_position_;
};