#ifndef Xenakis_h
#define Xenakis_h
#include <Arduino.h>
#include "Parameter.h"
// #include "Scales.h"
#define chain_size 7
#define max_count 25000

#define ARRAY_SIZE 128
// #define tempo 200
#define seqlength 16

class Xenakis: public Melodic{
private:
	 // Parameter direction;
	Parameter density;
	Parameter action1;
	Parameter action2;
	Parameter sectionLength;
	Parameter minvel;
	Parameter maxvel;


	 // densitys* densityL;
public:
	Parameter* parameters[6]={ &density, &action1, &action2, &sectionLength, &minvel, &maxvel};

	Xenakis():Melodic() {
		init();
	};
	String name="WEIGHTD";
	String shortName="XNK";
	void init(){
		// String directionOptions[3]={"UP","opd","U&D"};
		String noOptions[2]={"",""};
		action1.init("ACTION 1", "AC1", true, noOptions, noOptions,  0, 0, 9, 1);
		action2.init("ACTION 2", "AC2", true, noOptions, noOptions,  0, 0, 9, 1);
		density.init("DENSITY", "DST", true, noOptions, noOptions,  100, 10, 200, 5);
		sectionLength.init("SECL", "MIV", true, noOptions, noOptions,  50, 1, 127, 5);

		minvel.init("MINVEL", "MIV", true, noOptions, noOptions,  50, 1, 127, 5);
		maxvel.init("MAXVEL", "MXV", true, noOptions, noOptions,  50, 1, 127, 5);


	}
	byte ODDS_CHOICE=0;
	int DENSITY =100; // 100 = average, 200 = low, 50 = high
	int MAX_DENSITY = 200;
	int MIN_DENSITY = 10;
	byte MIN_VELOCITY;
	byte MAX_VELOCITY;
	int LOOP_LENGTH = ARRAY_SIZE;
	int CHANGES = 0;
	byte LOOP_STABILITY = 2; // How likely individual notes are to change as they play
	long OLD;
	long NEW;
	byte NOTE_ACTION_1;
	byte NOTE_ACTION_2;
	byte LOOP_ACTION_1;
	byte LOOP_ACTION_2;
	byte LOOP_EVERYNOTE_ACTION_1;
	byte LOOP_EVERYNOTE_ACTION_2;
	#define ODDS_COUNT 6
	byte ODDS[ODDS_COUNT][ARRAY_SIZE]={
	/*
	0 = 4/4
	1 = clock divisions
	2 = samba
	3 = 3/4
	4 = cuban
	5 = bossanova
	*/
	{95,5,5,5,95,5,5,5,95,5,5,5,95,5,5,5,95,5,5,5,95,5,5,5,95,5,5,5,95,5,5,5,95,5,5,5,95,5,5,5,95,5,5,5,95,5,5,5,95,5,5,5,95,5,5,5,95,5,5,5,95,5,5,5,95,5,5,5,95,5,5,5,95,5,5,5,95,5,5,5,95,5,5,5,95,5,5,5,95,5,5,5,95,5,5,5,95,5,5,5,95,5,5,5,95,5,5,5,95,5,5,5,95,5,5,5,95,5,5,5,95,5,5,5,95,5,5,5},
	{95,5,95,5,95,5,95,5,95,5,5,5,95,5,5,5,95,5,5,5,95,5,5,5,95,5,5,5,5,5,5,5,95,5,5,5,5,5,5,5,95,5,5,5,5,5,5,5,95,5,5,5,5,5,5,5,95,95,95,95,95,95,95,95,95,5,95,5,95,5,95,5,95,5,5,5,95,5,5,5,95,5,5,5,95,5,5,5,95,5,5,5,5,5,5,5,95,5,5,5,5,5,5,5,95,5,5,5,5,5,5,5,95,5,5,5,5,5,5,5,95,95,95,95,95,95,95,95,},
	{95,5,95,5,5,95,5,95,5,95,5,5,95,5,95,5,95,5,95,5,5,95,5,95,5,95,5,5,95,5,95,5,95,5,95,5,5,95,5,95,5,95,5,5,95,5,95,5,95,5,95,5,5,95,5,95,5,95,5,5,95,5,95,5,95,5,95,5,5,95,5,95,5,95,5,5,95,5,95,5,95,5,95,5,5,95,5,95,5,95,5,5,95,5,95,5,95,5,95,5,5,95,5,95,5,95,5,5,95,5,95,5,95,5,95,5,5,95,5,95,5,95,5,5,95,5,95,5,},
	{90,20,20,90,20,20,90,20,20,90,20,20,90,20,20,90,20,20,90,20,20,90,20,20,90,20,20,90,20,20,20,20,90,20,20,90,20,20,90,20,20,90,20,20,90,20,20,90,20,20,90,20,20,90,20,20,90,20,20,90,20,20,20,20,90,20,20,90,20,20,90,20,20,90,20,20,90,20,20,90,20,20,90,20,20,90,20,20,90,20,20,90,20,20,20,20,90,20,20,90,20,20,90,20,20,90,20,20,90,20,20,90,20,20,90,20,20,90,20,20,90,20,20,90,20,20,20,20},
	{95,5,95,95,5,95,95,5,95,5,95,95,5,95,95,5,95,5,95,95,5,95,95,5,95,5,95,95,5,95,95,5,95,5,95,95,5,95,95,5,95,5,95,95,5,95,95,5,95,5,95,95,5,95,95,5,95,5,95,95,5,95,95,5,95,5,95,95,5,95,95,5,95,5,95,95,5,95,95,5,95,5,95,95,5,95,95,5,95,5,95,95,5,95,95,5,95,5,95,95,5,95,95,5,95,5,95,95,5,95,95,5,95,5,95,95,5,95,95,5,95,5,95,95,5,95,95,5,},
	{95,5,5,95,5,5,95,5,5,5,95,5,5,95,5,5,95,5,5,95,5,5,95,5,5,5,95,5,5,95,5,5,95,5,5,95,5,5,95,5,5,5,95,5,5,95,5,5,95,5,5,95,5,5,95,5,5,5,95,5,5,95,5,5,95,5,5,95,5,5,95,5,5,5,95,5,5,95,5,5,95,5,5,95,5,5,95,5,5,5,95,5,5,95,5,5,95,5,5,95,5,5,95,5,5,5,95,5,5,95,5,5,95,5,5,95,5,5,95,5,5,5,95,5,5,95,5,5,}};



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

