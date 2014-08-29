#pragma once

class MusicBlock
{
public:
	float x() { return x_; }
	float y() { return y_; }
	float width() { return width_; }
	float height() { return height_; }
	float note() { return note_; }

	void setX(float x) { x_ = x; };	
	void setY(float y) { y_ = y; }
	void setWidth(float width) { width_ = width; }
	void setHeight(float h) { height_ = h; }
	void setNote(float note) { note_ = note; }

private:
	float x_;
	float y_;
	float width_;
	float height_;
	float note_;
};