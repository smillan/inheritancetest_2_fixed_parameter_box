#ifndef Transpose_h
#define Transpose_h
#include <Arduino.h>
#include "Parameter.h"
// #include "Scales.h"

class Transpose: public Filter{
private:
	 // Parameter direction;
	Parameter note;
	Parameter octave;


	 // Scales* scaleL;
public:
	Parameter* parameters[2]={&note, &octave};

	Transpose():Filter() {
		init();
	};
	String name="TRNSPS";
	String shortName="TRP";
	void init(){
		String no[2]={"",""};
		// String noOptions[2]={"",""};
		note.init("NOTE", "NOT", true, no, no,  0, 0, 128, 1);
		octave.init("OCTV", "OCT", true, no, no,  0, 0, 6, 1);


	}
	int tempNote[3];
	int tempVel[3];
	int tempDur[3];
	int tempSeq[3];
;

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

	int doProcessing(int *parameters, long clockCount, byte step, byte *notes, byte *velocities, byte *durations ){

		 tempNote[0] = notes[step];

		return 1;
		// velocities[i]=127;
		// durations[step]=100;
	

	}

	int doProcessingSingle( int *parameters,long clockCount, byte step, byte note, byte velocity, byte duration   ){

		int temp=note;
		if (temp<parameters[2]) temp=parameters[2];
		if (temp>parameters[3]) temp=parameters[3];
		temp+=parameters[0];
		temp+=(parameters[1]*12);
		tempNote[0]=temp;
		return 1;

	}


	int getProcessedNote(byte n){
		return tempNote[n];
	}
	byte getProcessedSeq(byte n){
		return tempSeq[n];

	}
	byte getProcessedVelocity(byte n){
		return tempVel[n];
	}
	byte getProcessedDurations(byte n){
		return tempDur[n];
	}

	const String classname() { return "Transpose";}

};
#endif