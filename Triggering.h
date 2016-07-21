#include <Arduino.h>
#ifndef Triggering_h
#define Triggering_h
#include "Parameter.h"
#include "Trigger.h"
// #include "StreamNotes.h"
#include "Sequencer.h"
#include "Euclidean.h"
#include "Anushri.h"

class Triggering  {
  private:


  public:
    Sequencer sequencer;
    // StreamNotes stream;
    Anushri drummer;
    Euclidean euclidean;

    // Arpeggio arpeggio2;
    // Arpeggio xenakis2;
    // Arpeggio whitwell2;
    // Arpeggio random2;
    Trigger* triggerGens[4]={&euclidean, &sequencer, &drummer};

      Triggering( )
      {

      }

    // void getParams(){



    //   // int nPars=arpeggio.parameters[0]->optionsNames.size();
    //   // Parameter* temp = triggerGens[0]->getParameter(0);
    //   // triggerGens[0]->selectParameter(0);




    // }

    virtual const String classname() { return "EUCL";}

};
#endif