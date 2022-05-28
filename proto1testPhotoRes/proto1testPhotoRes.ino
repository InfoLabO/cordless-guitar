int val = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  /*digitalWrite(53,HIGH);
  digitalWrite(52,HIGH);*/
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(500);
  val = analogRead(A0);
  Serial.println(val);
}
