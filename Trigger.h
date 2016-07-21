#include <Arduino.h>
#ifndef Trigger_h
#define Trigger_h
class Trigger  {

protected:


public:
	String name="TRIG";
	String shortName="TRG";
	Parameter preset;
	Parameter* parameters[1]={&preset};
	int test = 0;
	Trigger( )
	{

	}
	void init(){


		
	}
	virtual void getNextStep ()
	{

	}
	virtual void generateSequence(int *parameters, byte *triggers){



	}
	virtual void generateStep(byte step, int *parameters, byte *triggers){



	}
	virtual Parameter* getParameter (int param)

	{

	}

	virtual int getParameterCount(){
		int max= sizeof(parameters) / sizeof(parameters[ 0 ]);
		return max;
	}
	virtual String getName(){


	}
	virtual String getShortName(){


	}

	virtual const String classname() { return "trigger";}

};
#endif