#include "MIDIUSB.h"
unsigned long time;
int pinTrig=2;
int pinEcho=3;
int pinSetUp=4;
boolean notRead = true;

int distMin=200; //à tester et modifier
int distMax=0; //à set-up

int nbNotesSaut=12;
int saut=0;

int previousState1 = 1;
int previousState2 = 1;
int previousState3 = 1;
int previousState4 = 1;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  time=micros();

  pinMode(pinTrig, OUTPUT);
  pinMode(pinEcho, INPUT);
  pinMode(pinSetUp, INPUT);



  digitalWrite(pinTrig,HIGH);
  delayMicroseconds(10);
  digitalWrite(pinTrig,LOW);

  distMax=pulseIn(pinEcho, HIGH)*0.95; //à tester pour consistance
}

void loop() {
  // put your main code here, to run repeatedly:
  
  if(digitalRead(7)==HIGH){
  
    digitalWrite(pinTrig,HIGH);
    delayMicroseconds(10);
    digitalWrite(pinTrig,LOW);
  
    time=pulseIn(pinEcho, HIGH);
    //saut=(time-distMin)*10/(distMax-distMin);
  
    controlChange(0, time); //  (channel, value)
    MidiUSB.flush();
  
    if (time>distMin||time<10000){
      if (analogRead(A0)>=20 && previousState1==1){
        //noteOn(0, 1+saut*nbNotesSaut, 100);  // channel, note, velocity
        noteOn(0, 50, 100);
        MidiUSB.flush();
        previousState1=0;
      }else {
        if (analogRead(A0)<20 && previousState1==0){
          //noteOff(0, 1+saut*nbNotesSaut, 0);  // channel, note, velocity
          noteOff(0, 50, 0);
          MidiUSB.flush();
          previousState1=1;
        }
      }
      
      if (analogRead(A1)>=20 && previousState2==1){
        noteOn(0, 52, 100);  // channel, note, velocity
        MidiUSB.flush();
        previousState2=0;
      }else {
        if (analogRead(A1)<20 && previousState2==0){
          noteOff(0, 52, 0);  // channel, note, velocity
          MidiUSB.flush();
          previousState2=1;
        }
      }
      
      if (analogRead(A2)>=20 && previousState3==1){
        noteOn(0, 55, 100);  // channel, note, velocity
        MidiUSB.flush();
        previousState3=0;
      }else {
        if (analogRead(A2)<20 && previousState3==0){
          noteOff(0, 55, 0);  // channel, note, velocity
          MidiUSB.flush();
          previousState3=1;
        }
      }
      
      if (analogRead(A3)>=20 && previousState4==1){
        noteOn(0, 57, 100);  // channel, note, velocity
        MidiUSB.flush();
        previousState4=0;
      }else {
        if (analogRead(A3)<20 && previousState4==0){
          noteOff(0, 57, 0);  // channel, note, velocity
          MidiUSB.flush();
          previousState4=1;
        }
      }
    }
    
    delay(10);
  }
}

void noteOn(byte channel, byte pitch, byte velocity) {

  midiEventPacket_t noteOn = {0x09, 0x90, pitch, velocity};

  MidiUSB.sendMIDI(noteOn);
}

void noteOff(byte channel, byte pitch, byte velocity) {

  midiEventPacket_t noteOff = {0x08, 0x80, pitch, velocity};

  MidiUSB.sendMIDI(noteOff);
}

void controlChange(byte channel, int value) {
  byte lowValue = value & 0x7F;
  byte highValue = value >> 7;
  midiEventPacket_t event = {0x0E, 0xE0, lowValue, highValue};
  MidiUSB.sendMIDI(event);
}
