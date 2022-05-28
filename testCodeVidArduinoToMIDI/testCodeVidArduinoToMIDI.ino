#include "MIDIUSB.h"
int val =0;
int previousState1 = 1;

void setup() {
  Serial.begin(9600);
}

void loop(){
  
  /*noteOn(0, 50, 100);  // channel, note, velocity
  MidiUSB.flush();
  delay(1000);
  noteOff(0, 50, 0);  // channel, note, velocity
  MidiUSB.flush();
  delay(1000);*/

  if (analogRead(A0)<20 && previousState1==1){
    noteOn(0, 50, 100);  // channel, note, velocity
    MidiUSB.flush();
    previousState1=0;
  }else {
    if (analogRead(A0)>20 && previousState1==0){
      noteOff(0, 50, 0);  // channel, note, velocity
      MidiUSB.flush();
      previousState1=1;
    }
  }
  
  val = analogRead(A0);
  Serial.println(val);
}

void noteOn(byte channel, byte pitch, byte velocity) {

  midiEventPacket_t noteOn = {0x09, 0x90, pitch, velocity};

  MidiUSB.sendMIDI(noteOn);
}

void noteOff(byte channel, byte pitch, byte velocity) {

  midiEventPacket_t noteOff = {0x08, 0x80, pitch, velocity};

  MidiUSB.sendMIDI(noteOff);
}
