#include "Tarjetero.h"
//UID de la tarjeta a leer
char UID[32];
// Buffer para escribir /leer datos en/de la tarjeta
char bufer[65];

char opcion; // Opción a realizar (L=leer/E=escribir)

int CANTCARATERES = 31;
#define TAMCODIGO 5
#define TAMCODIGOLINEAL 12

struct caracter
{
  char caracter;
  int codigo[TAMCODIGO];
};

struct caracter characters[31] = {
  {'a',  {0, 0, 0, 0, 0}},
  {'b',  {0, 0, 0, 0, 1}},
  {'c',  {0, 0, 0, 1, 0}},
  {'d',  {0, 0, 0, 1, 1}},
  {'e',  {0, 0, 1, 0, 0}},
  {'f',  {0, 0, 1, 0, 1}},
  {'g',  {0, 0, 1, 1, 0}},
  {'h',  {0, 0, 1, 1, 1}},
  {'i',  {0, 1, 0, 0, 0}},
  {'j',  {0, 1, 0, 0, 1}},
  {'k',  {0, 1, 0, 1, 0}},
  {'l',  {0, 1, 0, 1, 1}},
  {'m',  {0, 1, 1, 0, 0}},
  {'n',  {0, 1, 1, 0, 1}},
  {'o',  {0, 1, 1, 1, 0}},
  {'p',  {0, 1, 1, 1, 1}},
  {'q',  {1, 0, 0, 0, 0}},
  {'r',  {1, 0, 0, 0, 1}},
  {'s',  {1, 0, 0, 1, 0}},
  {'t',  {1, 0, 0, 1, 1}},
  {'u',  {1, 0, 1, 0, 0}},
  {'v',  {1, 0, 1, 0, 1}},
  {'w',  {1, 0, 1, 1, 0}},
  {'x',  {1, 0, 1, 1, 1}},
  {'y',  {1, 1, 0, 0, 0}},
  {'z',  {1, 1, 0, 0, 1}},
  {'.',  {1, 1, 0, 1, 0}},
  {',',  {1, 1, 0, 1, 1}},
  {';',  {1, 1, 1, 0, 0}},
  {' ',  {1, 1, 1, 0, 1}},
  {3,   {1, 1, 1, 1, 0}}
};
M[5] = {
  {1,1,1,1,1,1,0, 1,0,0,0,0}
  {1,0,1,1,1,1,0, 0,1,0,0,0}
  {1,1,0,1,1,1,0, 0,0,1,0,0}
  {1,1,1,0,1,1,0, 0,0,0,1,0}
  {1,1,1,1,0,1,0, 0,0,0,0,1}
}
int * codifica(char letra) {
  for (int i = 0; i < CANTCARATERES; ++i) {
    if (characters[i].caracter == letra) {
      return characters[i].codigo;
    }
  }

int * codificaLineal(int * palabra){
  int * resultado[[12] = new int[12];

  for (int c = 0; c < 12; c++) {
    int suma = 0;
    for (int f = 0; f < 5; f++){
      suma = (suma + (palabra[f] * M[f][c]));
    }
    resultado[c] = suma % 2;
  }
  return resultado;
}
uint16_t BytesToUint16(int * palabra){
  uint16_t resultado = 0;

  int cont = 11;
  for (int f = 0; f < 12; f++){
      resultado += palabra[f] *pow(10, cont);
      cont--;
  }

  return resultado;
}
int * Uint16ToBytes(uint16_t palabra){
  int * resultado  = new int[12];
  int cont = 11;
  
  for (int f = 0; f < 12; f++){
      int i = palabra / pow(10, cont);
      palabra = palabra - (i * pow(10, cont));
      resultado[f] = i;
  }

  return resultado;
}

int * decodificaLineal(int * palabra){
  int * resultado[[12] = new int[12];

  for (int c = 0; c < 12; c++) {
    int suma = 0;
    for (int f = 0; f < 5; f++){
      suma = (suma + (palabra[f] * M[f][c]));
    }
    resultado[c] = suma % 2;
  }
  return resultado;
}

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
