#ifndef Clamp_h
#define Clamp_h
#include <Arduino.h>
#include "Parameter.h"
// #include "Scales.h"

class Clamp: public Filter{
private:
	 // Parameter direction;
	Parameter max;
	Parameter min;
	Parameter transN;
	Parameter transO;
	// Parameter c;
	// Parameter offset;


	 // Scales* scaleL;
public:
	Parameter* parameters[4]={&transN,&transO, &min, &max };
	int tempNote[4]={0,0,0,0};
	int tempVel[4]={0,0,0,0};
	int tempDur[4]={0,0,0,0};
	int tempOct[4]={0,0,0,0};
	int tempSeq;
	byte returnNotes=3;

	Clamp():Filter() {
		init();
	};
	String name="MULTI";
	String shortName=" > ";
	void init(){
		String no[2]={"",""};
		// String mods[2]={"MAX","MIN","TRS"};
		// String noOptions[2]={"",""};
		transN.init("TRANSNOTE", "TRN", true, no, no,  0, -12, 12, 1);
		transO.init("TRANSOCTV", "TRO", true, no, no,  0, -4, 8, 1);
		min.init("MIN", "MIN", true, no, no,  0, 0, 128, 1);
		max.init("MAX", "MAX", true, no, no,  127, 0, 128, 1);
		// offset.init("OFFST", "OFS", true, no, no,  0, 0, 128, 1);


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
		
		int temp=notes[step];
		byte tempO=octaves[step];
		if (temp<parameters[2]) temp=parameters[2];
		if (temp>parameters[3]) temp=parameters[3];
		temp+=parameters[0];
		// temp+=(parameters[1]);
		tempOct[0]=tempO+(parameters[1]);
		tempNote[0]=temp;
		tempSeq=sequence[step];
		tempVel[0]=velocities[step];
		tempDur[0]=durations[step];
		// return temp;
		// velocities[i]=127;
		// durations[step]=100;


	}
void doProcessingSingle( int *parameters, long clockCount, byte step, byte seqStep, byte note, byte velocity,byte octave, byte duration   ){

		int temp=note;
		byte tempO=octave;

		if (temp<parameters[2]) temp=parameters[2];
		if (temp>parameters[3]) temp=parameters[3];
		temp+=parameters[0];
		tempOct[0]=tempO+(parameters[1]);
		tempNote[0]=temp;
		tempSeq=seqStep;
		tempVel[0]=velocity;
		tempDur[0]=duration;

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

	const String classname() { return "Clamp";}

};
#endif