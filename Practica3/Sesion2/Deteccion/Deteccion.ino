#include <RF2272.h>

bool decodificar(const uint8_t codigo, bool pulsados[4])
{
  //Cogemos el valor de cada bit
  int a0 = (codigo & 1) > 0;
  int a1 = (codigo & 2) > 0;
  int a2 = (codigo & 4) > 0;
  int a3 = (codigo & 8) > 0;
  int a4 = (codigo & 16) > 0;
  int a5 = (codigo & 32) > 0;
  int a6 = (codigo & 64)  > 0;
  //Calculamos las tres paridades
  int p1 = a0 ^ a2 ^ a4 ^ a6;
  int p2 = a1 ^ a2 ^ a5 ^ a6;
  int p3 = a3 ^ a4 ^ a5 ^ a6;

  //Si hay error devolvemos false
  if (p1 == 1 || p2 == 1 || p3 == 1) {
    pulsados[0] = false;
    pulsados[1] = false;
    pulsados[2] = false;
    pulsados[3] = false;
    return false;
  }

  pulsados[0] = (a2 > 0);
  pulsados[1] = (a4 > 0);
  pulsados[2] = (a5 > 0);
  pulsados[3] = (a6 > 0);

  return true;
}
void setup()
{
  Serial.begin(19200);
  IniciarRF2272();
}

void loop()
{
  int v = leerRF2272();
  int bit;
  String codigo = "";
  bool * pulsados = new bool[4];
  if (v != 0) {

    //comprobamos si la transmisión tiene errores
    if (decodificar((uint8_t)v, pulsados)) {
      Serial.print("Transmision correcta. ");
    } else {
      Serial.print("Error en la transmisión. ");
    }
    
    for (int i = 6; i >= 0; i--)
    {
      bit = (1 << i);
      if ((v & bit) > 0)
      {
        codigo = codigo + '1';
      }
      else
      {
        codigo = codigo + '0';
      }
    }
    if (codigo != "") {
      Serial.print("Codigo recibido: ");
      Serial.print(codigo);
    }
    Serial.println();

  }
  free(pulsados);

}
