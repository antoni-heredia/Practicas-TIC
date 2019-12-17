#include "Tarjetero.h"
//UID de la tarjeta a leer
char UID[32];
// Buffer para escribir /leer datos en/de la tarjeta
char bufer[65];

char opcion; // Opción a realizar (L=leer/E=escribir)

void setup() {
  //inicialización del tarjetero
  initMFRC522();
  //Finalización del buffer para poder enviarse por serial
  bufer[64] = '\0';
  opcion = ' ';

  Serial.begin(9600);
  while(!Serial); //Esperamos a que se abra el monitor serie
  Serial.println("Escoja una opción (L=leer/E=escribir)");
  do{
    if(Serial.available()){
      opcion = Serial.read();
      if (opcion != 'L' && opcion != 'E'){
        Serial.println("Opcion no válida (L/E)");
      }
    }
  } while(opcion != 'L' && opcion != 'E');
  if(opcion == 'E'){
    Serial.print("\nIntroudzca el mensa a escribir (max. 64...\n");
    while(!Serial.available());
    Serial.readBytes(bufer,64);
    Serial.println("Esperando a tarjeta para escribir...");
  }else{
    Serial.println("Esperando a tarjeta para leer...");
  }
}

void loop() {
  if(! isCardDetected())return;
  Serial.print("Tarjeta detectada. ");
  
  if(!readUIDCard(UID)) return;
  
  Serial.print(F("UID: "));
  Serial.println(UID);

  if(opcion == 'L'){
     //lectura de la tarjeta
     if(!readCard((uint16_t *) bufer)){
        Serial.println("Error en la lectura");
        closeCard();
        return;
     }
     Serial.print("Datos en la tarjeta: ");

     Serial.println(bufer);
  }else{ //Escritura en tarjeta
    if(!writeCard((uint16_t *)bufer)){
      Serial.println("Error en escritura de tarjeta ");
      closeCard();
      return;
    }
    Serial.println("Datos escritos en la tarjeta");
  }
  closeCard();
}
