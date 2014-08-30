#pragma once

#include <SFML/Graphics.hpp>
#include "Instrmnt.h"
#include "RtAudio.h"
#include "AbstractArea.h"
#include "AreaBuilder.h"

class SoundMovingAreaBuilder : public AreaBuilder<SoundMovingAreav2>
{
private:
	sf::Shape *shape_;
	stk::Instrmnt *instrument_;
	stk::StkFloat base_freq_;
	sf::Vector2f final_position_;
	float start_time_, duration_;
public:
	SoundMovingAreaBuilder();
	~SoundMovingAreaBuilder();

	SoundMovingAreaBuilder& withShape(sf::Shape* shape);
	SoundMovingAreaBuilder& withInstrument(stk::Instrmnt *instrument);
	SoundMovingAreaBuilder& withFreq(stk::StkFloat baseFreq);
	SoundMovingAreaBuilder& withFinalPosition(sf::Vector2f final_pos);
	SoundMovingAreaBuilder& withStartTime(float startTime);
	SoundMovingAreaBuilder& withDuration(float duration);

	SoundMovingAreav2* build();
};