	// void addRandomNoteAt(byte step, int *parameters, byte *notes, byte *velocities, byte *durations ,byte *octaves, byte scale){
	// 	if (velocities[step] == 0){
	// 		if(random(parameters[0])<ODDS[ODDS_CHOICE][step]){
	// 			int nScaleNotes=scaleList[scale].count;
	// 			// notes[i]=scaleList[currentScale].notes[i%nScaleNotes];
	// 			// notes[i]=scaleList[currentScale].notes[(128-i)%nScaleNotes];
	// 			byte newnote=scaleList[scale].notes[random(12)%nScaleNotes];
	// 			byte newoctave = random(5)+3;
	// 			notes[step]= newnote; // note
	// 			octaves[step]= newoctave;  // octave
	// 			velocities[step]= random(ODDS[ODDS_CHOICE][step]+27); // velocity
	// 			durations[step] = random(100); // duration

	// 		}
	// 	}
	// }


	// void changeRandomNoteAt(byte step, int *parameters, byte *notes, byte *velocities, byte *durations ,byte *octaves, byte scale){
	// 	if (step<ARRAY_SIZE
	// 		&& velocities[step] > parameters[4]
	// 		&& velocities[step] <= parameters[5]){
	// 		if(random(parameters[0])<ODDS[ODDS_CHOICE][step]){
	// 			int nScaleNotes=scaleList[scale].count;
	// 			byte newnote=scaleList[scale].notes[random(12)%nScaleNotes];
	// 			byte newoctave = random(5)+3;
	// 			notes[step]= newnote; // note
	// 			octaves[step]= newoctave;  // octave
	// 			velocities[step]= random(ODDS[ODDS_CHOICE][step]+27); // velocity
	// 			durations[step]= random(100); // duration

	// 		}
	// 	}
	// }

	// void incrementNoteAt(byte step, int *parameters, byte *notes, byte *velocities, byte *durations ,byte *octaves, byte scale){
	// 	if ( velocities[step] > 0 ){
	// 		int nScaleNotes=scaleList[scale].count;

