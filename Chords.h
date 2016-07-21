#include <Arduino.h>
#ifndef Chords_h
#define Chords_h

class Chords{
   public:
	
	  Chords() { 
	  }     

	  void getNextStep ()
	  { 
		 // cout << "Rectangle class area :" <<endl;
		Serial.println("Stream");

	  }
	 

		// ChordDef part_data;;
	
		// ChordDef scaleList[1] ={chromatic}
		byte chordList[14][3] = {
			{3,7,0},
			{4,7,0},
			{3,6,0},
			{4,8,0},
			{3,6,9},
			{3,6,10},
			{3,7,10},
			{3,7,11},
			{4,6,10},
			{4,7,9},
			{4,7,10},
			{4,7,11},
			{4,8,10},
			{4,8,11}
		};

		byte getChordList(byte w, byte n){
			return chordList[w][n];

		}
		

		



	// ScaleList getScale;
	  virtual  String classname() { return "chords";};

};	

#endif