#include <Arduino.h>
// #include "Track.h"



class Clocko {


  protected:

  public:
  	long timerDivided=0;
  	long timerMidi=0;

  	byte midiClockDiv=6;

    Clocko( )
    {
    	

    }
    
    // void notify(Track& tr){

    // 	&tr.tick()


    // }

    void tickClock()
  	{	
  	 
  		timerMidi++;
  		if (timerDivided%midiClockDiv==0)
  		{
  			timerDivided++;
  		}
  				

  	}


};