	// 		for (int i = 0; i < nScaleNotes; ++i)
	// 		{
	// 			if (notes[step]>=scaleList[scale].notes[i])
	// 			{
	// 				notes[step] = scaleList[scale].notes[(i+1)%nScaleNotes];
	// 				break;
	// 			}
	// 		}
	// 			// notes[step]=scaleList[scale].notes[random(12)%nScaleNotes];
	// 			// notes[step]=notes[step]%7;
	// 	}
	// }
	// void decrementNoteAt(byte step, int *parameters, byte *notes, byte *velocities, byte *durations ,byte *octaves, byte scale){
	// 	if ( velocities[step] > 0 ){
	// 		int nScaleNotes=scaleList[scale].count;

	// 		for (int i = 0; i < nScaleNotes; ++i)
	// 		{
	// 			if (notes[step]>=scaleList[scale].notes[i])
	// 			{
	// 				notes[step] = scaleList[scale].notes[(i-1)%nScaleNotes];
	// 				break;
	// 			}
	// 		}
	// 			// notes[step]=scaleList[scale].notes[random(12)%nScaleNotes];
	// 			// notes[step]=notes[step]%7;
	// 	}
	// }
	// void simplifyNoteAt(byte step, int *parameters, byte *notes, byte *velocities, byte *durations ,byte *octaves, byte scale){
	// 	if(ODDS[ODDS_CHOICE][step]>50){
	// 		notes[step] = 0;
	// 		octaves[step] = 5;
	// 		velocities[step] = 70;
	// 		durations[step]= 100;
	// 	}
	// 	else{
	// 		notes[step] = 0;
	// 		octaves[step] = 4;
	// 		velocities[step] = 40;
	// 		durations[step]= 50;
	// 	}

	// }
	// void repeatNoteBefore(byte step, int *parameters, byte *notes, byte *velocities, byte *durations ,byte *octaves, byte scale){
	// 	if (step > 1){
	// 		for (int i=step-1; i>=0;i--){
	// 			if(velocities[i]>0){
	// 				notes[step]=notes[i];
	// 				velocities[step]=velocities[i];
	// 				durations[step]=durations[i];
	// 				octaves[step]=octaves[i];
	// 				break;
	// 			}
	// 		}
	// 	}
	// }
	// void addRepeatedNote(byte step, int *parameters, byte *notes, byte *velocities, byte *durations ,byte *octaves, byte scale){
	// 	if (step > 1){
	// 		for (int i=step-1; i>=0;i--){
	// 			if(velocities[i]>0){
	// 				if(random(DENSITY)<ODDS[ODDS_CHOICE][step]){
	// 					notes[step]= notes[i]; // note
	// 					octaves[step]= octaves[i];  // octave
	// 					velocities[step]= random(ODDS[ODDS_CHOICE][step]+27); // velocity
	// 					durations[note_position]= durations;
	// 				}
	// 			}
	// 			break;
	// 		}
	// 	}
	// }
	// void drunkenRepeat(byte step, int *parameters, byte *notes, byte *velocities, byte *durations ,byte *octaves, byte scale){
	// 	if (step > 1){
	// 		for (int i=step-1; i>=0;i--){
	// 			if(velocities[i]>0){
	// 				if(random(DENSITY)<ODDS[ODDS_CHOICE][step]){
	// 			    notes[step]= notes[i]+random(3)-1; // note
	// 				    if (notes[step] == 255){
	// 				    	notes[step] = 7;
	// 				    }

	// 			    	if (notes[step]>7){
	// 				    	notes[step] = 0;
	// 				    	octaves[step]++;}
	// 				    	if (octaves[step] > 8){
	// 				    		octaves[step] = 3;
	// 				    	}

	// 					    octaves[step]= octaves[i];  // octave
	// 					    velocities[step]= velocities[i]; // velocity
	// 					    durations[step]= durations[i];
	// 					}
	// 				}
	// 			}
	// 		break;
	// 		}
	// 	}
	// }
	void generateSequence(int *parameters, byte step, byte *notes, byte *velocities, byte *durations ,byte *octaves, byte scale){
		// LOOP_ACTION_1 = random(SECTION_ACTIONS_COUNT);
		// LOOP_ACTION_2 = random(SECTION_ACTIONS_COUNT);
		// byte loopL=parameters[3];
		// for (int i = 0; i < loopL-1; ++i)
		// {
		// 	selectSectionAction(LOOP_ACTION_1, random(loopL));
		// 	selectSectionAction(LOOP_ACTION_2, random(loopL));
		// }
		// for (int x = 0; x < loopL; x++){
		// 	selectNoteAction(parameters[1], x);
		// 	selectNoteAction(parameters[2], x);
		// }
		// defineActions();
	}

