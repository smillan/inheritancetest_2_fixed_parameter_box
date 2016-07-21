#include <Arduino.h>
#include <Encoder.h>
#include <stack>
#include <vector>
#include <Streaming.h>
//.-----Sequencing

#include "Clock.h"
#include "Track.h"
#include "Control.h"
#include "Scales.h"
#include "MelodicGenerators.h"
#include "Triggering.h"
#include "TrackParameters.h"
#include "Filters.h"
#include "Chords.h"


#define MAX_TRACKS 4

#define ClockOutTime 10
#define ClockOutLed  24

class Orsini {

	public:
	Control control;
	TrackParameters parameters;
	MelodicGenerators generators;
	Triggering triggerGens;
	Filters filters;
	Chords chords;
	long	ct = 0;
	unsigned long previousMillis = 0;        // will store last time LED was updated
	unsigned long clockMillis = 0;        // will store last time LED was updated
	byte ledState = LOW;
	// Scales globalScales;
	// Encoder knobLeft(2, 3);
	// Encoder knobRight(7, 8);
	long positionLeft  = -999;
	long positionRight = -999;
	///---sequencing
	// MIDI_Class MIDI;
	Clocko theClock;
	int beats=0;
	int bars=0;
	byte nBeats=4;
	byte nBars=4;
	// StackArray <Track> stack;
	// Track* trackList[MAX_TRACKS];
	Track track0;
	Track track1;
	Track track2;
	Track track3;
	Track* tracks[4]={&track0,&track1,&track2,&track3};
	// Track track4;
	// Track track5;
	// std::vector<Track> tracks;
   Orsini()
	  {
		 // tracks.push_back(track0);
		// theClock.addMidi(MIDI);
		pinMode(ClockOutLed, OUTPUT);
		for (int i = 0; i < 4; ++i)
		{
			tracks[i]->addGens(generators);

			tracks[i]->addParameters(parameters);
			tracks[i]->addTrigs(triggerGens);
			tracks[i]->addFilters(filters);
			tracks[i]->setChannel((i+1));
			tracks[i]->trackNumber=i;


		}
			track0.init();
			delay(100);
			track1.init();
			delay(100);
			track2.init();
			delay(100);
			track3.init();
			delay(100);
			// track1.init();

		track0.isPlaying=true;
		track1.isPlaying=true;
		track2.isPlaying=true;
		track3.isPlaying=true;
		// track0.addGens(generators);
		// track0.addParameters(parameters);
		// track0.addTrigs(triggerGens);
		// track0.init();


	  }

	void reset()
	{

		for (int i = 0; i < 4; ++i)
		{
			tracks[i]->stop();

		}
		// track0.stop();
		// track0.stop();
		// track2.stop();
		// track3.stop();
		
		// track2.run();
		// track3.run();

	}
	void start()
	{

		// track0.start();
		
		for (int i = 0; i < 4; ++i)
		{
			tracks[i]->start();

		}
		beats=0;
		bars=0;
		// track2.start();
		// track3.start();
				



	}

	void displayControl(){
		control.control(tracks);
		// control.showDataOptions();

	}

	void run()
	{
		// control();
		if (millis()%5==0)
		{
			displayControl();
			/* code */
		}
		for (int i = 0; i < 4; ++i)
		{
			if (tracks[i]->isPlaying) tracks[i]->run();

		}

		// track0.run();
		ledClockDown(ClockOutLed);
		// track2.run();
		// track3.run();

	}
	void ledClockUp(byte led){
		// digitalWrite(led, HIGH);


	}
	void ledClockDown(byte led){
		unsigned long currentMillis = millis();
	  if(currentMillis >= clockMillis) {
		// save the last time you blinked the LED
		
		digitalWrite(ClockOutLed, LOW);
		// ledState=LOW;
		// if the LED is off turn it on and vice-versa:
		// set the LED with the ledState of the variable:
		// digitalWrite(ClockOutLed, LOW);
	  }

	}

	void midiClockTick()
	{
		unsigned long currentMillis = millis();

		 // if (ledState == LOW)
			//   ledState = HIGH;
			// else
			//   ledState = LOW;
		clockMillis=currentMillis+10;
		digitalWrite(ClockOutLed, HIGH);

		// if ((ct % (6)) == 0 ) {

		// }
		// ct++;
		// previousMillis = currentMillis;
		// theClock.tick();
		for (int i = 0; i < 4; ++i)
		{
			if (tracks[i]->isPlaying) tracks[i]->tick();

		}



	}
	  virtual const String classname() { return "orsini";}

   protected:
};