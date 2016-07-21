#ifndef Modulo_h
#define Modulo_h
#include <Arduino.h>
#include "Parameter.h"
// #include "Scales.h"

class Modulo: public Filter,  public Chords{
private:
	 // Parameter direction;
	Parameter steps;
	Parameter offset;
	Parameter repeater;
	Parameter times;


	 // Scales* scaleL;
public:
	Parameter* parameters[4]={&steps, &repeater, &offset,&times};

	Modulo():Filter() {
		init();
	};
	String name="MOD";
	String shortName="MOD";
	void init(){
		String no[2]={"",""};
		// String noOptions[2]={"",""};
		steps.init("STPS", "NOT", true, no, no,  1, 1, 128, 1);
		offset.init("RAND", "RND", true, no, no,  0, 0, 128, 1);
		repeater.init("RPEAT", "REP", true, no, no,  1, 1, 17, 1);
		times.init("TIMES", "TMS", true, no, no,  1, 1, 64, 1);


	}
	int tempNote[4]={0,0,0,0};
	byte tempVel[4]={0,0,0,0};
	byte tempDur[4]={0,0,0,0};
	byte tempOct[4]={0,0,0,0};
	int tempSeq;
	byte repeat=0;
	byte timesC=0;


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





	void doProcessing(int *parameters, long clockCount, byte step, byte *sequence, byte *notes, byte *velocities,byte *octaves, byte *durations){

		tempNote[0]= notes[step];
		tempSeq=sequence[step];
		tempVel[0]=velocities[step];
		tempDur[0]=durations[step];
		tempOct[0]=octaves[step];
		if (step%(parameters[0])==0) {repeat=0; timesC++;};
		if (timesC%parameters[3]==0 && repeat<parameters[1] && random(0,128)>parameters[2])
				{
					// Serial.println(step);
					// Serial.print("modB");
					// Serial.println(parameters[0]);
					tempSeq=sequence[step];
					repeat++;
				}
				else
				{
					tempSeq=0;
				}	
		// if( ){ 
			
				

		// 		// tempSeq=sequence[step];	
		// }else{
			
		// 		// tempSeq=0;


		// }
		







	}
	void doProcessingSingle( int *parameters, long clockCount, byte step, byte seqStep,  byte note, byte velocity,byte octave, byte duration   ){
		tempNote[0] = note;
		tempSeq=seqStep;
		tempVel[0]=velocity;
		tempDur[0]=duration;
		tempOct[0]=octave;
		if ( step % ( parameters[0]*parameters[3])==0 ) repeat=0;

			if ( repeat<parameters[1] && random(0,128)>parameters[2] )
			{
				tempSeq=seqStep;
				repeat++;
			}
			else
			{
				tempSeq=0;
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
	byte getProcessedDuration(byte n){
		return tempDur[n];
	}
	byte getProcessedOctave(byte n){
		return tempOct[n];
	}
	byte getNoteCount(){
		return returnNotes;
	}
	// virtual const String classname() { return "Modulo";}

};
#endif