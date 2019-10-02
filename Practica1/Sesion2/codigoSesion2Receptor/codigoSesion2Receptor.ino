int TAU = 10;
int n = 2;
int pin = 7;
int cantRecibidos = 0 ;
char cadena [11];

void setup() {
  // put your setup code here, to run once:
    pinMode(pin, INPUT);
  Serial.begin(9600);
}

void loop() {

  int bitRecibido = recvBit(pin);
  while(bitRecibido != -1){
    cadena[cantRecibidos] = bitRecibido + 48;
    bitRecibido = recvBit(pin);
    cantRecibidos += 1;
  }
  if(cantRecibidos >= 10){
    cadena[11] = '\0';
    Serial.print("La cadena es: ");
    Serial.println(cadena);
    cantRecibidos = 0;
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
