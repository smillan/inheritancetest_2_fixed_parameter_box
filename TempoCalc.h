#include <Arduino.h>
#define NUMBER_OF_TIME_SAMPLES 16
class TempoCalc{
   public:
   	unsigned long times[NUMBER_OF_TIME_SAMPLES]={0,0,0,0,0,0,0,0};
   	unsigned long now =  millis();
      unsigned long  tickcount=0;
   	unsigned long	tempoMillis=0;

      TempoCalc() {


       }
     
      
       float tick ()
      { 
         float sum=0;
      	//insert new item in array
      	unsigned long time= millis();
      	 float calc = time - now;
      	times[tickcount%NUMBER_OF_TIME_SAMPLES]=calc;
      	
      	//sum them for median
      	  sum=0;

      	for (int i = 0; i < NUMBER_OF_TIME_SAMPLES; ++i)
      	{
      		sum+=times[i];
      	}

      	sum = sum/NUMBER_OF_TIME_SAMPLES;

      	now = millis();
      	tickcount++;
         tempoMillis=sum*4;
         sum=60000/(sum*4);
         // cout << "Rectangle class area :" <<endl;
      	// Serial.println(F("clac"));
      	return sum;

      }
};