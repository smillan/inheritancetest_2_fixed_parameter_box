#ifndef Track_h
#define Track_h
#include <Arduino.h>
#include "Triggering.h"
#include "TrackData.h"
#include "MelodicGenerators.h"
#include "ParameterValues.h"

#include "MidiHandle.h"

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "Oled_Screen.h"
#include "Parameter.h"
#include "Filters.h"
#include "TrackParameters.h"

#define TEMP_MAX 10
// #include "Clock.h"

class Track : public TrackData, public MidiHandle{


	protected:
		// 96, 48, 32, 24, 16, 12,8,6,4,3,2, 1
		byte clockDivisions[12]={1,2,3,4,6,8,12,16,24,32,48,64};
		public:

		TrackParameters* parameters;

		ParameterValues melodicValues;
		ParameterValues triggerValues;
	 	ParameterValues trackValues; // SWING LOOPSIZE CLOCKDIV SCALE
	 	ParameterValues filterValues[4]; // SWING LOOPSIZE CLOCKDIV SCALE

	 	MelodicGenerators* melodicGenerators;
	 	Triggering* triggerGenerators;
	 	Filters* filters;

	 	byte currentGenerator=0;
	 	byte currentFilters[4]={0,0,0,0};
	 	byte currentTrigger=0;
	 	byte currentScale=0;
	 	// byte loopSize=16;
	 	// byte offset=16;
	 	bool isPlaying=true;


	 	Oled_Screen* display;
	 	int tempNote[TEMP_MAX];

		byte tempVel[TEMP_MAX];

		int tempDur[TEMP_MAX];

		byte tempOct[TEMP_MAX];

		byte tempSeq=1;
		enum SeqModes {SEQUENCE, STEP};
		SeqModes seqMode = SEQUENCE;

	 	byte trackNumber=0;
	 	Track()
	 	{
			// init();

		}
		void init(){
			getTriggerValues();
			getMelodicValues();
			getFilterValues(0);
			getFilterValues(1);
			getFilterValues(2);
			getFilterValues(3);
			getTrackValues();
		}


		Parameter* getParameter(byte parameter){
			return parameters->parameters[parameter];

		}
		Parameter* getMelodicParameter(byte parameter){
			return melodicGenerators->melodicGens[currentGenerator]->getParameter(parameter);

		}
		Parameter* getTriggerParameter(byte parameter){
			return triggerGenerators->triggerGens[currentTrigger]->getParameter(parameter);

		}
		Parameter* getFilterParameter(byte filter, byte parameter){
			return filters->filters[currentFilters[filter]]->getParameter(parameter);

		}


		int getTriggerParameterCount(byte parameter){

			return triggerGenerators->triggerGens[currentTrigger]->getParameterCount();
		}

		int getMelodicParameterCount(byte parameter){

			return melodicGenerators->melodicGens[currentTrigger]->getParameterCount();
		}

		int getFilterParameterCount(byte filter, byte parameter){

			return filters->filters[currentFilters[filter]]->getParameterCount();
		}

		int* getParameterValue(byte parameter, int increment){
		//GET THE INCEREMENT FROM PARAMETER LIST
			int max = parameters->parameters[parameter]->max;
			int min = parameters->parameters[parameter]->min;
			int incrementPreset = parameters->parameters[parameter]->increment;
			trackValues.values[parameter] = min( max((trackValues.values[parameter]+(increment * incrementPreset)), min), max-1);
			// trackValues.values[parameter]= trackValues

			return &trackValues.values[parameter];

		}

		int* getMelodicValue(byte parameter, int increment){
			//GET THE INCEREMENT FROM PARAMETER LIST
			// Serial.print("getMelodicValue -> ");
			// Serial.println(trackNumber);
			int max = melodicGenerators->melodicGens[currentGenerator]->getParameter(parameter)->max;
			int min = melodicGenerators->melodicGens[currentGenerator]->getParameter(parameter)->min;
			int incrementPreset =  melodicGenerators->melodicGens[currentGenerator]->getParameter(parameter)->increment;
			melodicValues.values[parameter] = min(max((melodicValues.values[parameter]+(increment * incrementPreset)), min), max-1) ;
			if (seqMode==STEP)
			{
				// melodicGenerators->melodicGens[currentGenerator]->generateStep(part_data.step, melodicValues.values, part_data.notes, part_data.velocities, part_data.durations, part_data.octaves, currentScale );

			}else{

				// melodicGenerators->melodicGens[currentGenerator]->generateSequence(melodicValues.values,part_data.step, part_data.notes, part_data.velocities, part_data.durations,part_data.octaves, currentScale );


			}
			// melodicGenerators->melodicGens[currentGenerator]->generateSequence(melodicValues.values, part_data.notes, part_data.velocities, part_data.durations, currentScale );
			// // trackValues.values[parameter]= trackValues

			return &melodicValues.values[parameter];

					}

