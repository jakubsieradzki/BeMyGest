#include "GameMgr.h"

void GameMgr::addScore(float points)
{
	if(points > 0.0f && points <= MAX_SCORE)
		score += (points*scoreRatio);
}

void GameMgr::subScore(float points)
{
	if(points > 0.0f && points <= MAX_SCORE)
		score -= points;
	if(score < 0.0f)
		score = 0.0f;
}

void GameMgr::resetScore()
{
	score = 0.0f;
}

float GameMgr::getScore()
{
	return score;
}

void GameMgr::setScore(float points)
{
	if(points >= 0.0f && points <= MAX_SCORE)
		score = points;
}

void GameMgr::resetScoreRatio()
{
	scoreRatio = 1;
}


void GameMgr::setScoreRatio(int ratio)
{
	if(ratio >= 1 && ratio <= MAX_RATIO_SCORE)
		scoreRatio = ratio;
}

void GameMgr::playRandomSound()
{
	int i = rand() % 7;

	sounds[i] -> play();
}

void GameMgr::playFaultSound()
{
	skucha -> play();
}

void GameMgr::loadSounds()
{
	for(int i = 0; i < 7; ++i)
	{
		sf::Music* temp = new sf::Music();
		temp -> openFromFile("resource/sfx/" + boost::lexical_cast<std::string>(i+1) + ".ogg");
		temp -> setVolume(65.0f);
		sounds[i] = temp;
	}
	skucha = new sf::Music();
	skucha -> openFromFile("resource/sfx/skucha.ogg");
	skucha ->setVolume(65.0f);
}