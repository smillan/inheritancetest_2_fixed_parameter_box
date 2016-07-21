#include <Arduino.h>
#include <MIDI.h>
#include "TempoCalc.h"
#include "Scales.h"
#include "Chords.h"
#include "Parameter.h"

// #include "MelodicGenerator.h"

#define VOICE_COUNT 16
#define CLOCK_DIVIDER 6

class MidiHandle {


protected:

public:
	MIDI_Class* midi;
	Triggering* trigger;
		// TrackData* data;

	Scales scales;
	Chords chords;

	int test=0;
	byte NOTE_ON[VOICE_COUNT];
	unsigned long NOTE_ON_SWING[VOICE_COUNT];
	byte NOTE_CHAN[VOICE_COUNT];
	bool midiIn;
	unsigned long NOTE_OFF[VOICE_COUNT];
	byte globalNote;
	bool playing ;
	float tempo = 0;
	unsigned long tempoMillis;;
	TempoCalc tempoCalc;
	byte swingAmount = 0 ;

	int divider;
	int clockDivider= 6 ;
	long _clockCounter=0;
	long step;
	MidiHandle()
	{
		init();


	}
	void addMidi(MIDI_Class& mid){

		midi=&mid;
	}
	void addTrigger(Triggering& trig){

		trigger=&trig;
	}
	void addData(TrackData& mel){

			 // data=&mel;
	}
	void init(){
		for (int i = 0; i < VOICE_COUNT; ++i)
		{
			NOTE_ON[i]=0;
			NOTE_ON_SWING[i]=0;
			NOTE_OFF[i]=0;
			NOTE_CHAN[i]=1;
		}
			 // data=&mel;
	}

	void tickMidi(){


			//PLAY UNSWINGED NOTES ON TICK


			//TEMPO CALCULATIONS
		if (_clockCounter%6==0)
		{
			tempo=tempoCalc.tick();
			tempoMillis=tempoCalc.tempoMillis;
			// noteKill();
				// swingAmount=tempoMillis/4;
		}
	}


	void playNote(byte pitch, byte velocity, int duration, byte chan)
	{
		unsigned long time = millis();

		// find an empty note slot
		boolean found_slot = false;
		for (int i=0;i<VOICE_COUNT;i++){
			if (NOTE_ON[i] == 0){
				NOTE_ON[i] = pitch;
				NOTE_OFF[i] = time+duration;
				NOTE_CHAN[i] = chan;
				found_slot = true;
				break;
			}
		}

			// // RED LIGHT SHOWS NOTE BUFFER IS OVERFULL
		if (found_slot == false){
		}
		else{
			midi -> sendNoteOn(pitch, velocity, chan);
			usbMIDI.sendNoteOn(pitch, velocity, chan);

		};
	}

	void swingNote(byte pitch, byte velocity, int duration, byte chan)
	{
		unsigned long time = millis();
		// find an empty note slot
		boolean found_slot = false;
		for (int i=0;i<VOICE_COUNT;i++){
			if (NOTE_ON[i] == 0){
				NOTE_ON[i] = pitch;
				NOTE_ON_SWING[i] = time+swingAmount;
				NOTE_OFF[i] = time+swingAmount+duration;
				NOTE_CHAN[i] = chan;
				found_slot = true;
				break;
			}
		}

			// RED LIGHT SHOWS NOTE BUFFER IS OVERFULL
		if (found_slot == false){
			//digitalWrite (7, HIGH);
		}
		else{
			//-  digitalWrite (7, LOW);
				// midi -> sendNoteOn(pitch, velocity, chan);

		};
	}


	void notesOnTick(byte step, byte note, byte velocity, byte duration, byte octave, byte chan ){
		// Serial.print("DURtick > ");
		// Serial.println(duration);
		// if ((_clockCounter % (clockDivider)) == 0 ) {
			// Serial.print("clockModulo=0ko>");
			// Serial.println(_clockCounter);

			int tempDur = duration*2;
			swing(step, note, octave, velocity, tempDur, chan);

		// }

	}  

	void noteKill()
	{
		unsigned long time=millis();
		for (int i=0;i<VOICE_COUNT;i++){
				if (NOTE_ON[i]>0 && NOTE_OFF[i]<time){  // if note value>0 and note off time < time

					byte pitch = NOTE_ON[i];
					byte velocity = 0;
					midi -> sendNoteOff(pitch, velocity, NOTE_CHAN[i]);
					usbMIDI.sendNoteOff(pitch, velocity, NOTE_CHAN[i]);
					NOTE_ON[i]=0; //wipe NOTE_ON entry to signal no active note
				}
			}
		}
		void reset()
		{
			_clockCounter=0;
	     	// data -> part_data.step=0;	
		}


		byte quantize(int note,int octave)
		{

			return octave*12+note;

		}
		void swing(int step, byte note, byte octave, byte vel, int duration, byte chan){
			if(swingAmount>0){
				if (step%2!=0)
				{
				 		// playNote(quantize(note, octave),vel,duration,chan);
					swingNote(quantize(note, octave),vel,duration,chan);

				}else {

					playNote(quantize(note, octave),vel,duration,chan);

				}

			}else{
				playNote(quantize(note, octave),vel,duration,chan);

			}



		}
		void run(){
		 	// playSwingNotes(); //RUNs ALL THE TIME

		}

		void playSwingNotes(){

					// Serial.print(NOTE_CHAN[]);

			unsigned long time=millis();
			for (int i=0;i<VOICE_COUNT;i++){
			    if (time >=  NOTE_ON_SWING[i] && NOTE_ON_SWING[i]>0  ){  // if note value>0 and note off time < time
					// Serial.print("NOTE_CHAN[i]");
					// Serial.print(NOTE_CHAN[i]);
					// delay(30);

			    	midi -> sendNoteOn(NOTE_ON[i], 127, NOTE_CHAN[i]);
			    	usbMIDI.sendNoteOn(NOTE_ON[i], 127, NOTE_CHAN[i]);
			    	NOTE_ON_SWING[i]=0;
			    }
			}
		}

      // virtual const String classname() { return "midiHandler";}



	};
