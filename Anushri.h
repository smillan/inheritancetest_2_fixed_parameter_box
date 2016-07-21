#include <Arduino.h>
#include "Parameter.h"


class Anushri: public Trigger{
private:

	Parameter xMap;
	Parameter yMap;
	Parameter BDfreq;
	Parameter SDfreq;
	Parameter HHfreq;


public:
	String name="DRUM";
	String shortName="DRM";
	Parameter* parameters[5]={&xMap,&yMap,&BDfreq,&SDfreq,&HHfreq};
	byte BDcluster1[32] = { 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68 };
	byte SDcluster1[32] = { 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68 };
	byte HHcluster1[32] = { 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68 };

	byte BDcluster2[32] = { 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68 };
	byte SDcluster2[32] = { 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68 };
	byte HHcluster2[32] = { 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68 };

	byte BDcluster3[32] = { 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68 };
	byte SDcluster3[32] = { 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68 };
	byte HHcluster3[32] = { 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68 };

	byte BDcluster4[32] = { 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68 };
	byte SDcluster4[32] = { 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68 };
	byte HHcluster4[32] = { 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68 };

	byte BDcluster5[32] = { 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68 };
	byte SDcluster5[32] = { 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68 };
	byte HHcluster5[32] = { 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68 };

	byte BDcluster6[32] = { 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68 };
	byte SDcluster6[32] = { 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68 };
	byte HHcluster6[32] = { 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68 };

	Anushri():Trigger() {
		init();

	 }
	int test=0;


	void init(){
				///NAME SHORTNAME TYPE(STR or INT) OPTIONS PRESET MIN MAX INCREMENT

		String noOptions[2]={" "," "};
		xMap.init("XMAP","XMP", "INT", noOptions, noOptions,  0, -100, 100, 1);
		yMap.init("YMAP","YMP", "INT", noOptions, noOptions,  0, -100, 100, 1);
		BDfreq.init("BD","BDF", "INT", noOptions, noOptions,  0, 0, 256, 1);
		SDfreq.init("SD","SDF", "INT", noOptions, noOptions,  0, 0, 256, 1);
		HHfreq.init("HH","HHF", "INT", noOptions, noOptions,  0, 0, 256, 1);



	}
	int getParameterCount(){
		int max= sizeof(parameters) / sizeof(parameters[ 0 ]);
		return max;
	}

	Parameter* getParameter( int param){
		return parameters[param];
	}

	String getName ()
	{
		return name;
	}
	String getShortName ()
	{
		return shortName;
	}

	void getNextStep ()
	{
				 // cout << "Rectangle class area :" <<endl;

	}

	virtual void generateSequence(int *parameters, byte *triggers){



	}
	virtual void generateStep(byte step, int *parameters, byte *triggers){



	}
};