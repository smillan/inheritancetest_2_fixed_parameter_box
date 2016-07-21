#include <Arduino.h>
#ifndef TrackParameters_h
#define TrackParameters_h
#include "Parameter.h"

class TrackParameters   {
	private:



			// String divOptions[12]={"96", "48", "32", "24", "16", "12","8","6","4","3","2", "1"};
			// clockDiv.init("ClockDiv", "DVI", false, divOptions, divOptions,  11, 0, 12, 1);
			// offset.init("offset", "DVI", true, Options, Options,  0, 0, 127, 1);
			// loopSize.init("loopSize", "LSZ", true, Options, Options,  16, 1, 127, 1);
			// swing.init("swing", "SWG", true, Options, Options, 0, 0, 80, 1);
			// melodicGenerators->melodicGens[0]->generateSequence(part_data.notes, part_data.velocities, part_data.durations);

	public:
		Parameter swing;
		Parameter scale;
		Parameter clockDiv;
		Parameter offset;
		Parameter loopSize;
		Parameter octave;


		Parameter* parameters[6]={&swing,&scale,&clockDiv,&offset, &loopSize,&octave};
		// Melodic melodicGensNoP[4]={arpeggio , xenakis, random, whitwell};
		// Melodic melodicGensNoP[4]={arpeggio , xenakis, random, whitwell};
		  TrackParameters( )
		  {
			String Options[2]={"",""};
			String scaleNames[20] = {	"chromatic", "wholetone", "minor", "harm_min", "pent_min", "major", "harm_maj", "pent_maj", "diminish", "fifths", "blues", "arabian", "persian", "oriental", "javanese", "jewish", "gypsy", "dorian", "ethiopian", "cutter" };
	 		String scaleShortNames[20] = {	"CHR", "WHT", "MIN", "HMI", "PMI", "MAJ", "HMA", "PMA", "DIM", "FIF", "BLU", "ARB", "PRS", "ORT", "JAV", "JWS", "GYP", "DOR", "ETH","CUT" };

			scale.init("SCALE", "SCL", false, scaleNames, scaleShortNames,  0, 0, 20, 1);
			String divOptions[12]={"64", "48", "32", "24", "16", "12","8","6","4","3","2","1"};
			clockDiv.init("DIV", "DIV", false, divOptions, divOptions,  4, 0, 12, 1);
			offset.init("OFFST", "OFS", true, Options, Options,  0, 0, 127, 1);
			loopSize.init("SIZE", "LSZ", true, Options, Options,  16, 1, 129, 1);
			swing.init("SWNG", "SWG", true, Options, Options, 0, 0, 80, 1);
			octave.init("OCT", "OCT", true, Options, Options, 4, -3, 6, 1);
		  }

		void getParams(){







			// melodicGens[0]->parameters[0]->optionsNames.pop();



		}

		virtual const String classname() { return "TrackParameters";}

};
#endif