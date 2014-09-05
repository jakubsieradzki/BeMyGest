#pragma once

#include "AreaManager.h"
#include <SFML/Graphics/RenderTarget.hpp>

class GameScreen : public sf::RenderTexture
{
public:
  GameScreen(sf::RenderWindow* render_window) 
    : render_window_(render_window),
      area_mgr_(new AreaManager(render_window)) {        
  }
	virtual ~GameScreen() { delete area_mgr_; }
  virtual void setup() = 0;
  void draw() {
    area_mgr_->draw();
    customDrawing();
  }
  virtual void customDrawing() {}
  void update(unsigned x_track_hand, unsigned y_track_hand) {
    area_mgr_->update(x_track_hand, y_track_hand, game_clock_);
    customUpdate();
  };
  virtual void customUpdate() {}
  virtual void onActivation() {}
  virtual void onLeave() {}

	void setLevelFile(std::string level_file) { level_file_ = level_file; }
protected:
  sf::RenderWindow* render_window_;
  AreaManager* area_mgr_;
	sf::Clock game_clock_;
	std::string level_file_;
private:
};