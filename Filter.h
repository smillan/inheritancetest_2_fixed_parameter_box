#include <Arduino.h>
#include "Parameter.h"
#include "Scales.h"

class Filter : public Scales {
protected:

public:
	Parameter preset;
	Parameter* parameters[1]={&preset};
			// Scales* ScaleL;
	String name="FLT";
	String shortName="";
	int tempNote[1]={0};
	int tempVel[1]={0};
	int tempDur[1]={0};
	int tempSeq=0;
	int tempOct[1]={0};
	byte returnNotes=1;

	Filter( )
	{
		String directionOptions[2]={"",""};

		preset.init("", "", "", directionOptions, directionOptions,  0, 0, 2, 1);

	}
	virtual void getNextStep ()

	{

	}
	virtual void nextStep (int step)

	{

	}
	virtual Parameter* getParameter (int param)

	{

	}
	virtual void init ()

	{

	}
	virtual void selectParameter (int param)

	{

	}
	virtual int getParameterCount(){

		int max= sizeof(parameters);
		return max;
	}

	virtual String getName(){
		return name;

	}
	virtual String getShortName(){

 		return shortName;
	}

		 // virtual Parameter* getParameter( int param){

		 //    return parameters[param];

		 //  }
		// virtual  String  getParameterName( int param){

		//     String name = parameters[param]-> name;
		//     return name;

		//   }

	virtual int getSeq(){

		return 36;
	}

	virtual void doProcessing( int *parameters, long clockCount, byte step, byte *sequence,byte *notes, byte *velocities, byte *octaves, byte *durations   ){



	}
	virtual void doProcessingSingle( int *parameters,long clockCount, byte step, byte seqStep, byte note, byte velocity, byte octave, byte duration   ){



	}

	virtual int getProcessedNote(byte n){
		return tempNote[n];
	}
	virtual byte getProcessedSeq(byte n){
		return tempSeq;

	}
	virtual byte getProcessedVelocity(byte n){
		return tempVel[n];
	}
	virtual byte getProcessedDuration(byte n){
		return tempDur[n];
	}
	virtual byte getProcessedOctave(byte n){
		return tempOct[n];
	}
	virtual byte getNoteCount(){
		return returnNotes;
	}

	virtual void tick ()

	{

	}
	 // virtual void addScales (Scales& scales)

	 //    {
	 //      ScaleL=&scales;

	 //    }


	virtual const String classname() { return "Filter";}


};