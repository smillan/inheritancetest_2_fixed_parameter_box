#include <Arduino.h>
#include <MIDI.h>
#include <SD.h>

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "Oled_Screen.h"

#include "Parameter.h"
#include "Track.h"
#include "SDSave.h"

#include <Bounce.h>
// #include "MelodicGenerator.h"
#define SHIFT_BUTTON 27
#define MENU_BUTTON 28
#define CHANNEL_1_BUTTON 2
#define CHANNEL_2_BUTTON 3
#define CHANNEL_3_BUTTON 4
#define CHANNEL_4_BUTTON 5
#define KNOB_1_BUTTON 6
#define KNOB_2_BUTTON 7
#define KNOB_3_BUTTON 8
#define KNOB_4_BUTTON 9
#define KNOB_5_BUTTON 25
#define KNOB_6_BUTTON 26
#define PLOAD_PIN 32
#define CE_PIN 33
#define CLK_PIN 30
#define DATA_PIN 29
/* How many shift register chips are daisy-chained.
*/
#define NUMBER_OF_SHIFT_CHIPS   2

/* Width of data (how many ext lines).
*/
#define DATA_WIDTH   NUMBER_OF_SHIFT_CHIPS * 8

/* Width of pulse to trigger the shift register to read and latch.
*/
#define PULSE_WIDTH_USEC   5

/* Optional delay between shift register reads.
*/
#define POLL_DELAY_MSEC   1

/* You will need to change the "int" to "long" If the
 * NUMBER_OF_SHIFT_CHIPS is higher than 2.
*/
#define BYTES_VAL_T unsigned int




