#include <RF2272.h>

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  IniciarRF2272();
}

void loop() {
  int v  = leerRF2272();
  int bit;
  String codigo = "";
  if(v != 0)
    for (int i = 6; i >= 0; i--){
      bit  = (1<<i);
      if((v & bit) > 0) {
        codigo = codigo + '1';
      }else{
        codigo = codigo + '0';
      }
    }
  if(codigo != "")  
    Serial.println(codigo);
}
