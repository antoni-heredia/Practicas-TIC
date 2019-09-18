int TAU = 100;
int n = 2;
int pin = 7;
void setup() {
  // put your setup code here, to run once:
    pinMode(pin, INPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  String cadena = "";
  int bitRecibido = recvBit(pin);
  if(bitRecibido != -1){
    cadena += bitRecibido;
    while(bitRecibido =! -1){
      bitRecibido = recvBit(pin);
      cadena+=char(bitRecibido);
    }
    Serial.println(cadena);
  }
}

int recvBit(int pin){
  int cont = 0;
  while(cont <= n && digitalRead(pin) == LOW){
    cont++;
    delay(TAU/n);
  }
  if(cont > n)
    return -1;
  else{
    cont  = 0;
    while(digitalRead(pin) == HIGH){
      cont++;
      delay(TAU/n);
    }
    if(cont > n)
      return 1;
    else
      return 0; 
      
  }
  
}
