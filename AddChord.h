#ifndef AddChord_h
#define AddChord_h
#include <Arduino.h>
#include "Parameter.h"
#include "Chords.h"

// #include "Scales.h"

class AddChord: public Filter{
private:
	 // Parameter direction;
	Parameter chord;
	Parameter density;
	Parameter randomness;
	Parameter maxvel;
	Chords chords;
	int tempNote[4]={0,0,0,0};
	int tempVel[4]={0,0,0,0};
	int tempDur[4]={0,0,0,0};
	int tempSeq;
	 // Scales* scaleL;
public:
	Parameter* parameters[4]={&chord, &density, &randomness, &maxvel};
	byte returnNotes=3;


	AddChord():Filter() {
		init();
	};
	String name="CHRD";
	String shortName="CHD";
	void init(){
		String no[2]={"",""};
		// String noOptions[2]={"",""};
		chord.init("CHRD", shortName, true, no, no,  0, 0, 14, 1);
		density.init("DNSITY", "DST", true, no, no,  127, 0, 128,1);
		randomness.init("RNDM", "RND", true, no, no,  0,  0, 128, 1);
		maxvel.init("MAXVEL", "NVL", true, no, no,  0,  0, 127, 1);


	}

			// directio.setParameter("DIR", "STR", 0,1);
			// void setParameter(byte param, int value){
			//   parameters[param]->value=value;

			// }

	Parameter* getParameter( int param){
		return parameters[param];
	}

	int getParameterCount(){
		int max= sizeof(parameters) / sizeof(parameters[ 0 ]);
		return max;
	}


	void selectParameter (int option)
	{


	}



	void getNextStep ()
	{

	}

	String getName ()
	{
		return name;
	}
	String getShortName ()
	{
		return shortName;
	}

	void nextStep (int step)
	{

	}




	int getSeq(){

		return 36;
	}

	void doProcessing(int *parameters, long clockCount, byte step, byte *sequence, byte *notes, byte *velocities,byte *octaves, byte *durations){

		tempNote[0]= notes[step];
		tempSeq=sequence[step];
		tempVel[0]=velocities[step];
		tempDur[0]=durations[step];
		tempOct[0]=octaves[step];
		// byte chord = random(0,13);
		byte temp=parameters[0]+random(0, parameters[2]);
		byte chord = temp%13;
		for (int i = 1; i <4 ; ++i)
		{
			byte noteChord=chords.getChordList(chord, i);
			if (noteChord==0) break;

			byte temp = notes[step]+noteChord;
			tempNote[i]=temp;
			tempSeq=sequence[step];
			tempVel[i]=velocities[step];
			tempOct[i]=octaves[step];
			tempDur[i]=durations[step]+100;
			// Serial.println("---inproc---");
 		// 	Serial.print("nnot > ");
			// Serial.println(i);
			// Serial.print("note > ");
			// Serial.println(tempNote[i]);
			// Serial.println("seq");
			// Serial.println(tempSeq);
			// Serial.println("------");
		}

		// return notes[step]+parameters[3];
		// velocities[i]=127;
		// durations[step]=100;


	}
	void doProcessingSingle( int *parameters, long clockCount, byte step, byte seqStep, byte note, byte velocity,byte octave, byte duration   ){
		
		// byte chord = random(0,13);

		byte temp=parameters[0]+random(0, parameters[2]);
		byte chord = temp%13;
		if (random(0, 128)<parameters[1])
		{
			tempNote[0] = note;
			tempSeq=step;
			tempVel[0]=velocity;
			tempOct[0]=octave;
			tempDur[0]=duration;
			for (int i = 1; i <4; ++i)
			{	
				byte noteChord=chords.getChordList(chord, i);
				if (noteChord==0 ) break;
				byte temp = note+noteChord;
				tempNote[i]=temp;
				tempSeq=seqStep;
				tempVel[i]=velocity;
				tempOct[i]=octave;
				tempDur[i]=duration+100;
			}
		}else{
			tempNote[0] = note;
			tempSeq=seqStep;
			tempVel[0]=parameters[3];
			tempDur[0]=duration;
			for (int i = 1; i <4; ++i)
			{	byte noteChord=chords.getChordList(chord, i);
				if (noteChord==0 ) break;
				byte temp = note+noteChord;
				tempNote[i]=note;
				tempSeq=seqStep;
				tempVel[i]=0;
				tempDur[i]=0;
				tempOct[i]=octave;
				
			}
		}
		
	}


	int getProcessedNote(byte n){
		return tempNote[n];
	}
	byte getProcessedSeq(byte n){
		return tempSeq;
	}
	byte getProcessedVelocity(byte n){
		return tempVel[n];
	}
	byte getProcessedOctave(byte n){
		return tempOct[n];
	}
	byte getProcessedDuration(byte n){
		return tempDur[n];
	}
	byte getNoteCount(){
		return returnNotes;
	}
	const String classname() { return "AddChord";}

};
#endif