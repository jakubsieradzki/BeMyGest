#ifndef SOUND_MAKER_
#define SOUND_MAKER_

// #include "BeeThree.h"
#include "RtAudio.h"
#include "Instrmnt.h"
#include "Messager.h"

using namespace stk;

struct TickData
{
	Instrmnt *instrument;
	StkFloat freq;
	StkFloat scaler;
	Messager messager;
	Skini::Message message;
	int counter;
	bool haveMessage;
	bool done;

	TickData() : instrument(0), scaler(1.0), counter(0), done(false), haveMessage(false) {}
};

class SoundMaker
{
public:
	SoundMaker() { initDac(); }
	~SoundMaker();

	void setInstrument(Instrmnt * instrument);
	// not needed ?
	void setFrequency(StkFloat frequency);
	void startStream();
	void closeStream();
	void playNote(StkFloat frequency, StkFloat amplitude);
	void stopNote();
private:
	TickData tickData_;
	// zrobic wskaznik zeby wiele instancji dzielilo stream ?
	RtAudio dac_;

	void initDac();
};



#endif