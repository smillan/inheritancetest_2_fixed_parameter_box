#include <Arduino.h>
#include "Parameter.h"
#include "Scales.h"

class Melodic : public Scales {
protected:

public:
	Parameter preset;
	Parameter* parameters[1]={&preset};
			// Scales* ScaleL;
	String name="";
	String shortName="MDC";
	Melodic( )
	{
		String directionOptions[6]={"A","b"};

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


	}
	virtual String getShortName(){


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

	virtual void generateSequence(int *parameters, byte step, byte *notes, byte *velocities, byte *durations ,byte *octaves, byte scale){



	}
	virtual void generateStep(byte step, int *parameters, byte *notes, byte *velocities, byte *durations ,byte *octaves, byte scale){



	}
	virtual void tick ()

	{

	}
	 // virtual void addScales (Scales& scales)

	 //    {
	 //      ScaleL=&scales;

	 //    }


	virtual const String classname() { return "melodic";}


};