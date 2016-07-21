#include <Arduino.h>
#ifndef Filters_h
#define Filters_h
#include "Parameter.h"
#include "Filter.h"
#include "Clamp.h"
#include "BeatCutter.h"
// #include "Transpose.h"
#include "Modulo.h"
#include "AddChord.h"
// #include "Thru.h"

class Filters  {
private:


public:
	Clamp clamp;
	// Thru thru;
	BeatCutter beat;
	// Transpose transpose;
	Modulo modulo;
	AddChord chord;
	// Arpeggio arpeggio;
	// Xenakis xenakis;
	// Arpeggio whitwell;
	// Arpeggio random;
		// Arpeggio arpeggio2;
		// Arpeggio xenakis2;
		// Arpeggio whitwell2;
		// Arpeggio random2;
		Filter* filters[5	]={&clamp, &modulo, &beat,  &chord};
		// Melodic melodicGensNoP[4]={arpeggio , xenakis, random, whitwell};
		// Melodic melodicGensNoP[4]={arpeggio , xenakis, random, whitwell};
	Filters( )
	{

	}

	// void getParams(){



	// 		// int nPars=arpeggio.parameters[0]->optionsNames.size();
	// 	Parameter* temp = melodicGens[0]->getParameter(0);
	// 	melodicGens[0]->selectParameter(0);


	// 		// for (int i = 0; i < nPars; ++i)
	// 		// {
	// 		// 	// melodicGens[0]->parameters[0]->optionsNames.push(melodicGens[0]->parameters[0]->optionsNames.top());
	// 		// 	// melodicGens[0]->parameters[0]->optionsNames.pop();


	// 		// 	/* code */
	// 		// }

	// 		// melodicGens[0]->parameters[0]->optionsNames.pop();



	// }

	virtual const String classname() { return "FILTERS";}

};
#endif