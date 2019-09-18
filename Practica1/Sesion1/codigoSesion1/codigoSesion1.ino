bool encendido;
int ROJO = 13;
int VERDE = 9;
int ENTRADA = 7;
void setup() {
  // put your setup code here, to run once:
    pinMode(ROJO, OUTPUT);
    pinMode(VERDE, OUTPUT);
    pinMode(ENTRADA, INPUT);
    
    encendido = true;
    digitalWrite(ROJO, LOW);    
    digitalWrite(VERDE, HIGH);    
    Serial.begin(9600);
}

void loop() {
  while (Serial.available() > 0) {
    String cadena = Serial.readString();
    if(cadena == "ON"){
      encendido = true;
    } else if(cadena == "OFF"){
      encendido = false;
    }
  
  }
  
  if(encendido){
      if(digitalRead(ENTRADA)== HIGH){
        digitalWrite(VERDE,LOW);
        digitalWrite(ROJO,HIGH);
      }else{
        digitalWrite(VERDE,HIGH);
        digitalWrite(ROJO,LOW);
      }

  }else if(!encendido){
    digitalWrite(ROJO,LOW);
    digitalWrite(VERDE,LOW);
  }
}
