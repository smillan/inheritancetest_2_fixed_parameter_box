#ifndef Arpeggio_h
#define Arpeggio_h
#include <Arduino.h>
#include "Parameter.h"
// #include "Scales.h"

class Arpeggio: public Melodic{
private:
	Parameter direction;
	Parameter offset;
	Parameter size;
	Parameter velmode;
	Parameter durmode;
	Parameter octmode;

	 // Scales* scaleL;
public:
	Parameter* parameters[6]={&direction, &size, &offset ,&velmode,&durmode, &octmode};

	Arpeggio():Melodic() {
		init();
	};
	String name="ARP";
	String shortName="ARP";
	void init(){
		String no[2]={"",""};
		String directionOptions[6]={"UP","DWN","U&D","BCK","RND","QRT"};
		direction.init("DIRECTION", " > ", false, directionOptions, directionOptions,  0, 0, 6, 1);
		size.init("SIZE", "<_>", true, no, no,  1, 1, 17, 1);
		offset.init("OFFST", " | ", true, no, no,  0, 0, 11, 1);
		velmode.init("VELOCITY", "V  ", true, no, no,  0, 0, 128, 1);
		durmode.init("DURATION", "D  ", true, no, no,  0, 0, 255, 1);
		octmode.init("OCTAVE", "O  ", true, no, no,  0, 0, 18, 1);


	}

			// directio.setParameter("DIR", "STR", 0,1);
			// void setParameter(byte param, int value){
			// 	 parameters[param]->value=value;

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
	void setDuration (byte mode)
	{


	}
	void setVelocity (byte mode)
	{


	}
	byte setOctave (byte mode, byte original,byte count)
	{
		 byte octmp=original;
			switch(mode){


				case 1:
					octmp=(original+count)%1;
					break;
				case 2:
					octmp=(original+count)%2;
					break;
				case 3:
					octmp=(original+count)%3;
					break;
				case 4:
					octmp=(original+count)%4;
					break;
				case 5:
					octmp=(original-count)%1;
					break;
				case 6:
					octmp=(original-count)%2;
					break;
				case 7:
					octmp=(original-count)%3;
					break;
				case 8:
					octmp=(original-count)%4;
					break;
				case 9:
					octmp=original+(random(0,1));
					break;
				case 10:
					octmp=original+(random(0,2));
					break;
				case 11:
					octmp=original+(random(0,3));
					break;
				case 12:
					octmp=original+(random(0,4));
					break;
				case 13:
					octmp=original-(random(0,1));
					break;
				case 14:
					octmp=original-(random(0,2));
					break;
				case 15:
					octmp=original-(random(0,3));
					break;
				case 16:
					octmp=original-(random(0,4));
					break;
				case 17:
					octmp=original-(random(0,4));
					break;

				default:
					break;
			}
			return octmp;


	}
	byte setVelocity (byte mode, byte original,byte count)
	{
		 byte veltmp=original;
			switch(mode){


				case 0:
					veltmp=100;
					break;
				case 1:
					veltmp=127;
					break;
				case 2:
					veltmp=127-random(0,40);
					break;
				case 3:
					veltmp=random(40,100);
					break;
				case 4:
					veltmp=random(100,127);
					break;
				

				default:
					veltmp=mode;
					break;
			}
			return veltmp;


	}

