#include <Arduino.h>
#ifndef MelodicGenerators_h
#define MelodicGenerators_h
#include "Parameter.h"
#include "Xenakis.h"

class MelodicGenerators  {
private:


public:
	Arpeggio arpeggio;
	Xenakis xenakis;
	Arpeggio whitwell;
	Arpeggio random;
		// Arpeggio arpeggio2;
		// Arpeggio xenakis2;
		// Arpeggio whitwell2;
		// Arpeggio random2;
	Melodic* melodicGens[4]={&arpeggio , &xenakis, &random, &whitwell};
		// Melodic melodicGensNoP[4]={arpeggio , xenakis, random, whitwell};
		// Melodic melodicGensNoP[4]={arpeggio , xenakis, random, whitwell};
	MelodicGenerators( )
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

	virtual const String classname() { return "MelodicGenerators";}

};
#endif