		int* setMelodicValue(byte parameter, int increment){
					//GET THE INCEREMENT FROM PARAMETER LIST
					// Serial.print("setMelodicValue -> ");
					// Serial.println(trackNumber);
					int max = melodicGenerators->melodicGens[currentGenerator]->getParameter(parameter)->max;
					int min = melodicGenerators->melodicGens[currentGenerator]->getParameter(parameter)->min;
					int incrementPreset =  melodicGenerators->melodicGens[currentGenerator]->getParameter(parameter)->increment;
					melodicValues.values[parameter] = min(max((melodicValues.values[parameter]+(increment * incrementPreset)), min), max-1) ;
					if (seqMode==STEP)
					{
						melodicGenerators->melodicGens[currentGenerator]->generateStep(part_data.step, melodicValues.values, part_data.notes, part_data.velocities, part_data.durations, part_data.octaves, currentScale );

					}else{

						melodicGenerators->melodicGens[currentGenerator]->generateSequence(melodicValues.values,part_data.step, part_data.notes, part_data.velocities, part_data.durations,part_data.octaves, currentScale );


					}
					// melodicGenerators->melodicGens[currentGenerator]->generateSequence(melodicValues.values, part_data.notes, part_data.velocities, part_data.durations, currentScale );
					// // trackValues.values[parameter]= trackValues

					return &melodicValues.values[parameter];

		}

		void generateMelodic(){
			Serial.println("genmelo");

			if (seqMode==STEP)
			{
				melodicGenerators->melodicGens[currentGenerator]->generateStep(part_data.step, melodicValues.values, part_data.notes, part_data.velocities, part_data.durations, part_data.octaves, currentScale );

			}else{

				melodicGenerators->melodicGens[currentGenerator]->generateSequence(melodicValues.values,part_data.step, part_data.notes, part_data.velocities, part_data.durations,part_data.octaves, currentScale );


			}

		}
		void generateTrigger(){
			Serial.println("gentrig");

			if (seqMode==STEP)
			{
				
				triggerGenerators->triggerGens[currentTrigger]->generateStep(part_data.step, triggerValues.values, part_data.sequence);
			}else{
				
				triggerGenerators->triggerGens[currentTrigger]->generateSequence(triggerValues.values, part_data.sequence);


			}

		}

		int* getTriggerValue(byte parameter, int increment){
			//GET THE INCEREMENT FROM PARAMETER LIST
			int max = triggerGenerators->triggerGens[currentTrigger]->getParameter(parameter)->max;
			int min = triggerGenerators->triggerGens[currentTrigger]->getParameter(parameter)->min;
			int incrementPreset =  triggerGenerators->triggerGens[currentTrigger]->getParameter(parameter)->increment;
			triggerValues.values[parameter] = min(max((triggerValues.values[parameter]+(increment * incrementPreset)), min  ), max) ;
			if (seqMode==STEP)
			{
				
				// triggerGenerators->triggerGens[currentTrigger]->generateStep(part_data.step, triggerValues.values, part_data.sequence);
			}else{
				
				// triggerGenerators->triggerGens[currentTrigger]->generateSequence(triggerValues.values, part_data.sequence);


			}
			// // trackValues.values[parameter]= trackValues
			// Serial.print("name >");
			// Serial.println(triggerGenerators->triggerGens[currentTrigger]->getParameter(parameter)->getName);

			return &triggerValues.values[parameter];

		}
		int* getFilterValue(byte filter, byte parameter, int increment){
			//GET THE INCEREMENT FROM PARAMETER LIST
			int max = filters->filters[currentFilters[filter]]->getParameter(parameter)->max;
			int min = filters->filters[currentFilters[filter]]->getParameter(parameter)->min;
			int incrementPreset =  filters->filters[currentFilters[filter]]->getParameter(parameter)->increment;
			filterValues[filter].values[parameter] = min(max((filterValues[filter].values[parameter]+(increment * incrementPreset)), min  ), max) ;
			// filters->filters[currentFilters[filter]]->generateSequence(filterValues[filter].values, part_data.sequence);
			// // trackValues.values[parameter]= trackValues
			// Serial.print("name >");
			// Serial.println(triggerGenerators->triggerGens[currentTrigger]->getParameter(parameter)->getName);

			return &filterValues[filter].values[parameter];

		}