	byte setDuration (byte mode, byte original, byte count)
	{
		 byte durTmp=original;
			switch(mode){
				case 0:
					durTmp=10;
					break;
				case 1:
				//SHORT
					durTmp=50;
					break;
				case 2:
					durTmp=80;
					break;
				case 3:
					durTmp=100;
					break;
				case 4:
					durTmp=random(10, 20);
					break;
				case 5:
					durTmp=original+random(20, 80);
					break;
				case 6:
					durTmp=original+random(80, 200);
					break;


				default:
					durTmp = 20+(mode);
					break;
			}
			return durTmp;


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

	void generateSequence(int *parameters, byte step, byte *notes, byte *velocities, byte *durations ,byte *octaves, byte scale){

		byte currentScale=scale;
		int mode = parameters[0];
		int size = parameters[1];
		int offs = parameters[2];

		switch( mode){
			//UP
			case 0:
			for (int i = 0; i < 128; ++i)
			{

				int nScaleNotes=scaleList[currentScale].count;
				// notes[i]=scaleList[currentScale].notes[i%nScaleNotes];
				byte tempnote=((offs+i)%size)%nScaleNotes;
				notes[i]=scaleList[currentScale].notes[tempnote];
				velocities[i]=setVelocity(parameters[3], velocities[step], i);
				// durations[i]=random(50, 50);
				octaves[i]=setOctave(parameters[5], octaves[step], i);
				durations[i]=setDuration(parameters[4], durations[step], i);

			}
			break;
			//DOWN
			case 1:
			for (int i = 0; i < 128; ++i)
			{

				int nScaleNotes=scaleList[currentScale].count;

				byte tempnote=((12-(offs+i))%size)%nScaleNotes;

				notes[i]=scaleList[currentScale].notes[tempnote];
				velocities[i]=setVelocity(parameters[3], velocities[step], i);
				// durations[i]=random(50, 50);
				octaves[i]=setOctave(parameters[5], octaves[step], i);
				durations[i]=setDuration(parameters[4], durations[step], i);



			}
			break;
			// upNDown
			case 2:
			for (int i = 0; i < 64; ++i)
			{

				int nScaleNotes=scaleList[currentScale].count;
				// notes[i]=scaleList[currentScale].notes[i%nScaleNotes];
				notes[i]=scaleList[currentScale].notes[(i)%nScaleNotes];
				velocities[i]=setVelocity(parameters[3], velocities[step], i);
				// durations[i]=random(50, 50);
				octaves[i]=setOctave(parameters[5], octaves[step], i);
				durations[i]=setDuration(parameters[4], durations[step], i);




			}
			for (int i = 64; i < 128; ++i)
			{

				int nScaleNotes=scaleList[currentScale].count;
				// notes[i]=scaleList[currentScale].notes[i%nScaleNotes];
				notes[i]=scaleList[currentScale].notes[(128-i)%nScaleNotes];
				velocities[i]=setVelocity(parameters[3], velocities[step], i);
				durations[i]=random(50, 50);
				// octaves[i]=random(3, 8);
				octaves[i]=setOctave(parameters[5], octaves[step], i);
				durations[i]=setDuration(parameters[4], durations[step], i);
				//



			}
			break;
			//RAND
			case 3:
			for (int i = 0; i < 128; ++i)
			{

				int nScaleNotes=scaleList[currentScale].count;
				// notes[i]=scaleList[currentScale].notes[i%nScaleNotes];
				notes[i]=scaleList[currentScale].notes[(random(offs,size+offs))%nScaleNotes];
				velocities[i]=setVelocity(parameters[3], velocities[step], i);
				// durations[i]=random(50, 50);
				octaves[i]=setOctave(parameters[5], octaves[step], i);
				durations[i]=setDuration(parameters[4], durations[step], i);




			}
			break;
			//DEFAULT
			default:
			for (int i = 0; i < 128; ++i)
			{

				int nScaleNotes=scaleList[currentScale].count;
				// notes[i]=scaleList[currentScale].notes[i%nScaleNotes];
				notes[i]=scaleList[currentScale].notes[(random(0,size))%nScaleNotes];
				velocities[i]=setVelocity(parameters[3], velocities[step], i);
				// durations[i]=random(50, 50);
				octaves[i]=setOctave(parameters[5], octaves[step], i);
				durations[i]=setDuration(parameters[4], durations[step], i);




			}
			break;

		}



	}
	void generateStep(int *parameters, byte step, byte *notes, byte *velocities, byte *durations ,byte *octaves, byte scale){

		byte currentScale=scale;
		int mode = parameters[0];
		int size = parameters[1];
		int offs = parameters[2];

		switch( mode){
			case 0:
			for (int i = step; i < 32+step; ++i)
			{

				int nScaleNotes=scaleList[currentScale].count;
				// notes[i]=scaleList[currentScale].notes[i%nScaleNotes];
				byte tempnote=((offs+i)%size)%nScaleNotes;
				notes[i]=scaleList[currentScale].notes[tempnote];
				velocities[i]=setVelocity(parameters[3], velocities[step], i);
				// durations[i]=random(50, 50);
				octaves[i]=setOctave(parameters[5], octaves[step], i);
				durations[i]=setDuration(parameters[4], durations[step], i);

			}
			break;
			case 1:
			for (int i = step; i < 32+step; ++i)
			{

				int nScaleNotes=scaleList[currentScale].count;

				byte tempnote=((12-(offs+i))%size)%nScaleNotes;

				notes[i]=scaleList[currentScale].notes[tempnote];
				velocities[i]=setVelocity(parameters[3], velocities[step], i);
				// durations[i]=random(50, 50);
				octaves[i]=setOctave(parameters[5], octaves[step], i);
				durations[i]=setDuration(parameters[4], durations[step], i);



			}
			break;
			case 2:
			for (int i = step; i <32+step; ++i)
			{

				int nScaleNotes=scaleList[currentScale].count;
				// notes[i]=scaleList[currentScale].notes[i%nScaleNotes];
				notes[i]=scaleList[currentScale].notes[(i)%nScaleNotes];
				velocities[i]=setVelocity(parameters[3], velocities[step], i);
				// durations[i]=random(50, 50);
				octaves[i]=setOctave(parameters[5], octaves[step], i);
				durations[i]=setDuration(parameters[4], durations[step], i);




			}
			for (int i = step; i < 32+step; ++i)
			{

				int nScaleNotes=scaleList[currentScale].count;
				// notes[i]=scaleList[currentScale].notes[i%nScaleNotes];
				notes[i]=scaleList[currentScale].notes[(128-i)%nScaleNotes];
				velocities[i]=setVelocity(parameters[3], velocities[step], i);
				durations[i]=random(50, 50);
				// octaves[i]=random(3, 8);
				octaves[i]=setOctave(parameters[5], octaves[step], i);
				durations[i]=setDuration(parameters[4], durations[step], i);
				//



			}
			break;
			default:
			for (int i = step; i < 32+step; ++i)
			{

				int nScaleNotes=scaleList[currentScale].count;
				// notes[i]=scaleList[currentScale].notes[i%nScaleNotes];
				notes[i]=scaleList[currentScale].notes[(random(0,18))%nScaleNotes];
				velocities[i]=setVelocity(parameters[3], velocities[step], i);
				// durations[i]=random(50, 50);
				octaves[i]=setOctave(parameters[5], octaves[step], i);
				durations[i]=setDuration(parameters[4], durations[step], i);




			}
			break;

		}



	}
	virtual const String classname() { return "arpeggio";}

};
#endif