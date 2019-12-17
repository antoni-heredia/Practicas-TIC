#include <RF2272.h>

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  IniciarRF2272();
}

void loop() {
  int v  = leerRF2272();
  int bit;
  //Cogemos el valor de cada bit
  bit a0 =  (leerRF2272() & 1);
  bit a1 =  (leerRF2272() & 2);
  bit a2 =  (leerRF2272() & 4);
  bit a3 =  (leerRF2272() & 8);
  bit a4 =  (leerRF2272() & 16);
  bit a5 =  (leerRF2272() & 32);
  bit a6 =  (leerRF2272() & 64);
  //Calculamos las tres paridades
  bit p1 = a0^a2^a4^a6;
  bit p2 = a1^a2^a5^a6;
  bit p3= a3^a4^a5^a6;
  //Comprobamos si en alguna de las tres hay error
  if(p1 == 1){
      Serial.println("Error en p1");
    return 0;
  }
  if(p2 == 1){
      Serial.println("Error en p2");
    return 0;
  }
  if(p3 == 1){
    Serial.println("Error en p3");
    return 0;
  }
  if(codigo != "")  
    Serial.println(codigo);
}
