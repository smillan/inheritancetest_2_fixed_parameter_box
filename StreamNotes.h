#include <Arduino.h>

class StreamNotes: public Trigger{
public:
	Parameter grid;
	Parameter* parameters[1]={&grid};

	String name="STRM";
	String shortName="STR";

	StreamNotes():Trigger() { 
		init();
	}
	int test=0;

	void getNextStep ()
	{
				 // cout << "Rectangle class area :" <<endl;
		// Serial.println("Stream");

	}
	void init(){
		String no[2]={"",""};

		grid.init("GRID", "GRD", true, no, no,  0, 0, 6, 1);


	}
	int getParameterCount(){
		int max= sizeof(parameters) / sizeof(parameters[ 0 ]);
		return max;
	}
	Parameter* getParameter( int param){
		return parameters[param];
	}

	void generateSequence(int *parameters, byte *triggers){



	}
	void generateStep(int *parameters, byte *triggers){



	}
	String getName ()
	{
		return name;
	}
	String getShortName ()
	{
		return shortName;
	}
};