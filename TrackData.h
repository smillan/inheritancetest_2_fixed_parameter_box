#include <Arduino.h>
#ifndef TrackData_h
#define TrackData_h

//.-----Sequencing

#include "Melodic.h"
// #include "Xenakis.h"
#include "Arpeggio.h"



#define START_LOOP_SIZE 16
#define MAX_ARRAY_NOTES 128


class TrackData{

	 public:
			///---sequencing
	 TrackData()
			{
				 init();

			}


			typedef struct
				{ 	byte sequence[MAX_ARRAY_NOTES];
					byte notes[MAX_ARRAY_NOTES];
					byte velocities[MAX_ARRAY_NOTES];
					byte durations[MAX_ARRAY_NOTES];
					byte octaves[MAX_ARRAY_NOTES];
					byte channel=1;
					byte octave=2;
					byte step=0;
					byte offset=0;
					byte loopSize=START_LOOP_SIZE;
				} Data;
				Data part_data;



				typedef struct
				{
						byte currentScale = 0;
						byte currentGenerator=0;

				} Settings;

			Settings parameters;

			void init(){
				for (int i = 0; i < MAX_ARRAY_NOTES; ++i)
				{
					part_data.sequence[i]=0;
					part_data.notes[i]=i;
					part_data.sequence[i]=true;
					part_data.velocities[i]=127;
					part_data.durations[i]=10;
					part_data.octaves[i]=2;
				}



			}




			typedef struct
			{
					String a = "scale";
					String b = "generator";

			} SettingsNames;
			SettingsNames parameterNames;


			virtual void reset(){


				part_data.step=0;
				// notes_selector->nextStep(part_data.step);
			}


			// virtual const String classname() { return "trackData";}


				 protected:
};



#endif