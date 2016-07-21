#ifndef Parameter_h
#define Parameter_h
#include <Arduino.h>
// #include "Track.h"
#include <stack>
#include <vector>
#include <Streaming.h>



class Parameter{


  protected:

  public:
    String name="";
    String shortName="";
    //TRUE = INTEGER FALSE = STRING LIST
    boolean type=true;
    int preset=0;
    int value=0;
    int min=0;
    int max=0;
    int increment=0;

    std::vector<String> optionsNames;
    std::vector<String> optionsShortNames;

    // String optionsNames[1];
    // String optionsShortNames[1];
    Parameter()
    {


    }
    ///NAME SHORTNAME TYPE(STR or INT) OPTIONS PRESET MIN MAX INCREMENT


    void init(String na, String sNa, bool ty, String *opt, String *optShort, int pst, int mn , int mx, int inc)
    {

      name=na;
      shortName=sNa;
      type=ty;

      preset=pst;
      value=pst;
      max = mx;
      min = mn;
      increment = inc;

      if(!ty){
         for(int i=0; i<max; i++){
            optionsNames.push_back(opt[i]);
            optionsShortNames.push_back(optShort[i]);
          };

      }



    }
   String getName ()
      {
        return name;
      }
    String getShortName ()
    {
      return shortName;
    }

    bool getType ()
    {
      return type;
    }

   
      virtual const String classname() { return "parameter";}


};
#endif
