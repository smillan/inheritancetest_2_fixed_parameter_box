#include <Arduino.h>
// #include "Track.h"


Sd2Card card;
SdVolume volume;
SdFile root;
// SdFile ffil;
File settingsFile;
// File myFile;
class SaveToSSD {


protected:

public:


	byte midiClockDiv=6;

	SaveToSSD( )
	{


	}

		// void notify(Track& tr){

		// 	&tr.tick()


		// }


	File readSDSettings(){
		char character;
		String settingName;
		String settingValue;
		settingsFile = SD.open("orsini.txt");
		return settingsFile;
		// if (settingsFile) {
		// 	Serial.print("settingsFile");
		// 	while (settingsFile.available()) {
		// 			character = settingsFile.read();
		// 			// Serial.print(character);
		// 			// delay(1);
		// 	}
		// 		character = settingsFile.read();
		// 		while(character != '='){
		// 			settingName = settingName + character;
		// 			character = settingsFile.read();
		// 		}
		// 	// 	character = settingsFile.read();
		// 	// 	while(character != '\n'){
		// 	// 		settingValue = settingValue + character;
		// 	// 		character = settingsFile.read();
		// 	// 		if(character == '\n'){
						
		// 	// 			//Debuuging Printing
		// 	// 			Serial.print("Name:");
		// 	// 			Serial.println(settingName);
		// 	// 			Serial.print("Value :");
		// 	// 			Serial.println(settingValue);

		// 	// 			// Apply the value to the parameter
		// 	// 			// applySetting(settingName,settingValue);
		// 	// 			// Reset Strings
		// 	// 			settingName = "";
		// 	// 			settingValue = "";
		// 	// 		}
		// 	// 	}
		// 	// }
		// // close the file:
		// 	settingsFile.close();
			// Serial.println("closed");

		// } 
		// else {
		// // if the file didn't open, print an error:
		// 	// Serial.println("error opening settings.txt");
		// }
	}
	void sdOpen(){
		SD.remove("orsini.txt");
		settingsFile = SD.open("orsini.txt", FILE_WRITE);
	}

	void sdClose(){
			settingsFile.close();
	}

	void save(String data){
		

	// if the file opened okay, write to it:
		if (settingsFile) {
			// Serial.print("Writing to stee.txt...");
			settingsFile.print(data);
	// close the file:
		
			// Serial.println("done.");
		} else {
		// if the file didn't open, print an error:
			// Serial.println("error opening test.txt");
		}
		// Serial.print("done");
	}

	void test(){
		if (!card.init(SPI_HALF_SPEED, 10)) {
			// Serial.println("initialization failed. Things to check:");
			// Serial.println("* is a card is inserted?");
			// Serial.println("* Is your wiring correct?");
			// Serial.println("* did you change the chipSelect pin to match your shield or module?");
			return;
		} else {
			// Serial.println("Wiring is correct and a card is present."); 
		}
	// OPEN SD CARD 
	// print the type of card
		// Serial.print("\nCard type: ");
		switch(card.type()) {
			case SD_CARD_TYPE_SD1:
			// Serial.println("SD1");
			break;
			case SD_CARD_TYPE_SD2:
			// Serial.println("SD2");
			break;
			case SD_CARD_TYPE_SDHC:
			// Serial.println("SDHC");
			break;
			default:
			Serial.println("");
		}

	// Now we will try to open the 'volume'/'partition' - it should be FAT16 or FAT32
		if (!volume.init(card)) {
			// Serial.println("Could not find FAT16/FAT32 partition.\nMake sure you've formatted the card");
			return;
		}


	// print the type and size of the first FAT-type volume
		uint32_t volumesize;
		// Serial.print("\nVolume type is FAT");
		Serial.println(volume.fatType(), DEC);
		Serial.println();

	volumesize = volume.blocksPerCluster();    // clusters are collections of blocks
	volumesize *= volume.clusterCount();       // we'll have a lot of clusters
	volumesize *= 512;                            // SD card blocks are always 512 bytes
	// Serial.print("Volume size (bytes): ");
	// Serial.println(volumesize);
	// Serial.print("Volume size (Kbytes): ");
	volumesize /= 1024;
	// Serial.println(volumesize);
	// Serial.print("Volume size (Mbytes): ");
	volumesize /= 1024;
	// Serial.println(volumesize);

	
	// Serial.println("\nFiles found on the card (name, date and size in bytes): ");
	root.openRoot(volume);
	
	// list all files in the card with date and size
	root.ls(LS_R | LS_DATE | LS_SIZE);

}


};