		byte getCurrentGenerator(){
			return currentGenerator;


		}
		byte getCurrentTrigger(){
			return currentGenerator;
		}
		byte getCurrentFilter(byte filter){
			return currentFilters[filter];
		}


		void setCurrentGenerator(byte newGen){
			if (currentGenerator!=newGen){
				currentGenerator=newGen;
				getMelodicValues();

			};

			// int max= sizeof(melodicValues.values) / sizeof(melodicValues.values[ 0 ]);
		}
		void setCurrentTrigger(byte newTrig){
			if (currentTrigger!=newTrig) currentTrigger=newTrig;
			getTriggerValues();
			// int max= sizeof(melodicValues.values) / sizeof(melodicValues.values[ 0 ]);
		}
		void setCurrentFilter(byte filter, byte newTrig){
			if (currentFilters[filter]!=newTrig) currentFilters[filter]=newTrig;
			getFilterValues(filter);
			// int max= sizeof(melodicValues.values) / sizeof(melodicValues.values[ 0 ]);
		}


		void getMelodicValues(){
			// melodicValues.clear();

				int nPars = melodicGenerators->melodicGens[currentGenerator]->getParameterCount();
				for (int i = 0; i < nPars; ++i)
				{
					Parameter* temp= melodicGenerators->melodicGens[currentGenerator]->getParameter(i);
					melodicValues.addValue(i, temp->preset);
			}

		}

		void getTriggerValues(){
			// melodicValues.clear();

			int nPars = triggerGenerators->triggerGens[currentTrigger]->getParameterCount();
			for (int i = 0; i < nPars; ++i)
			{
				Parameter* temp= triggerGenerators->triggerGens[currentTrigger]->getParameter(i);
				// Serial.println(temp->preset)
				triggerValues.addValue(i, temp->preset);
			}

		}

		void getFilterValues(byte filter){
			// melodicValues.clear();

				int nPars = filters->filters[currentFilters[filter]]->getParameterCount();
				for (int i = 0; i < nPars; ++i)
				{
					Parameter* temp= filters->filters[currentFilters[filter]]->getParameter(i);
					filterValues[filter].addValue(i, temp->preset);
			}

		}

		String getMelodicName(){
			String name = melodicGenerators->melodicGens[currentGenerator]->getName();
			return name;
		}
		String getTriggerName(){
				String name = triggerGenerators->triggerGens[currentTrigger]->getName();
				return name;
			}
		String getFilterName(byte filter){
				String name = filters->filters[currentFilters[filter]]->getName();
				return name;
			}

		void getTrackValues(){
			int nPars = 5;
			for (int i = 0; i < nPars; ++i)
			{
				int temp= parameters->parameters[i]->preset;
				trackValues.addValue(i, temp);
			}

		}

		void setTrackVariables()
		{
			swingAmount=trackValues.values[0];
			currentScale=trackValues.values[1];
			melodicGenerators->melodicGens[currentGenerator]->generateSequence(melodicValues.values, part_data.step, part_data.notes, part_data.velocities, part_data.durations,part_data.octaves, 0);
			
			if (_clockCounter%16==0)
			{
				clockDivider=clockDivisions[trackValues.values[2]]*3;
			}

			part_data.offset=trackValues.values[3];
			part_data.loopSize=trackValues.values[4];
			part_data.octave=trackValues.values[5];

		}

		void addParameters(TrackParameters& param)
		{
			parameters=&param;
		}
		void setChannel(byte chan){

			part_data.channel=chan;
		}

		void addGens(MelodicGenerators& gens){
			melodicGenerators=&gens;
			melodicGenerators->melodicGens[0]->generateSequence(melodicValues.values, part_data.step, part_data.notes, part_data.velocities, part_data.durations,part_data.octaves, 0);

		}
		void addTrigs(Triggering& trigs){

			triggerGenerators=&trigs;
			triggerGenerators->triggerGens[0]->generateSequence(triggerValues.values, part_data.sequence);
		}