#define ENCODER_OPTIMIZE_INTERRUPTS
#include <Encoder.h>

 Encoder knobOne(3,2);
 Encoder knobTwo(6,8 );
 Encoder knobThree(5, 4);
 Encoder knobFour(9,11);
 Encoder knobFive(15,20);
 Encoder knobSix(21,22);

 SaveToSSD sd;
 File settings;

 class Control {
	// Bounce bouncer_shift = Bounce( SHIFT_BUTTON, 5 );
	// Bounce bouncer_menu = Bounce( MENU_BUTTON, 50 );

	// Bounce bouncer_channel_1 = Bounce( CHANNEL_1_BUTTON,5 );
	// Bounce bouncer_channel_2 = Bounce( CHANNEL_2_BUTTON,5 );
	// Bounce bouncer_channel_3 = Bounce( CHANNEL_3_BUTTON,5 );
	// Bounce bouncer_channel_4 = Bounce( CHANNEL_4_BUTTON,5 );


	// Bounce bouncer_knobButton_1 = Bounce( KNOB_1_BUTTON,5 );
	// Bounce bouncer_knobButton_2 = Bounce( KNOB_2_BUTTON,5 );
	// Bounce bouncer_knobButton_3 = Bounce( KNOB_3_BUTTON,5 );
	// Bounce bouncer_knobButton_4 = Bounce( KNOB_4_BUTTON,5 );
	// Bounce bouncer_knobButton_5 = Bounce( KNOB_5_BUTTON,5 );
	// Bounce bouncer_knobButton_6 = Bounce( KNOB_6_BUTTON,5 );
 private:
 	long positionOne  = -999;
 	long positionTwo = -999;
 	long positionThree  = -999;
 	long positionFour = -999;


 public:
 	Track* trackIn;
 	Track* ctracks[4];
 	bool tempoState;
 	bool shift=false;
 	bool shiftKnobs[6]={false,false,false,false,false,false};
 	byte updateKnob=0;
 	bool cleared=true;
 	bool changed=true;
 	bool showChanged=true;
 	bool lazyChanged=true;
 	Encoder* encoders[6]={&knobOne,&knobTwo,&knobThree,&knobFour, &knobFive, &knobSix};
 	long positions[4] ={-999,-999,-999,-999};
 	byte values[10]={0,0,0,0,0,0,0,0,0,0};
 	byte butValues[16]={0,0,0,0,0,0,0,0,0,0,0,0};


 	Oled_Screen* display;
 	enum Modes {GLOBAL, TRACK};
 	Modes mode = TRACK;
 	byte currentTrack=0;
 	byte stepSelected=0;
 	unsigned long changeMillis=0;
 	unsigned long lazyMillis=0;
 	byte showTime= 200;
 	byte lazyTime= 50;
 	int cnt=0;

 	BYTES_VAL_T pinValues;
 	BYTES_VAL_T oldPinValues;
		// modes mode = GLOBAL;
 	Control()
 	{
		// pinMode(SHIFT_BUTTON ,INPUT);
		// pinMode(MENU_BUTTON ,INPUT);
		// pinMode(CHANNEL_1_BUTTON , INPUT);
		// pinMode(CHANNEL_2_BUTTON , INPUT);
		// pinMode(CHANNEL_3_BUTTON , INPUT);
		// pinMode(CHANNEL_4_BUTTON , INPUT);
		// pinMode(KNOB_1_BUTTON , INPUT);
		// pinMode(KNOB_2_BUTTON , INPUT);
		// pinMode(KNOB_3_BUTTON , INPUT);
		// pinMode(KNOB_4_BUTTON , INPUT);
		// pinMode(KNOB_5_BUTTON , INPUT);
		// pinMode(KNOB_6_BUTTON , INPUT);
 		pinMode(PLOAD_PIN , OUTPUT);
 		pinMode(CE_PIN , OUTPUT);
 		pinMode(CLK_PIN , OUTPUT);
 		pinMode(DATA_PIN , INPUT);



			// Setup the button
			// pinMode(  ,INPUT);
			// Activate internal pull-up (optional)
			// digitalWrite(  ,HIGH);
			// After setting up the button, setup the object
			// bouncer.attach(  );
			// bouncer.interval(5);
			// init();
 	}
 	BYTES_VAL_T read_shift_regs()
 	{
 		long bitVal;
 		BYTES_VAL_T bytesVal = 0;

	  /* Trigger a parallel Load to latch the state of the data lines,
	  */
 		digitalWrite(CE_PIN, HIGH);
 		digitalWrite(PLOAD_PIN, LOW);
 		delayMicroseconds(PULSE_WIDTH_USEC);
 		digitalWrite(PLOAD_PIN, HIGH);
 		digitalWrite(CE_PIN, LOW);

	  /* Loop to read each bit value from the serial out line
	   * of the SN74HC165N.
	  */
	   for (int i = 0; i < DATA_WIDTH; i++)
	   {
	   	bitVal = digitalRead(DATA_PIN);

		/* Set the corresponding bit in bytesVal.
		*/
	   	bytesVal |= (bitVal << ((DATA_WIDTH - 1) - i));

		/* Pulse the Clock (rising edge shifts the next bit).
		*/
	   	digitalWrite(CLK_PIN, HIGH);
	   	delayMicroseconds(PULSE_WIDTH_USEC);
	   	digitalWrite(CLK_PIN, LOW);
	   }

	   return (bytesVal);
	}

	void display_pin_values()
	{


		for (int i = 0; i < DATA_WIDTH; i++)
		{



		// Serial.print((pinValues >> i) & 1);

			if ((pinValues >> i) & 1)
				butValues[i]=1;
			else
				butValues[i]=0;
		// Serial.print(i);
		// Serial.print(" -> ");
		// Serial.print(values[i]);
		// Serial.print("\r\n");
		}

		// Serial.print("\r\n");
		// Serial.print(shift);
	}	

	void addDisplay(Oled_Screen& disp){
		display = &disp;
		display->init();

	}
	void printControl(){
		if (mode==GLOBAL)
		{

		}else{

		}



	}

	void load(File settingsFile){

			// Serial.print(getStringPartByNr(settingsFile,'#', 0));
		// char tex[]
		byte track=0;
		byte trig;
		byte melody;
		byte filter;
		bool completed=false;
			char character;
			  int seccion=0;
			  String settingName="";
			  String settingValue;
			  // settingsFile = SD.open("settings.txt");
			  byte nval=0;
			  if (settingsFile) {
			    while (settingsFile.available()) {
			     			 	character = settingsFile.read();
								
								// Serial.print(character);
								// seccion=90;
								
								
								// delay(1);
								// int bogus=19;

								
								if(seccion==0 && character!='\n' && character!=':')
								{
										// ctracks[track]->currentTrigger = settingValue.toInt();

									    settingValue+=character;
										// Serial.println("");	
										// Serial.println("");	
										// Serial.println(track);	
										// Serial.println(ctracks[track]->currentTrigger);	
										ctracks[track]->currentTrigger = int(settingValue.toInt());

										settingValue = "";

										// Serial.print(character);		
										// Serial.println("_trig");		

										// Serial.println("read/track");
										// Serial.print(track);
								}else if(seccion==1  && character!='\n'){
										// settingValue = "";
										// Serial.print("uno");		
										// Serial.println(seccion);
										// Serial.print(character);		
										// Serial.println(track);	
										if (character!=':')
										{
											// Serial.print(settingValue);		
											settingValue+=character;
										}else{
											
											
											// Serial.print("nval");		
											// Serial.println(nval);	
											// Serial.print("val");		
											// Serial.println(String(settingValue));

											ctracks[track]->triggerValues.addValue(nval, int(settingValue.toInt()));
											nval++;
											settingValue = "";
										}
								}
								else if(seccion==2 && character!='\n' && character!=':'){
										// Serial.print(character);		

										settingValue+=character;
										ctracks[track]->currentGenerator = int(settingValue.toInt());
										// Serial.print("mel");	
										// Serial.println(settingValue);	
										settingValue = "";

										// Serial.print(settingValue);	
								}else if(seccion==3 && character!='\n'){

										if (character!=':')
										{
											// Serial.print(settingValue);		
											settingValue+=character;

										}else{
											
											// Serial.print("nval");		
											// Serial.println(nval);	
											// Serial.print("val");		
											// Serial.println(String(settingValue));

											ctracks[track]->melodicValues.addValue(nval, int(settingValue.toInt()));
											nval++;
											settingValue = "";
										}

								}else if(seccion==4 && character!='\n'){
										settingValue+=character;
										ctracks[track]->currentFilters[0] = int(settingValue.toInt());

										// Serial.print("f1->");	
										// Serial.println(settingValue);	
										settingValue = "";

										// Serial.print(settingValue);	
								}else if(seccion==5 && character!='\n'){
										if (character!=':')
										{
											// Serial.print(settingValue);		
											settingValue+=character;

										}else{
											
											// Serial.print("nval");		
											// Serial.println(nval);	
											// Serial.print("val");		
											// Serial.println(String(settingValue));

											ctracks[track]->filterValues[0].addValue(nval, int(settingValue.toInt()));
											nval++;
											settingValue = "";
										}
								}else if(seccion==6 && character!='\n'){
										settingValue+=character;
										ctracks[track]->currentFilters[1] = int(settingValue.toInt());	
										settingValue = "";

										// Serial.print(settingValue);	
								}else if(seccion==7 && character!='\n'){
										if (character!=':')
										{
											// Serial.print(settingValue);		
											settingValue+=character;

										}else{
											ctracks[track]->filterValues[1].addValue(nval, int(settingValue.toInt()));
											nval++;
											settingValue = "";
										}
								}else if(seccion==8 && character!='\n'){
										settingValue+=character;
										ctracks[track]->currentFilters[2] = int(settingValue.toInt());	
										settingValue = "";

										// Serial.print(settingValue);	
								}else if(seccion==9 && character!='\n'){
										if (character!=':')
										{
											settingValue+=character;

										}else{
											ctracks[track]->filterValues[2].addValue(nval, int(settingValue.toInt()));
											nval++;
											settingValue = "";
										}
								}else if(seccion==10 && character!='\n'){
										settingValue+=character;
										ctracks[track]->currentFilters[3] = int(settingValue.toInt());	
										settingValue = "";

										// Serial.print(settingValue);	
								}else if(seccion==11 && character!='\n'){
										if (character!=':')
										{
											settingValue+=character;

										}else{
											ctracks[track]->filterValues[3].addValue(nval, int(settingValue.toInt()));
											nval++;
											settingValue = "";
										}
								}else if(seccion==12 && character!='\n'){
										if (character!=':')
										{
											settingValue+=character;

										}else{
											ctracks[track]->trackValues.addValue(nval, int(settingValue.toInt()));
											nval++;
											settingValue = "";
										}
								}
								
								if (character=='\n' && seccion < 80){
									seccion++; // read track
									nval=0;
									if (seccion==13)
									{	seccion=0;
										if(track<3)track++;
										// Serial.println("");
									// Serial.print("track->");	

										// Serial.println(track);
									}
									// Serial.print("tr");
									// character = settingsFile.read();
									// completed=false;
									// Serial.print(character);
									
									// Serial.print("seccion->");
									// Serial.println(seccion);	
									// Serial.print("track->");	
									// Serial.println(track);	


								}
								
						

						
			      // character = settingsFile.read();

			    // track++
			}
		}
		settingsFile.close();
		lazyChanged=true;
		updateKnob=0;

	}
	void save( byte i){
		String all="";
		
			// all+=String(i);
			// all+="\n";
			// all+="\n";
			// Serial.print(sizeof(ctracks[i]->melodicValues.values));
			// all+=">"+String(ctracks[i]->getTriggerName());	
			all+="";

			all+=String(ctracks[i]->currentTrigger);	
			all+=":\n";

			for (int m = 0; m < 6; ++m)
			{
				all+=saveTriggerOption(i, m);
				
			}
			all+="\n";

			// all+=String(ctracks[i]->getMelodicName())+ ":";	
			all+=String(ctracks[i]->currentGenerator);	
			// all+="\n";
			all+=":\n";

			for (int m = 0; m < 6; ++m)
			{
				all+=saveMelodicOption(i, m);
			}
			// all+="\n";

			for (int f = 0; f < 4; ++f){

					// all+="?"+String(ctracks[i]->getFilterName(f))+ ":";	
					all+="\n";
					all+=String(ctracks[i]->currentFilters[f]);	
					all+="\n";


					for (int m = 0; m < 6; ++m){	
						all+=saveFilterOption(i, f, m);
						
					}
					// all+="\n";

			}
			all+="\n";
			all+=saveTrackOptions(i);
			all+="\n";
			
			// all+="=";
			
		
			Serial.print(all);
			sd.save(all);

	}
// void save( byte i){
// 		String all="";
		
// 			// all+=String(i);
// 			// all+="\n";
// 			// all+="\n";
// 			// Serial.print(sizeof(ctracks[i]->melodicValues.values));
// 			// all+=">"+String(ctracks[i]->getTriggerName());	
// 			all+="tr->";

// 			all+=String(ctracks[i]->currentTrigger);	
// 			all+="\nto->";

// 			for (int m = 0; m < 6; ++m)
// 			{
// 				all+=saveTriggerOption(i, m);
				
// 			}
// 			all+="\ncg->";

// 			// all+=String(ctracks[i]->getMelodicName())+ ":";	
// 			all+=String(ctracks[i]->currentGenerator);	
// 			// all+="\n";
// 			all+="\nco->";

// 			for (int m = 0; m < 6; ++m)
// 			{
// 				all+=saveMelodicOption(i, m);
// 			}
// 			// all+="\n";

// 			for (int f = 0; f < 4; ++f){

// 					// all+="?"+String(ctracks[i]->getFilterName(f))+ ":";	
// 					all+="\nfn->";
// 					all+=String(ctracks[i]->currentFilters[f]);	
// 					all+="\nfo->";


// 					for (int m = 0; m < 6; ++m){	
// 						all+=saveFilterOption(i, f, m);
						
// 					}
// 					// all+="\n";

// 			}
// 			all+="\n";
			
// 			// all+="=";
			
		
// 			// Serial.print(all);
// 			sd.save(all);

// 	}
	void control(Track* tracks[]){
		trackIn=tracks[currentTrack];
			// Serial.print(currentTrack);

		ctracks[0]=tracks[0];
		ctracks[1]=tracks[1];
		ctracks[2]=tracks[2];
		ctracks[3]=tracks[3];
		unsigned long currentMillis = millis();
		pinValues = read_shift_regs();

		  /* If there was a chage in state, display which ones changed.
		  */
		if (pinValues != oldPinValues)
		{
			// Serial.print("*Pin value change detected*\r\n");
			display_pin_values();
			oldPinValues = pinValues;
			updateShifters();
		}


		if (currentMillis - lazyMillis >= lazyTime)
		{

			lazyScreenDisplay(updateKnob);

			lazyMillis=currentMillis;
		}


	// save the last time you blinked the lastED

		// changeMillis = currentMillis;


		if(mode==GLOBAL){


			for (int i = 0; i < 6; ++i)
			{
				if (!shiftKnobs[i])
				{
					setGlobalParameter(i);
				}else{
						// setTrackValue(i);
					setGlobalParameter(i);
				}
			}
			if (!changed)
			{
				// showChain();
				changed=true;
			}


		}else{
			for (int i = 0; i < 6; ++i)
			{
				if (shift )
				{

					// Serial.println("shiftKnobs[i]");
					// Serial.println(shiftKnobs[i]);
					setTrackValue(i);
				}else{
						// setTrackValue(i);
					/////AQUI ESTA EL FAIL¡¡¡
					
					melodicOrTrigger(i);
				}
			}
					// Serial.println("shift");
					// Serial.println(shift);
			if (!changed)
			{
				// showDataOptions(stepSelected);
				// showTrackOptions();
				changed=true;
			}



		}

		// updateBounces();
		// updateShifters();



	}

	void setMode(){

			// readBounces();

	}
	void menuGlobal(){
		updateKnob=0;
		if (!cleared)
		{
			display->clearDisplay();
			cleared=true;

		};
		lazyChanged=true;

		if (mode==GLOBAL)
		{
			mode=TRACK;
		}else{
			mode=GLOBAL;
		}


	}
	void changeChannel(int channel){

		currentTrack = channel;

		if (shift)
		{

			ctracks[channel]->isPlaying = !ctracks[channel]->isPlaying ;
			lazyChanged=true;
			updateKnob=0;

		}else{
				// values[currentTrack+2] = 1;
			lazyChanged=true;
			updateKnob=0;
		}



	}
	void changeOption(int channel){

		if (mode==TRACK )
		{
					// shiftKnobs[0] = 1;
			stepSelected=channel;
					Serial.print(stepSelected);
			lazyChanged=true;
			updateKnob=0;

		}else{
			stepSelected=channel;
					Serial.print(stepSelected);
			lazyChanged=true;
			updateKnob=0;

		}


	}
	void updateShifters(){


		shift=butValues[10];
		shift!=shift;
		if (butValues[3] ){ menuGlobal(); };
		if (butValues[14] ){ changeChannel(0);};
		if (butValues[13] ){ changeChannel(1);};
		if (butValues[0] ){ changeChannel(2);};
		if (butValues[7] ){ changeChannel(3);};
		if (butValues[9] ){ changeOption(0);};
		if (butValues[8] ){ changeOption(1);};
		if (butValues[12] ){ changeOption(2);};
		if (butValues[1] ){ changeOption(3);};
		if (butValues[5] ){ changeOption(4);};
		if (butValues[4] ){ changeOption(5);};
		if (butValues[15] ){ sd.sdOpen();save(0);save(1);save(2);save(3);sd.sdClose();};
		if (butValues[6] ){ load(sd.readSDSettings());};
	}
	// void updateBounces(){

	// 	if(bouncer_menu.update()){
	// 		if ( bouncer_menu.read()==1)
	// 		{
	// 			updateKnob=0;
	// 			if (!cleared)
	// 			{
	// 				display->clearDisplay();
	// 				cleared=true;

	// 			};
	// 			lazyChanged=true;

	// 			if (mode==GLOBAL)
	// 			{
	// 				mode=TRACK;
	// 			}else{
	// 				mode=GLOBAL;
	// 			}
	// 		}else{
	// 			cleared=false;
	// 			changed=false;
	// 		}


	// 	};
	// 		// values[0] = bouncer_menu.read();


	// 	if(bouncer_shift.update()){;
	// 		if(bouncer_shift.read()==1){
	// 			updateKnob=0;


	// 			// showChanged=false;
	// 			shift=true;
	// 		}else{
	// 			shift=false;
	// 			// lazyChanged=true;
	// 		}

	// 		// Serial.println(shift);
	// 	}

	// 	if (bouncer_channel_1.update())
	// 	{
	// 		if (shift)
	// 		{
	// 			if (bouncer_channel_1.read()==1)
	// 			{
	// 				ctracks[0]->isPlaying = !ctracks[0]->isPlaying ;
	// 			}


	// 			lazyChanged=true;
	// 			updateKnob=0;

	// 		}else{

	// 			values[2] = bouncer_channel_1.read();
	// 			lazyChanged=true;
	// 			updateKnob=0;
	// 		}




	// 	}else{
	// 		changed=false;
	// 	}
	// 	if (bouncer_channel_2.update())
	// 	{
	// 		if (shift)
	// 		{
	// 			if (bouncer_channel_2.read()==1)
	// 			{
	// 				ctracks[1]->isPlaying = !ctracks[1]->isPlaying ;
	// 			}
	// 			lazyChanged=true;
	// 			updateKnob=0;

	// 		}else{

	// 			values[3] = bouncer_channel_2.read();
	// 			lazyChanged=true;
	// 			updateKnob=0;

	// 		}


	// 	}
	// 	if (bouncer_channel_3.update())
	// 	{
	// 		if (shift)
	// 		{
	// 			if (bouncer_channel_3.read()==1)
	// 			{
	// 				ctracks[2]->isPlaying = !ctracks[2]->isPlaying ;
	// 			}
	// 			lazyChanged=true;
	// 			updateKnob=0;

	// 		}else{

	// 			values[4] = bouncer_channel_3.read();
	// 			lazyChanged=true;
	// 			updateKnob=0;

	// 		}




	// 	}
	// 	if (bouncer_channel_4.update())
	// 	{
	// 		if (shift)
	// 		{
	// 			if (bouncer_channel_4.read()==1)
	// 			{
	// 				ctracks[3]->isPlaying = !ctracks[3]->isPlaying ;
	// 			}
	// 			lazyChanged=true;
	// 			updateKnob=0;

	// 		}else{

	// 			values[5] = bouncer_channel_4.read();
	// 			lazyChanged=true;
	// 			updateKnob=0;
	// 		}



	// 	}
	// 	for (int i = 2; i < 6; ++i)
	// 	{
	// 		if(values[i]==1) currentTrack=i-2;

	// 	}


	// 	if (bouncer_knobButton_1.update()){

	// 			if (mode==TRACK )
	// 			{
	// 				shiftKnobs[0] = bouncer_knobButton_1.read();
	// 				stepSelected=0;
	// 				// Serial.print(stepSelected);
	// 				lazyChanged=true;
	// 				updateKnob=0;

	// 			}else{
	// 				stepSelected=0;
	// 				// Serial.print(stepSelected);
	// 				lazyChanged=true;
	// 				updateKnob=0;

	// 			}


	// 	}

	// 	if (bouncer_knobButton_2.update()){
	// 		if (mode==TRACK )
	// 		{
	// 			shiftKnobs[1] = bouncer_knobButton_2.read();
	// 			stepSelected=1;
	// 			// Serial.print(stepSelected);
	// 			lazyChanged=true;
	// 			updateKnob=0;
	// 		}else{
	// 			stepSelected=1;
	// 			// Serial.print(stepSelected);
	// 			lazyChanged=true;
	// 			updateKnob=0;

	// 		}
	// 	}

	// 	if (bouncer_knobButton_3.update()){
	// 		if (mode==TRACK )
	// 		{
	// 			shiftKnobs[2] = bouncer_knobButton_3.read();
	// 			stepSelected=2;
	// 			// Serial.print(stepSelected);
	// 			lazyChanged=true;
	// 			updateKnob=0;
	// 		}else{
	// 			stepSelected=2;
	// 			// Serial.print(stepSelected);
	// 			lazyChanged=true;
	// 			updateKnob=0;

	// 		}
	// 	}

	// 	if (bouncer_knobButton_4.update()){
	// 		if (mode==TRACK )
	// 		{
	// 			shiftKnobs[3] = bouncer_knobButton_4.read();
	// 			stepSelected=3;
	// 			// Serial.print(stepSelected);
	// 			lazyChanged=true;
	// 			updateKnob=0;
	// 		}else{
	// 			// Serial.print(stepSelected);
	// 			lazyChanged=true;
	// 			updateKnob=0;
	// 			stepSelected=3;

	// 		}
	// 	}
	// 	if (bouncer_knobButton_5.update()){
	// 		// Serial.print("4");
	// 		if (mode==TRACK )
	// 		{
	// 			shiftKnobs[4] = bouncer_knobButton_5.read();
	// 			stepSelected=4;

	// 			lazyChanged=true;
	// 			updateKnob=0;
	// 		}else{
	// 			// Serial.print(stepSelected);
	// 			lazyChanged=true;
	// 			updateKnob=0;
	// 			stepSelected=4;

	// 		}
	// 	}
	// 	if (bouncer_knobButton_6.update()){
	// 		// Serial.print("4");
	// 		if (mode==TRACK )
	// 		{
	// 			shiftKnobs[5] = bouncer_knobButton_6.read();
	// 			stepSelected=5;

	// 			// Serial.print(stepSelected);
	// 			lazyChanged=true;
	// 			updateKnob=0;
	// 		}else{
	// 			// Serial.print(stepSelected);
	// 			lazyChanged=true;
	// 			updateKnob=0;
	// 			stepSelected=5;

	// 		}
	// 	}

	// }

	void printBounces(){

			// byte readings[9] = {


			// }
	}
		/// NEW VALUE FOR TRACK SETTINGS SWING ETC
	void setTrackValue(byte encoder){
		long newPos= encoders[encoder]->read();

		if (newPos != positions[encoder] &&  newPos%4==0  ){
			updateKnob=encoder;

			int increment = checkDirection(positions[encoder], newPos);
			positions[encoder] = newPos;


			int* temp = trackIn->getParameterValue(encoder, increment);

			showParameter(trackIn->getParameter(encoder), temp);
			showTrackOption(encoder);
			if (encoder==1)
			{
				trackIn->generateMelodic();
				
			}
					// trackIn->setParameter(encoder, newPos);
			// showDataOptions(stepSelected);
		}


	}
	void melodicOrTrigger(byte encoder){
		// updateKnob=encoder;


		if (stepSelected==0)
		{
			setTriggerValue(encoder);
		}else if (stepSelected==1)
		{
		// Serial.println("melodicOrTrigger");

			setMelodicValue(encoder);
		}else if (stepSelected==2) {

			setFilterValue(0, encoder);
		}
		else if (stepSelected==3) {

			setFilterValue(1, encoder);
		}
		else if (stepSelected==4) {

			setFilterValue(2, encoder);
		}
		else if (stepSelected==5) {

			setFilterValue(3, encoder);
		}


	}
	void setMelodicValue(byte encoder){
		// updateKnob=encoder;
		
		long newPos= encoders[encoder]->read();
		if (encoder<trackIn->getMelodicParameterCount(encoder))
		{
			if (newPos != positions[encoder] &&  newPos%4==0  ){
				updateKnob=encoder;

				int increment = checkDirection(positions[encoder], newPos);
				positions[encoder] = newPos;


				int* temp = trackIn->setMelodicValue(encoder, increment);
				// Serial.println("setMelodicValue");
				// showParameter(trackIn->getMelodicParameter(encoder), temp);
				showParameter2(trackIn->getMelodicName(), trackIn->getMelodicParameter(encoder), temp);
				showMelodicOption(encoder);
					// trackIn->setParameter(encoder, newPos);
				// showDataOptions(stepSelected);
			}
		}


	}
	void setTriggerValue(byte encoder){
		long newPos= encoders[encoder]->read();

		if (newPos != positions[encoder] &&  newPos%4==0  ){
			if (encoder<trackIn->getTriggerParameterCount(encoder))
			{
				updateKnob=encoder;



				int increment = checkDirection(positions[encoder], newPos);
				positions[encoder] = newPos;

				int* temp = trackIn->getTriggerValue(encoder, increment);

				showParameter2(trackIn->getTriggerName(),trackIn->getTriggerParameter(encoder), temp);
				showTriggerOption(encoder);
				trackIn->generateTrigger();
				// trackIn->setParameter(encoder, newPos);
			// showDataOptions(stepSelected);
			}
		}



	}
	void setFilterValue(byte filter, byte encoder){
		long newPos= encoders[encoder]->read();

		if (newPos != positions[encoder] &&  newPos%4==0  ){
			if (encoder<trackIn->getFilterParameterCount(filter, encoder))
			{
				updateKnob=encoder;

				int increment = checkDirection(positions[encoder], newPos);
				positions[encoder] = newPos;

				int* temp = trackIn->getFilterValue(filter, encoder, increment);

				showParameter2(trackIn->getFilterName(filter),trackIn->getFilterParameter(filter, encoder), temp);
				showFilterOption(filter, encoder);
					// trackIn->setParameter(encoder, newPos);
				 // showDataOptions(stepSelected);
			}
		}



	}


	void setGlobalParameter(byte encoder){
		long newPos= encoders[encoder]->read();

		if (newPos != positions[encoder] &&  newPos%4==0  ){
			updateKnob=encoder;

			int increment = checkDirection(positions[encoder], newPos);
			positions[encoder] = newPos;


			if (encoder == 0)
			{
				byte temp = trackIn->currentTrigger;
				//3 is the number of trigger classes
				trackIn->setCurrentTrigger(abs((temp+increment)%3));
				String gen = trackIn->getTriggerName();

				display->drawParameter(18, 0, 120, 20, gen, String(trackIn->currentTrigger));
			}


			if (encoder == 1)
			{
				byte temp = trackIn->getCurrentGenerator();
				//4 is the number of melodic classes

				trackIn->setCurrentGenerator(abs((temp+increment)%4));
				String gen = trackIn->melodicGenerators->melodicGens[trackIn->currentGenerator]->getName();

				display->drawParameter(18, 0, 120, 20, gen, String(trackIn->currentGenerator));
			}
				//4 is the number of filter classes

			if (encoder == 2)
			{
				byte temp = trackIn->getCurrentFilter(0);

				trackIn->setCurrentFilter(0, abs((temp+increment)%4));
				String gen = trackIn->filters->filters[trackIn->currentFilters[0]]->getName();
				display->drawParameter(18, 0, 120, 20, gen, String(trackIn->currentFilters[0]));
			}

			if (encoder == 3)
			{
				byte temp = trackIn->getCurrentFilter(1);

				trackIn->setCurrentFilter(1, abs((temp+increment)%4));
				String gen = trackIn->filters->filters[trackIn->currentFilters[1]]->getName();
				display->drawParameter(18, 0, 120, 20, gen, String(trackIn->currentFilters[1]));
			}

			if (encoder == 4)
			{
				byte temp = trackIn->getCurrentFilter(2);

				trackIn->setCurrentFilter(2, abs((temp+increment)%4));
				String gen = trackIn->filters->filters[trackIn->currentFilters[2]]->getName();
				display->drawParameter(18, 0, 120, 20, gen, String(trackIn->currentFilters[2]));
			}
			if (encoder == 5)
			{
				byte temp = trackIn->getCurrentFilter(3);

				trackIn->setCurrentFilter(3, abs((temp+increment)%4));
				String gen = trackIn->filters->filters[trackIn->currentFilters[3]]->getName();
				display->drawParameter(18, 0, 120, 20, gen, String(trackIn->currentFilters[3]));
			}




			stepSelected=encoder;

				// trackIn->setParameter(encoder, newPos);
			// showChain();
			lazyChanged=true;
		}



	}
		// void selectGlobalParameter(byte encoder){
		// 	long newPos= encoders[encoder]->read();

		// 	if (newPos != positions[encoder] &&  newPos%4==0  ){
		// 		stepSelected=encoder;

		// 	}
		// 	showChain();



		// }
	int checkDirection(long oldPos, long newPosToCheck ){
		// printControl();
		showChanged=false;
		changeMillis = millis()+showTime;
		if (oldPos<newPosToCheck)
		{
			Serial.print("+");
			return 1;
		}else{
			Serial.print("-");

			return -1;
		}


	}

	void tst(){


	}

	void showParameter(Parameter *par, int *value){

		if(par->type==true){

			display->drawParameter(18, 0, 120, 20,  par->name, String(*value));

		}else{

			display->drawParameter(18, 0, 120, 20,  par->name, par->optionsNames[*value]);

		}
	}
	void showParameter2(String name, Parameter *par, int *value){

		if(par->type==true){

			display->drawParameter(18, 0, 120, 20,  name+"|"+par->name, String(*value));

		}else{

			display->drawParameter(18, 0, 120, 20,  name+"|"+par->name, par->optionsNames[*value]);

		}
	}
		///SWING ETC..
	void showTrackOption(byte param){
		if(trackIn->parameters->parameters[param]->type==true){

			display->drawTextSquare(21*param, 57, 20, 9, trackIn->parameters->parameters[param]->shortName, String(*trackIn->getParameterValue(param,0)));

		}else{

			display->drawTextSquare(21*param, 57, 20, 9,trackIn->parameters->parameters[param]->shortName, trackIn->parameters->parameters[param]->optionsShortNames[*trackIn->getParameterValue(param,0)]);

		}
	}

	void showTrackOptions(){
		int count = 6;
		Parameter* tempArray[count];
		for(int i=0; i<count; i++){
			if (i==updateKnob)
			{

				if(trackIn->parameters->parameters[i]->type==true){

					display->drawTextSquare(21*i, 57, 20, 9, trackIn->parameters->parameters[i]->shortName, String(*trackIn->getParameterValue(i,0)));

				}else{

					display->drawTextSquare(21*i, 57, 20, 9,trackIn->parameters->parameters[i]->shortName, trackIn->parameters->parameters[i]->optionsShortNames[*trackIn->getParameterValue(i,0)]);



				}
			}

		}
		// showTrack();
	}
	String saveTrackOptions(byte itrack){
		String out="";

		int count = 6;
		Parameter* tempArray[count];
		for(int i=0; i<count; i++){
			

				if(ctracks[itrack]->parameters->parameters[i]->type==true){
					// out+= ctracks[itrack]->parameters->parameters[i]->name;
					// out+=":";
					out+=String(*ctracks[itrack]->getParameterValue(i,0));
					out+=":";
					// display->drawTextSquare(21*i, 57, 20, 9, ctracks[itrack]->parameters->parameters[i]->shortName, String(*ctracks[itrack]->getParameterValue(i,0)));

				}else{
					// out+= ctracks[itrack]->parameters->parameters[i]->name;
					// out+=":";
					out+=String(*ctracks[itrack]->getParameterValue(i,0));

					// out+=ctracks[itrack]->parameters->parameters[i]->optionsShortNames[*ctracks[itrack]->getParameterValue(i,0)];
					out+=":";
					// display->drawTextSquare(21*i, 57, 20, 9,ctracks[itrack]->parameters->parameters[i]->shortName, ctracks[itrack]->parameters->parameters[i]->optionsShortNames[*trackIn->getParameterValue(i,0)]);



				}
			

		}
		return out;
		// showTrack();
	}
	void showTrack(){
			// display->clearDisplay();
		if (trackIn->isPlaying==true)
		{
			display->drawParameterInverted(0, 0, 13, 20, " ", String(currentTrack+1));
			/* code */
		}else{

			display->drawParameter(0, 0, 13, 20, " ", String(currentTrack+1));

		}

		// updateKnob=0;
		// lazyChanged=true;


	}
		/// MELODIC

	void lazyScreenDisplay(byte knob){
		updateKnob = knob;
		if (lazyChanged  )
		{
			// Serial.print("lazy"+knob);
			updateKnob=updateKnob%6;
			if (mode==TRACK)
			{
				showDataOptions(stepSelected);
				showTrackOptions();
			}else{
				showChain();
			}
			if (updateKnob>4)
			{
				lazyChanged=false;
			}else{
				// Serial.print("++");

				updateKnob++;
			}
			showTrack();



		}
	}
	void showTriggerOption(byte param){
		byte count = trackIn->triggerGenerators->triggerGens[trackIn->currentTrigger]->getParameterCount();
		Parameter* tempArray[count];
		tempArray[param] =  trackIn->getTriggerParameter(param);
		if(tempArray[param]->type==true){

			display->drawTextSquare((21*param), 38, 20, 9, tempArray[param]->getShortName(), String(*trackIn->getTriggerValue(param,0)));

		}else{

			display->drawTextSquare((21*param), 38, 20, 9, tempArray[param]->getShortName(), tempArray[param]->optionsShortNames[*trackIn->getTriggerValue(param,0)]);

		}

	}
	String saveTriggerOption(byte itrack, byte param){
		String out="";

		byte count = ctracks[itrack]->triggerGenerators->triggerGens[ctracks[itrack]->currentTrigger]->getParameterCount();
		if (param<count)
		{

			Parameter* tempArray[count];
			tempArray[param] =  ctracks[itrack]->getTriggerParameter(param);
			if(tempArray[param]->type==true){

				// out+= tempArray[param]->getName();
				// out+=":";
				out+=String(*ctracks[itrack]->getTriggerValue(param,0));
				out+=":";

			}else{
				// out+= tempArray[param]->getName();
				// out+=":";
				out+=String(*ctracks[itrack]->getTriggerValue(param,0));
				// out+=  tempArray[param]->optionsShortNames[*trackIn->getTriggerValue(param,0)];
				out+=":";


			}
		}
		return out;
	}
	void showMelodicOption(byte param){
		byte count = trackIn->melodicGenerators->melodicGens[trackIn->currentGenerator]->getParameterCount();

		Parameter* tempArray[count];
		tempArray[param] =  trackIn->getMelodicParameter(param);

		if(tempArray[param]->type==true){

			display->drawTextSquare((21*param), 38, 20, 9, tempArray[param]->getShortName(), String(*trackIn->getMelodicValue(param,0)));

		}else{

			display->drawTextSquare((21*param), 38, 20, 9, tempArray[param]->getShortName(), tempArray[param]->optionsShortNames[*trackIn->getMelodicValue(param,0)]);

		}
	}
	String saveMelodicOption(byte itrack, byte param){
		String out="";
		byte count = ctracks[itrack]->melodicGenerators->melodicGens[ctracks[itrack]->currentGenerator]->getParameterCount();
		if (param<count)
		{
			

			Parameter* tempArray[count];
			tempArray[param] =  ctracks[itrack]->getMelodicParameter(param);

			if(tempArray[param]->type==true){
				// out+= tempArray[param]->getName();
				// out+=":";
				out+=String(*ctracks[itrack]->getMelodicValue(param,0));
				out+=":";

				// out+="\r\n";

			// display->drawTextSquare((21*param), 38, 20, 9, tempArray[param]->getShortName(), String(*ctracks[itrack]->getMelodicValue(param,0)));

			}else{
				// out+= tempArray[param]->getName();
				// out+=String(*ctracks[itrack]->getMelodicValue(param,0));
				out+=String(*ctracks[itrack]->getMelodicValue(param,0));
				out+=":";

				// out+= tempArray[param]->optionsShortNames[*ctracks[itrack]->getMelodicValue(param,0)];
				// out+="\r\n";

			// display->drawTextSquare((21*param), 38, 20, 9, tempArray[param]->getShortName(), tempArray[param]->optionsShortNames[*trackIn->getMelodicValue(param,0)]);

			}
			return out;

		}
	}
	void showFilterOption(byte filter, byte param){

		int count = trackIn->filters->filters[trackIn->currentFilters[filter]]->getParameterCount();
		Parameter* tempArray[count];
		tempArray[param] =  trackIn->getFilterParameter(filter, param);

		if(tempArray[param]->type==true){

			display->drawTextSquare((21*param), 38, 20, 9, tempArray[param]->getShortName(), String(*trackIn->getFilterValue(filter, param, 0)));

		}else{

			display->drawTextSquare((21*param), 38, 20, 9, tempArray[param]->getShortName(), tempArray[param]->optionsShortNames[*trackIn->getFilterValue(filter, param, 0)]);

		}
	}
	String saveFilterOption(byte itrack, byte filter, byte param){
		String out="";

		int count = ctracks[itrack]->filters->filters[ctracks[itrack]->currentFilters[filter]]->getParameterCount();
		if (param<count)
		{

			Parameter* tempArray[count];
			tempArray[param] =  ctracks[itrack]->getFilterParameter(filter, param);

			if(tempArray[param]->type==true){
				// out+= tempArray[param]->getName();
				out+= String(*ctracks[itrack]->getFilterValue(filter, param, 0));
				out+=":";

				// out+="\r\n";
			// display->drawTextSquare((21*param), 38, 20, 9, tempArray[param]->getShortName(), String(*ctracks[itrack]->getFilterValue(filter, param, 0)));

			}else{
				// out+= tempArray[param]->getName();
				out+= tempArray[param]->optionsShortNames[*ctracks[itrack]->getFilterValue(filter, param, 0)];
				out+=":";

				// out+="\r\n";
				// display->drawTextSquare((21*param), 38, 20, 9, tempArray[param]->getShortName(), tempArray[param]->optionsShortNames[*trackIn->getFilterValue(filter, param, 0)]);

			}
		}
			return out;


	}
	void showDataOptions(byte step){
		// Serial.println("showDataOptions");
		int npar=0;
		if (step==0)
		{
			int count = trackIn->triggerGenerators->triggerGens[trackIn->currentTrigger]->getParameterCount();
			
			Parameter* tempArray[count];
			// Parameter* temp=trackIn->getTriggerParameter(0);

			// int count = trackIn->triggerGenerators->triggerGens[trackIn->currentGenerator]->getParameterCount();

			for(int i=0; i<count; i++){

				if (i<count)
				{
					if (i==updateKnob)
					{
						showTriggerOption(i);
						// tempArray[i] =  trackIn->getTriggerParameter(i);
						// if(tempArray[i]->type==true){

						// 	display->drawTextSquare((21*i), 38, 20, 9, tempArray[i]->getShortName(), String(*trackIn->getTriggerValue(i,0)));

						// }else{

						// 	display->drawTextSquare((21*i), 38, 20, 9, tempArray[i]->getShortName(), tempArray[i]->optionsShortNames[*trackIn->getTriggerValue(i,0)]);

						// }
					}
				}

				npar++;
			}
			if (npar<6)
			{
				
				display->fillBlank((21*npar), 38, 3+(6-npar)*20, 9);

				
			}
		}else if (step==1){
			int count = trackIn->melodicGenerators->melodicGens[trackIn->currentGenerator]->getParameterCount();
			Parameter* tempArray[count];


			for(int i=0; i<count; i++){
				if (i==updateKnob)
				{
					showMelodicOption(i);
					// tempArray[i] =  trackIn->getMelodicParameter(i);

					// if(tempArray[i]->type==true){

					// 	display->drawTextSquare((21*i), 38, 20, 9, tempArray[i]->getShortName(), String(*trackIn->getMelodicValue(i,0)));

					// }else{

					// 	display->drawTextSquare((21*i), 38, 20, 9, tempArray[i]->getShortName(), tempArray[i]->optionsShortNames[*trackIn->getMelodicValue(i,0)]);

					// }
				}

				npar++;
			}
			if (npar<6)
			{
				
				display->fillBlank((21*npar), 38, 3+(6-npar)*20, 9);

				
			}
		}else if (step==2){
			int count = trackIn->filters->filters[trackIn->currentFilters[0]]->getParameterCount();
			Parameter* tempArray[count];

			for(int i=0; i<count; i++){
				if (i==updateKnob)
				{
					showFilterOption(0,i);
					// tempArray[i] =  trackIn->getFilterParameter(0,i);
					// // Serial.print("stepSelected>");
					// // Serial.println(stepSelected);
					// // Serial.print("type>");
					// // Serial.println(tempArray[i]->type);
					// // Serial.print("value>");
					// // Serial.println(*trackIn->getFilterValue(0, 0, 0));

					// if(tempArray[i]->type==true){

					// 	display->drawTextSquare((21*i), 38, 20, 9, tempArray[i]->getShortName(), String(*trackIn->getFilterValue(0, i, 0)));

					// }else{

					// 	display->drawTextSquare((21*i), 38, 20, 9, tempArray[i]->getShortName(), tempArray[i]->optionsShortNames[*trackIn->getFilterValue(0, i, 0)]);

					// }
				}

				npar++;
			}
			if (npar<6)
			{
				
				display->fillBlank((21*npar), 38, 3+(6-npar)*20, 9);

				
			}
		}else if (step==3){
			int count = trackIn->filters->filters[trackIn->currentFilters[1]]->getParameterCount();
			Parameter* tempArray[count];

			for(int i=0; i<count; i++){
				if (i==updateKnob)
				{
					showFilterOption(1,i);
					// tempArray[i] =  trackIn->getFilterParameter(1,i);
					// // Serial.print("stepSelected>");
					// // Serial.println(stepSelected);
					// // Serial.print("type>");
					// // Serial.println(tempArray[i]->type);
					// // Serial.print("value>");
					// // Serial.println(*trackIn->getFilterValue(1, 0, 0));

					// if(tempArray[i]->type==true){

					// 	display->drawTextSquare((21*i), 38, 20, 9, tempArray[i]->getShortName(), String(*trackIn->getFilterValue(1, i, 0)));

					// }else{

					// 	display->drawTextSquare((21*i), 38, 20, 9, tempArray[i]->getShortName(), tempArray[i]->optionsShortNames[*trackIn->getFilterValue(1, i, 0)]);

					// }
				}

				npar++;
			}
			if (npar<6)
			{
				
				display->fillBlank((21*npar), 38, 3+(6-npar)*20, 9);

				
			}
		}else if (step==4){
			int count = trackIn->filters->filters[trackIn->currentFilters[2]]->getParameterCount();
			Parameter* tempArray[count];

			for(int i=0; i<count; i++){
				if (i==updateKnob)
				{	
					showFilterOption(2,i);
					// tempArray[i] =  trackIn->getFilterParameter(2,i);
					// // Serial.print("stepSelected>");
					// // Serial.println(stepSelected);
					// // Serial.print("type>");
					// // Serial.println(tempArray[i]->getShortName());
					// // Serial.print("value>");
					// // Serial.println(*trackIn->getFilterValue(1, 0, 0));

					// if(tempArray[i]->type==true){

					// 	display->drawTextSquare((21*i), 38, 20, 9, tempArray[i]->getShortName(), String(*trackIn->getFilterValue(2, i, 0)));

					// }else{

					// 	display->drawTextSquare((21*i), 38, 20, 9, tempArray[i]->getShortName(), tempArray[i]->optionsShortNames[*trackIn->getFilterValue(1, i, 0)]);

					// }
				}

				npar++;
			}
			if (npar<6)
			{
				
				display->fillBlank((21*npar), 38, 3+(6-npar)*20, 9);

				
			}
		}else if (step==5){
			int count = trackIn->filters->filters[trackIn->currentFilters[3]]->getParameterCount();
			Parameter* tempArray[count];

			for(int i=0; i<count; i++){
				if (i==updateKnob)
				{
					showFilterOption(3,i);
					// tempArray[i] =  trackIn->getFilterParameter(3,i);
					// // Serial.print("stepSelected>");
					// // Serial.println(stepSelected);
					// // Serial.print("type>");
					// // Serial.println(tempArray[i]->getShortName());
					// // Serial.print("value>");
					// // Serial.println(*trackIn->getFilterValue(1, 0, 0));

					// if(tempArray[i]->type==true){

					// 	display->drawTextSquare((21*i), 38, 20, 9, tempArray[i]->getShortName(), String(*trackIn->getFilterValue(3 , i, 0)));

					// }else{

					// 	display->drawTextSquare((21*i), 38, 20, 9, tempArray[i]->getShortName(), tempArray[i]->optionsShortNames[*trackIn->getFilterValue(1, i, 0)]);

					// }
				}

				npar++;
			}
			if (npar<6)
			{
				
				display->fillBlank((21*npar), 38, 3+(6-npar)*20, 9);

				
			}
		}

		// showTrackOptions();
		// display -> drawPixelTempo(tempoState);

	}
	void showChain(){
		String genStr[6]={"SQ>","MD>","F1>","F2>","F3>","F4>"};

		String gens;
		for (int i = 0; i < 6; ++i)
		{
				// Serial.print("updateKnob");
				// Serial.println(updateKnob);
				// Serial.print("i");
				// Serial.println(i);


			if (i==updateKnob)
			{

				String gen = trackIn->melodicGenerators->melodicGens[0]->getName();
				if (i==0)
				{
					gens = trackIn->triggerGenerators->triggerGens[trackIn->currentTrigger]->getShortName();

				}else if(i==1) {

					gens = trackIn->melodicGenerators->melodicGens[trackIn->currentGenerator]->getShortName();

				}else if(i==2){
					// Serial.print("stepSelected");
					// Serial.println(trackIn->currentFilters[0]);
					gens = trackIn->filters->filters[trackIn->currentFilters[0]]->getShortName();

				}else if(i==3){
					// Serial.print("stepSelected");
					// Serial.println(trackIn->currentFilters[1]);
					gens = trackIn->filters->filters[trackIn->currentFilters[1]]->getShortName();

				}else if(i==4){
					// Serial.print("stepSelected");
					// Serial.println(trackIn->currentFilters[2]);
					gens = trackIn->filters->filters[trackIn->currentFilters[2]]->getShortName();

				}else if(i==5){
					// Serial.print("stepSelected");
					// Serial.println(trackIn->currentFilters[3]);
					gens = trackIn->filters->filters[trackIn->currentFilters[3]]->getShortName();

				}

				if (i!=stepSelected)
				{
					display->drawTextSquare(21*i, 57, 20, 9,  genStr[i], gens);

				}else{

					display->drawTextSquareInverted(21*i, 57, 20, 9,  genStr[i], gens);

				}
			}
		}

	// int count = trackIn->melodicGenerators->melodicGens[trackIn->currentGenerator]->getParameterCount();
	  //  		Parameter* tempArray[count];
	  //  		for(int i=0; i<count; i++){

	  //        tempArray[i] =  trackIn->melodicGenerators->melodicGens[trackIn->currentGenerator]->getParameter(i);
	  //        if(tempArray[i]->type==true){

	  //        	display->drawTextSquare(21*i, 57, 20, 9, tempArray[i]->shortName, String(*trackIn->getParameterValue(i,0)));

	  //        }else{

	  //        	display->drawTextSquare(21*i, 57, 20, 9, tempArray[i]->shortName, tempArray[i]->optionsShortNames[tempArray[i]->value]);

	  //        }

	  //  	 	}
			// showTrackOptions();
			// display -> drawPixelTempo(tempoState);

	}
	void showPixelTempo(){
		if (tempoState == false){
			tempoState=true;
				// this->drawPixel(126, 5, WHITE);
		}
		else
		{
			tempoState=false;
		}

	}

	  // virtual const String classname() { return "Controlr";}
};
