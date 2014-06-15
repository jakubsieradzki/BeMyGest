#pragma once

class MusicNote
{
public:
	MusicNote(float frquency, float start_time, float duration);
	~MusicNote();
	float frequency() { return frequency_; }
	float start_time() { return start_time_; }
	float duration() { return duration_; }
private:
	float frequency_;
	float start_time_;
	float duration_;
};