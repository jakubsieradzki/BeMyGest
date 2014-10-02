#include "SoundMaker.h"
#include "SKINI.msg"

#define DELTA_CONTROL_TICKS 64

SoundMaker::~SoundMaker()
{
	delete tickData_.instrument;
}

void processMessage( TickData* data )
{
	register StkFloat value1 = data->message.floatValues[0];
	register StkFloat value2 = data->message.floatValues[1];
	switch( data->message.type ) {
		case __SK_Exit_:
			data->done = true;
			return;
		case __SK_NoteOn_:
			if ( value2 == 0.0 ) // velocity is zero ... really a NoteOff
				data->instrument->noteOff( 0.5 );
			else { // a NoteOn
				std::cout << "tick note on" << std::endl;
				//StkFloat frequency = 220.0 * pow( 2.0, (value1 - 57.0) / 12.0 );
				data->instrument->noteOn( value1, value2 );
			}
			break;
		case __SK_NoteOff_:
			std::cout << "tick note off" << std::endl;
			data->instrument->noteOff(value2);
			break;
		case __SK_ControlChange_:
			data->instrument->controlChange( (int) value1, value2 );
			break;
		case __SK_AfterTouch_:
			data->instrument->controlChange( 128, value1 );
	} // end of switch
	data->haveMessage = false;
	return;
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

int control_tick(void *outputBuffer, void *inputBuffer, unsigned int nBufferFrames,
		double streamTime, RtAudioStreamStatus status, void *userData )
{
	TickData *data = (TickData *) userData;
	register StkFloat *samples = (StkFloat *) outputBuffer;
	int counter, nTicks = (int) nBufferFrames;

	while ( nTicks > 0 && !data->done )
	{
		if ( !data->haveMessage ) 
		{
			data->messager.popMessage( data->message );
			if ( data->message.type > 0 ) 
			{
				data->counter = (long) (data->message.time * Stk::sampleRate());
				data->haveMessage = true;
			}
			else
			{
				data->counter = DELTA_CONTROL_TICKS;
			}
		}
		counter = std::min( nTicks, data->counter );
		data->counter -= counter;
		for ( int i=0; i<counter; i++ )
		{
			*samples++ = data->instrument->tick();
			nTicks--;
		}
		if ( nTicks == 0 ) break;
		// Process control messages.
		if ( data->haveMessage ) processMessage( data );
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
	/*stk::Skini::Message msg;
	msg.type = __SK_NoteOn_;
	msg.floatValues[0] = frequency;
	msg.floatValues[1] = amplitude;
	tickData_.messager.pushMessage(msg);*/
}

void SoundMaker::stopNote()
{
	tickData_.instrument->noteOff(0.5);	
	/*stk::StkFloat ampl = 0.5;
	stk::Skini::Message msg;
	msg.type = __SK_NoteOff_;
	msg.floatValues[0] = 300.0;
	msg.floatValues[1] = 0.3;
	tickData_.messager.pushMessage(msg);*/
}