		void addFilters(Filters& flt){

			filters=&flt;
		}

		void tick(){

				// midiLoop();
			// playNotes()
			tickMidi();



			// Serial.println();
			// Serial.println();
			// Serial.println();
			// if()
			// display->drawPixelTempo(_clockCounter%2);
				// Serial.print("STEP > ");
				// Serial.println(part_data.step);
				// Serial.print("clock > ");
				// Serial.println(_clockCounter);
			if ((_clockCounter % (clockDivider)) == 0 ) {
				// for (int i = 0; i < 128; ++i)
				// {

				// 	Serial.print("| ");
				// 	// Serial.print(i);
				// 	// Serial.print(" > ");
				// 	Serial.print(part_data.sequence[i]);
				// 	Serial.print(", ");

				// }
				// Serial.println();
				// Serial.print("TRACK - ");
				// Serial.print(trackNumber);
				// Serial.print("STEP > ");
				// Serial.print(part_data.step);
				// Serial.print("SEQ > ");
				// Serial.print(part_data.sequence[part_data.step]);

				// Serial.print("NOTE > ");
				// Serial.println(part_data.notes[part_data.step]);
				// Serial.print("VEL > ");
				// Serial.println(part_data.velocities[part_data.step]);
				// Serial.print("DUR > ");
				// Serial.println(part_data.durations[part_data.step]);
				// Serial.print("octave > ");
				// Serial.println(part_data.octave);
				// Serial.print("channel > ");
				// Serial.println(part_data.channel);
				// Serial.println();
				// Serial.println();
			 	// int step=part_data.step;
			 	byte stepOffset=abs((part_data.step-part_data.offset)%128)%part_data.loopSize;

			 	applyNoteFilters(stepOffset);
			 	// 	Serial.print("stepbool > ");
					// Serial.println(tempSeq);
					// Serial.print("seqstep > ");
					// Serial.println(stepOffset);
			 	for (int i = 0; i < 5; ++i)
			 	{
			 		
			 		if (tempSeq!=0 && tempDur[i]>0)
			 		{
						// Serial.println("---intick---");

			 		// 	Serial.print("i > ");
						// Serial.println(i);
						// Serial.print("note > ");
						// Serial.println(tempNote[i]);
						// Serial.print("Octacte > ");
						// Serial.println(tempOct[i]);
						// Serial.print("vel > ");
						// Serial.println(tempVel[i]);
						// Serial.print("dur > ");
						// Serial.println(tempDur[i]);
						// Serial.print("dur > ");
						// Serial.println(part_data.durations[part_data.step]);
						// Serial.println("------");

			 			// stepOffset,
					 	// 	0,
					 	// 	tempVel[i],
					 	// 	tempDur[i],
					 	// 	part_data.octave,
					 	// 	part_data.channel
			 			notesOnTick(
					 		stepOffset,
					 		tempNote[i],
					 		tempVel[i],
					 		tempDur[i],
					 		tempOct[i]+part_data.octave,
					 		part_data.channel
				 		);
			 		}
			 	}
			 		//
			 	if (part_data.sequence[stepOffset]==1)
			 	{
			 		// notesOnTick(
					 // 		stepOffset,
					 // 		part_data.notes[stepOffset]-12,
					 // 		part_data.velocities[stepOffset],
					 // 		part_data.durations [stepOffset],
					 // 		part_data.octave,
					 // 		part_data.channel
				 	// 	);


			 	}
			 	part_data.step=((part_data.step)+1)%128;
			}
			_clockCounter++;
		}

		void firstFilterNote(byte filter,byte nStep){

			filters->filters[currentFilters[filter]]->doProcessing(filterValues[filter].values, _clockCounter, nStep, part_data.sequence, part_data.notes, part_data.velocities, part_data.octaves, part_data.durations);

		}
		void filterFilteredNote(byte filter, byte step, byte seqStep, byte note, byte velocity,byte octave, byte duration){

			filters->filters[currentFilters[filter]]->doProcessingSingle(filterValues[filter].values, _clockCounter, step, seqStep, note, velocity, octave, duration);

		}


