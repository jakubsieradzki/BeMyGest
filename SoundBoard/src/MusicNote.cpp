#include "MusicNote.h"

MusicNote::MusicNote(float freq, float start_time, float duration)
	: frequency_(freq), start_time_(start_time), duration_(duration)
{}

MusicNote::~MusicNote()
{}