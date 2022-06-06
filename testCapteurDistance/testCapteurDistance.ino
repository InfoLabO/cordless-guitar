unsigned long time;
int pinTrig=2;
int pinEcho=3;
boolean notRead = true;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  time=micros();

  pinMode(pinTrig, OUTPUT);
  pinMode(pinEcho, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  /*if(micros()-time<50){
    digitalWrite(pinTrig,HIGH);
  } else {
    digitalWrite(pinTrig,LOW);
  }
  if(digitalRead(pinEcho)==HIGH&&notRead){
    Serial.println(micros()-time);
    notRead=false;
  }
  if(micros()-time>10000){
    time=micros();
    notRead=true;
  }*/

  digitalWrite(pinTrig,HIGH);
  delayMicroseconds(10);
  digitalWrite(pinTrig,LOW);

  time=pulseIn(pinEcho, HIGH);

  Serial.println(time);
  delay(10);
}