		int getFilteredNote(byte filter, byte note){

			return filters->filters[currentFilters[filter]]->getProcessedNote(note);

		}
		int getFilteredSeq(byte filter){

			return filters->filters[currentFilters[filter]]->getProcessedSeq(0);

		}
		int getFilteredVel(byte filter, byte note){

			return filters->filters[currentFilters[filter]]->getProcessedVelocity(note);

		}
		int getFilteredDur(byte filter, byte note){

			return filters->filters[currentFilters[filter]]->getProcessedDuration(note);

		}
		int getFilteredOct(byte filter, byte note){

			return filters->filters[currentFilters[filter]]->getProcessedOctave(note);

		}
		int getFilteredCount(byte filter){

			return filters->filters[currentFilters[filter]]->getNoteCount();

		}


		void applyNoteFilters(byte step){
			tempNote[0]=part_data.notes[step];
			tempVel[0]=part_data.velocities[step];
			tempDur[0]=part_data.durations[step];
			tempOct[0]=part_data.octaves[step];

			tempSeq=part_data.sequence[step];
			// Serial.print("apply -> tempSec > ");
			// Serial.println(tempSeq);

			//get first filter count and process
			firstFilterNote(0, step);
			// //TOTAL NOTES PER TICK
			// int accum=-1;
			//get the actual notes and add them to the temp rray
			tempSeq = getFilteredSeq(0);

			for (int i = 0; i < 4; ++i)
			{
				if (i<getFilteredCount(0))
				{
					tempNote[i] = getFilteredNote(0,i);
					tempVel[i] = getFilteredVel(0,i);
					tempDur[i] = getFilteredDur(0,i);
					tempOct[i] = getFilteredOct(0,i);

				}else{

					tempNote[i] = 200;
					// tempSeq = 0;
					tempVel[i] = 0;
					tempDur[i] = 0;
				}
			}
			// get second filter count and process

			for (int f = 1; f < 4; ++f)
			{
				// Serial.print("apply -> name > ");
				// Serial.println( filters->filters[currentFilters[f]]->getName());
				filterFilteredNote(f, step, tempSeq, tempNote[0], tempVel[0], tempOct[0], tempDur[0]);

				tempSeq = getFilteredSeq(f);

				for (int i = 0; i < 4; ++i)
				{

					if (i<getFilteredCount(f))
					{
						tempNote[i] = getFilteredNote(f,i);
						tempVel[i] = getFilteredVel(f,i);
						tempDur[i] = getFilteredDur(f,i);
						tempOct[i] = getFilteredOct(f,i);
					}else{

						tempNote[i] = 200;
						// tempSeq = 0;
						tempVel[i] = 0;
						tempDur[i] = 0;
						tempOct[i] = 0;
					}
				}
			}

				// for (int i = 0; i < accum; ++i)
				// {
				// 	tempNote[accum] = getFilteredNote(1,i);
				// 	accum++;
				// }

				// nNewNotes = filterFilteredNote(2, part_data.step, tempNote[accum-1]);

				// for (int i = 0; i < nNewNotes; ++i)
				// {
				// 	tempNote[accum] = getFilteredNote(2,i);
				// 	accum++;
				// }

				// nNewNotes = filterFilteredNote(3, part_data.step, tempNote[accum-1]);

				// for (int i = 0; i < nNewNotes; ++i)
				// {
				// 	tempNote[accum] = getFilteredNote(3,i);
				// 	accum++;
				// }

				// newNote = filterFilteredNote(1, part_data.step, newNote);
				// newNote = filterFilteredNote(2, part_data.step, newNote);
				// newNote = filterFilteredNote(3, part_data.step, newNote);
				// return newNote;

		}

		void run(){
			playSwingNotes();
			setTrackVariables();
			noteKill();
			// Serial.print(trackNumber);
			// midi.run();
			// showTempo();
		}


		void showTempo(){
			display->drawTextSquare(0, 100, 20, 9, "tempo", String(ceil(tempo)));


		}


		void addDisplay(Oled_Screen& disp){
			display = &disp;
			display->init();
		}

		void start()
		{
			// midi.reset();
			// data.reset();

			part_data.step=0;
			_clockCounter=0;
			tick();
			// trigger.reset();
		}
		void stop()
		{
			// midi.reset();
			// data.reset();
			part_data.step=0;
			_clockCounter=0;
				// Serial.print("STEP");
				// Serial.println(part_data.step);
				// Serial.print("clock");
				// Serial.println(_clockCounter);
			// tick(0,0);
			// trigger.reset();
		}



		String classname() { return "track";}

	};
	#endif