	void clearNote(int *parameters, byte step, byte *notes, byte *velocities, byte *durations ,byte *octaves, byte scale){
		if (velocities[step] > parameters[4] && velocities[step] <= parameters[5]){
			velocities[step] = 0;
		}
	}
	void generateStep(byte step, int *parameters, byte *notes, byte *velocities, byte *durations ,byte *octaves, byte scale){





	}

	// #define SECTION_ACTIONS_COUNT 13
	// void selectSectionAction(byte choice, byte step, byte *notes, byte *velocities, byte *durations ,byte *octaves, byte scale){
	// 	switch (choice){
	// 		case 0:
	// 		addRandomNoteAt(step, notes, velocities, durations, scale);
	// 		Serial.print(" add ");
	// 		break;
	// 		case 1:
	// 		changeRandomNoteAt(step, notes, velocities, durations, scale );
	// 		Serial.print(" change ");
	// 		break;
	// 		case 2:
	// 		incrementNoteAt(step, notes, velocities, durations, scale );
	// 		Serial.print(" up ");
	// 		break;
	// 		case 3:
	// 		decrementNoteAt(step, notes, velocities, durations, scale );
	// 		Serial.print(" down ");
	// 		break;
	// 		case 4:
	// 		addRepeatedNote(step, notes, velocities, durations, scale );
	// 		Serial.print(" repeat ");
	// 		break;
	// 		case 5:
	// 		simplifyNoteAt(step, notes, velocities, durations, scale );
	// 		Serial.print(" simplify ");
	// 		break;
	// 		case 6:
	// 		ODDS_CHOICE = random(ODDS_COUNT);
	// 		Serial.print(" re-rhythm ");
	// 		break;
	// 		case 7:
	// 		// fillRandom();
	// 		Serial.print (" fill ");
	// 		break;
	// 		case 8:
	// 		freeze();
	// 		Serial.print (" freeze ");
	// 		break;
	// 		case 9:
	// 		clearNote(step, notes, velocities, durations, scale );
	// 		Serial.print (" CLR ");
	// 		break;
	// 		case 10:
	// 		clearNote(step, notes, velocities, durations, scale );
	// 		Serial.print (" CLRhi ");
	// 		break;
	// 		case 11:
	// 		clearNote(step, notes, velocities, durations, scale );
	// 		Serial.print (" CLRlo ");
	// 		break;
	// 		case 12:
	// 		drunkenRepeat(step, notes, velocities, durations, scale );
	// 		Serial.print (" Drunken ");
	// 		break;
	// 		default:
	// 		Serial.print (".");
	// 		break;
	// 	}
	// }
		// #define NOTE_ACTIONS_COUNT 9
		// void selectNoteAction(byte choice, byte step, byte *notes, byte *velocities, byte *durations ,byte *octaves, byte scale){

		// 	switch (choice){
		// 		case 0:
		// 		addRandomNoteAt(step, notes, velocities, durations, scale );
		// 		Serial.print(" Nadd ");
		// 		break;
		// 		case 1:
		// 		changeRandomNoteAt(step, notes, velocities, durations, scale );
		// 		Serial.print(" Nchange ");
		// 		break;
		// 		case 2:
		// 		incrementNoteAt(step, notes, velocities, durations, scale );
		// 		Serial.print(" Nup ");
		// 		break;
		// 		case 3:
		// 		decrementNoteAt(step, notes, velocities, durations, scale );
		// 		Serial.print(" Ndown ");
		// 		break;
		// 		case 4:
		// 		addRepeatedNote(step, notes, velocities, durations, scale );
		// 		Serial.print(" Nrepeat ");
		// 		break;
		// 		case 5:
		// 		simplifyNoteAt(step, notes, velocities, durations, scale );
		// 		Serial.print(" Nsimplify ");
		// 		break;
		// 		case 6:
		// 		changeRandomNoteAt(step, notes, velocities, durations, scale );
		// 		Serial.print(" NchngHI ");
		// 		break;
		// 		case 7:
		// 		changeRandomNoteAt(step, notes, velocities, durations, scale );
		// 		Serial.print (" NchngLO ");
		// 		break;
		// 		case 8:
		// 		drunkenRepeat(step, notes, velocities, durations, scale );
		// 		Serial.print (" Drunken ");
		// 		break;
		// 		default:
		// 		Serial.print (".");
		// 		break;
		// 	}
		// }
		

		virtual const String classname() { return "Xenakis";}

	};
#endif