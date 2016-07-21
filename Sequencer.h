#include <Arduino.h>

class Sequencer: public Trigger{
public:
	Parameter grid;
	Parameter divisionup;
	Parameter division;
	Parameter* parameters[3]={&grid,&division,&divisionup};

	String name="SEQUNCR";
	String shortName="SEQ";

	Sequencer():Trigger() {
		init();
	 }
	int test=0;


	void getNextStep ()
	{
		// cout << "Rectangle class area :" <<endl;
	}

	void init(){

		String no[2]={"",""};
		grid.init("GRID", "GRD", true, no, no,  1, 1, 16, 1);
		division.init("DIV UP", "DV-", true, no, no,  1, 1, 64, 1);
		divisionup.init("DIV DOWN", "DV+", true, no, no,  1, 1, 64, 1);


	}
	int getParameterCount(){
		int max= sizeof(parameters) / sizeof(parameters[ 0 ]);
		return max;
	}

	Parameter* getParameter( int param){
		return parameters[param];
	}

	virtual void generateSequence(int *parameters, byte *triggers){
		for (int i = 0; i < 128; ++i)
		{
			int divi;
			// trackIn->generateMelodic();
			if (i%parameters[0])
			{
				divi=random(parameters[1],parameters[2]);
			}
			if ( i%divi  )
			{
				triggers[i]=1;

			}else{

				triggers[i]=0;


			}
			
		}


	}
	virtual void generateStep(byte step, int *parameters, byte *triggers){



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