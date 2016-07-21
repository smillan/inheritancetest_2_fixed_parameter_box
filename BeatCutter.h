#ifndef BeatCutter_h
#define BeatCutter_h
#include <Arduino.h>
#include "Parameter.h"
// #include "Scales.h"

class BeatCutter: public Filter{
private:
	 // Parameter direction;



	Parameter p_maxPhraselength;
	Parameter p_repeatChance;
	Parameter p_unitsInCut;
	Parameter p_maxRepeats;

	 // Scales* scaleL;
public:
	Parameter* parameters[4]={&p_maxPhraselength, &p_repeatChance, &p_unitsInCut, &p_maxRepeats};

	BeatCutter():Filter() {
		init();
	};
	String name="ACUT";
	String shortName="CUT";
	void init(){
		
		String no[2]={"",""};
		p_maxPhraselength.init("LENGTH", "MXP", true, no, no,  1, 1, 4, 1);
		p_repeatChance.init("CHNCE", "RPT", true, no, no,  0, 0, 99, 5);
		p_unitsInCut.init("UNIT", "UIC", true, no, no,  1, 1, 4, 1);
		p_maxRepeats.init("RPEAT", "MXR", true, no, no,  2, 1, 8, 1);


	}
	long _posCounter = 0;
	byte division=1;
	byte divTemp=division;
	byte subDiv= 16;
	byte maxPhraselength=1;
	float repeatChance= 0.00;
	byte unitsInCut=1;
	byte maxRepeats=1;
	byte unitsLeft=0;
	byte unitsDone=0;
	byte totalUnits=0;
	byte barsNow;
	byte repeats=0;
	byte repeatsDone=0;
	boolean repeating=false;
	byte index=0;
	///
	byte segs[128];
	byte indx[128];
	byte dindx[128];

	byte segsCount=0;
	byte indxCount=0;
	byte dindxCount=0;
	byte dindxTotal=0;
			// directio.setParameter("DIR", "STR", 0,1);
			// void setParameter(byte param, int value){
			//   parameters[param]->value=value;

			// }
	int tempNote[4]={0,0,0,0};
	int tempVel[4]={0,0,0,0};
	int tempDur[4]={0,0,0,0};
	int tempOct[4]={0,0,0,0};
	int tempSeq;

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

	void cutter(){
		// Serial.println("cutter");
		segsCount=0;
		indxCount=1;
		dindxCount=0;
		barsNow=byte(random(1, maxPhraselength));
		totalUnits=byte(barsNow*subDiv);
		unitsDone=0;
		repeats=0;
		repeatsDone=0;
		index=0;
		indx[0]=(0);
		while(unitsDone<totalUnits){
	
	       unitsLeft= byte(totalUnits - unitsDone);
	       if(repeatsDone==repeats){
	           repeatsDone=0;
	           if((unitsLeft<(subDiv/2)) && (random(0,100) < repeatChance)){
	                unitsInCut=1;
	          	repeats=unitsLeft;
	           } else {
	               byte temp, max;
	               temp=byte(subDiv/2);
	               if(temp % 2==0){
	                   max=byte((temp-2)/2);
	               } else {
	                   max=byte((temp-1)/2);
	               }
	               unitsInCut=byte(random(0,max));
	             unitsInCut=byte(2*unitsInCut+1);
	            repeating=true;
	            while(unitsInCut>unitsLeft){
	              unitsInCut=byte(unitsInCut-2);
	            }
	            repeats=byte(random(1, maxRepeats));
	            if(repeats*unitsInCut>unitsLeft){
	                unitsInCut=unitsLeft;
	            repeats=1;

	            }
	           }

	          index= byte((index+unitsInCut)%subDiv);

	       }

	      //segs.push(int(unitsInCut));
	     // println(unitsInCut);
	      segs[segsCount]=(byte(unitsInCut));
	      // segs = append(segs, byte(unitsInCut));
	      segsCount++;

	      // indx=append(indx, index);
	      indx[indxCount]=(byte(index));

	      indxCount++;
	      unitsDone=byte(unitsDone+unitsInCut);
	      repeatsDone=byte(repeatsDone + 1);

	    }
	    //printArray(segs);
	    //println("vvvvvvvvvv");
	    //printArray(indx);
	    int ctr=0;
	    for(int s=0; s<segsCount; s++){

	        for(int i=0; i<segs[s]; i++){
	         //dindx[i]=byte((i+ctr)%subDiv);
	         ctr=indx[s];
	         // dindx[dindxCount]=( dindxCount);
	         dindx[dindxCount]=( byte((i+ctr)%subDiv));

	         dindxCount++;
	         //dindx = append(dindx, byte((i)));

	        }
	    }

	dindxTotal = dindxCount;
	// printArray(sequence);
	// println("------------");
	}

	

	void doProcessing(int *parameters, long clockCount, byte step, byte *sequence, byte *notes, byte *velocities,byte *octaves, byte *durations){

		// tempNote[0]= notes[step];
		// tempSeq=sequence[step];
		// tempVel[0]=velocities[step];
		// tempDur[0]=durations[step];
		maxPhraselength=parameters[0];
		repeatChance=parameters[1];
		unitsInCut=parameters[2];
		maxRepeats=parameters[3];
		// Serial.print("dindx");
		// Serial.println(dindx[step%dindxTotal]);
		if (step%(dindxTotal)==0) cutter();
		tempNote[0] = notes[dindx[step%dindxTotal]];
		tempSeq = sequence[dindx[step%dindxTotal]];
		tempVel[0]=velocities[dindx[step%dindxTotal]];
		tempDur[0]=durations[dindx[step%dindxTotal]];
		tempOct[0]=octaves[dindx[step%dindxTotal]];

	




	}
	void doProcessingSingle( int *parameters, long clockCount, byte step, byte seqStep,  byte note, byte velocity,byte octave, byte duration   ){
		// tempNote[0] = note;
		maxPhraselength=parameters[0];
		repeatChance=parameters[1];
		unitsInCut=parameters[2];
		maxRepeats=parameters[3];
		tempSeq=step;
		tempVel[0]=velocity;
		tempDur[0]=duration;
		if (step%(dindxTotal)==0) cutter();
		tempNote[0] = note;
		tempOct[0] = octave;
		// tempSeq = step;
		// tempVel[0]=velocities[dindx[step%dindxTotal]];
		// tempDur[0]=durations[dindx[step%dindxTotal]];

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


	const String classname() { return "BeatCutter";}

};
#endif