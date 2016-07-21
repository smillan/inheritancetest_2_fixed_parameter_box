#include <stack>
#include <vector>
#include <iterator>
#include <Streaming.h>
#include <Bounce.h>
// #include "Track.h"
#include "Orsini.h"
#include <MIDI.h>
#define ENCODER_OPTIMIZE_INTERRUPTS
#include <Encoder.h>

#include <SD.h>
#include <SPI.h>
#include <Wire.h>
#include "Adafruit_GFX.h"
#include "Adafruit_SSD1306.h"
#include "Oled_Screen.h"
#include "Parameter.h"
#include "Scales.h"

// #include "Parameter.h"
Oled_Screen screen(17, 16, 19, 28, 18);

Orsini global;
MIDI_Class MIDI;



unsigned long debugtime = 11400 ;
unsigned long previousMillis = 0;
void setup() {
  SPI.setMOSI(7);
  SPI.setSCK(14);

  int crashCountdown;
  if (!(SD.begin(10))) {
    while (!(SD.begin(10))) {
      digitalWrite(13, HIGH);
      delay(100);
      digitalWrite(13, LOW);

      delay(100);
      crashCountdown++;
      // if (crashCountdown > 6)     reBoot();

    }
  }

  MIDI.begin(MIDI_CHANNEL_OMNI);
  MIDI.setHandleClock(HandleClock);
  usbMIDI.setHandleRealTimeSystem(RealTimeSystem);
  MIDI.setHandleNoteOn(HandleNoteOn);
  MIDI.setHandleNoteOff(HandleNoteOff);
  MIDI.setHandleStart(starto);
  MIDI.setHandleStop(reseto);
  global.track0.addMidi(MIDI);
  global.track1.addMidi(MIDI);
  global.track2.addMidi(MIDI);
  global.track3.addMidi(MIDI);
  global.control.addDisplay(screen);
  Serial.println("rfl = " + String(freeRam()));

}
void RealTimeSystem(byte realtimebyte) {

  if (realtimebyte == 248) {
    HandleClock();
  }

  // if(counter == 12) { digitalWrite(11, LOW); } }

  if (realtimebyte == 250 || realtimebyte == 251) {
    starto();
  }

  if (realtimebyte == 252) {
    reseto();
  }

}

void loop() {
  MIDI.read();
  usbMIDI.read();
  global.run();

  // global.displayControl();

  // control();
  unsigned long currentMillis = millis();




  if (currentMillis - previousMillis > debugtime) {

    // save the last time you blinked the LED
    previousMillis = currentMillis;
    // global.control.printBounces();
    // global.control.printControl();

    // TestStack::RunTest();
    Serial.println("rfl = " + String(freeRam()));
    // global.generators.getParams();

    // global.track0.melody.nextStep();
    // global.track0.melody.nextStep();
    // global.track0.melody.notes_selector->trik();
    // global.track0.melody.notes_selector->parameters[0]->tick();
    // global.track0.melody.notes_selector->getNextStep();
    // global.track0.melody.notes_selector->nextStep(0);
    // global.track0.melody.changeGenerator(random(0,2));
    // int count = global.track0.melody.notes_selector->getParameterCount();

    // Parameter* temp=  global.track0.melody.notes_selector->getParameter(0);

    // Parameter* tempArray[count];

    // for(int i=0; i<count; i++){
    //      tempArray[i] =  global.track0.melody.notes_selector->getParameter(i);
    // }


  }

  // put your main code here, to run repeatedly:

}

void HandleNoteOn(byte channel, byte note, byte velocity) {
  Serial.print("ofwfewefwfpj");
  // Do whatever you want when you receive a Note On.
  // digitalWrite(8, HIGH);


  // Try to keep your callbacks short (no delays ect) as the contrary would slow down the loop()
  // and have a bad impact on real-time performance.
}

void HandleNoteOff(byte channel, byte note, byte velocity) {
  Serial.print("ofwfewefwfpj");

  // Do whatever you want when you receive a Note On.
  // digitalWrite(8, LOW);


  // Try to keep your callbacks short (no delays ect) as the contrary would slow down the loop()
  // and have a bad impact on real-time performance.
}

void HandleClock() {
  // global.control.showPixelTempo();
  global.midiClockTick();
  // Serial.print("clok");
}
void reseto() {

  // global.reset();
  Serial.println("reset");



}
void starto() {
  // reseto();

  // Serial.println("start1");


  // timer.midiClockTick();
  global.start();

}
uint32_t freeRam() { // for Teensy 3.0
  uint32_t stackTop;
  uint32_t heapTop;

  // current position of the stack.
  stackTop = (uint32_t) &stackTop;

  // current position of heap.
  void* hTop = malloc(1);
  heapTop = (uint32_t) hTop;
  free(hTop);

  // The difference is the free, available ram.
  return stackTop - heapTop;
}
