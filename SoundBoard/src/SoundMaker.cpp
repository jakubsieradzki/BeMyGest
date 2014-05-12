#include "SoundMaker.h"

SoundMaker::~SoundMaker()
{
	delete tickData_.instrument;
}

int simple_tick( void *outputBuffer, void *inputBuffer, unsigned int nBufferFrames,
	double streamTime, RtAudioStreamStatus status, void *userData )
{
	TickData *data = (TickData *) userData;
	register StkFloat *samples = (StkFloat*) outputBuffer;
	for (unsigned int i = 0; i < nBufferFrames; ++i)
	{
		*samples++ = data->instrument->tick();
	}
	return 0;
}

int tick(void *outputBuffer, void *inputBuffer, unsigned int nBufferFrames,
		double streamTime, RtAudioStreamStatus status, void *userData )
{
	TickData *data = (TickData *) userData;
	register StkFloat *samples = (StkFloat *) outputBuffer;
	for ( unsigned int i=0; i<nBufferFrames; i++ ) 
	{
		*samples++ = data->instrument->tick();
		if ( ++data->counter % 2000 == 0 ) 
		{
			data->scaler += 0.025;
			data->instrument->setFrequency( data->freq * data->scaler );
		}
	}
	if ( data->counter > 80000 )
	{
		std::cout << "done" << std::endl;
		data->done = true;
	}
	return 0;
}

void SoundMaker::initDac()
{
	 // Figure out how many bytes in an StkFloat and setup the RtAudio stream.
	RtAudio::StreamParameters parameters;
	parameters.deviceId = dac_.getDefaultOutputDevice();
	parameters.nChannels = 1;
	RtAudioFormat format = ( sizeof(StkFloat) == 8 ) ? RTAUDIO_FLOAT64 : RTAUDIO_FLOAT32;
	unsigned int bufferFrames = RT_BUFFER_SIZE;
	try 
	{
		dac_.openStream( &parameters, NULL, format, (unsigned int)Stk::sampleRate(), &bufferFrames, &simple_tick, (void *)&tickData_ );
	}
	catch ( RtAudioError& error ) 
	{
		error.printMessage();
		//TODO handle error
	}
}

void SoundMaker::setInstrument(Instrmnt *instrument)
{
	tickData_.instrument = instrument;
}

void SoundMaker::setFrequency(StkFloat frequency)
{
	tickData_.freq = frequency;
}

void SoundMaker::startStream()
{
	try
	{
		dac_.startStream();
	}
	catch ( RtAudioError &error )
	{
		error.printMessage();
	}
}

void SoundMaker::closeStream()
{
	try
	{
		dac_.closeStream();
	}
	catch ( RtAudioError &error )
	{
		error.printMessage();
	}
}

void SoundMaker::playNote(StkFloat frequency, StkFloat amplitude)
{
	tickData_.instrument->noteOn(frequency, amplitude);
}

void SoundMaker::stopNote()
{
	tickData_.instrument->noteOff(0.5);
}