#ifndef ParameterValues_h
#define ParameterValues_h
#include <Arduino.h>
// #include "Track.h"
#include <stack>
#include <vector>
#include <Streaming.h>



class ParameterValues{


  protected:

  public:



    int values[6]={0,0,0,0,0,0};

    // String optionsNames[1];
    // String optionsShortNames[1];
    ParameterValues()
    {


    }
    ///NAME SHORTNAME TYPE(STR or INT) OPTIONS PRESET MIN MAX INCREMENT


    void addValue(byte index, int value)
    {
        values[index%6]=value;
    }

    void clear(){
        for (int i = 0; i < 6; ++i)
        {
            values[i]=0;
        }
    }


      virtual const String classname() { return "parameterValues";}


};
#endif
