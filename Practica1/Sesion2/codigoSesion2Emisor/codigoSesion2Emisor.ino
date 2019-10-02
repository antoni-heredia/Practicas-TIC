int TAU = 10;
int pin = 8;
void setup() {
  // put your setup code here, to run once:
  pinMode(pin, OUTPUT);
  Serial.begin(9600);
}
void loop() {
  while (Serial.available() > 0) {
     char c = Serial.read ();
     int bitleido = c - '0';
     sendBit(bitleido, pin);
  }
}

void sendBit(int value, int pin){
  digitalWrite(pin,HIGH);

  if(value == 0)
    delay(TAU);
  else if (value == 1)
    delay(2*TAU);
  
  digitalWrite(pin,LOW);
  delay(TAU);

};
