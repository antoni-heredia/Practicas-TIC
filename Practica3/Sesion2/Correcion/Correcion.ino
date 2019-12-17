#include <RF2272.h>

bool MultiplicaZ2(int *palabra, int palabraSize, int Matriz[7][3], int FilMatriz, int ColMatriz, int *salida)
{
  if (palabraSize != FilMatriz)
    return false;

  for (int c = 0; c < ColMatriz; c++) {
    int suma = 0;
    for (int f = 0; f < palabraSize; f++){
      suma = (suma + (palabra[f] * Matriz[f][c]));
    }
    salida[c] = suma % 2;
    //Serial.println(salida[c]);

  }
  return true;
}
int bin2Dec( int * numero, int longitud) {
  int suma = 0;
  for (int i = 0; i < longitud; i++) {
    suma += pow(2, i) * numero[i];
  }
  return suma;
}
bool decodificar(const uint8_t codigo, bool pulsados[4])
{
  int valores[7][3] = {{1, 1, 1}, {1, 1, 0}, {1, 0, 1}, {1, 0, 0}, {0, 1, 1}, {0, 1, 0}, {0, 0, 1}};
  int * palabra = new int[7];
  int pos = 0;
  for (int i = 6; i >= 0; i--){
    palabra[pos] = ((codigo & (1 << i)) > 0) ? 1 : 0 ;
    pos++;
  }
  int *salida = new int[3];
  MultiplicaZ2(palabra, 7, valores, 7, 3, salida );

  bool error = false;
  for (int i = 0; i < 3; i++)
    if ( salida[i] == 1)
      error = true;

  if (error) {
    int pos = bin2Dec(salida, 3);
    if(palabra[6-pos] == 1){
      palabra[6-pos] = 0;
    }else{
      palabra[6-pos] = 1;

    }
  }

  pulsados[0] = (palabra[4] > 0);
  pulsados[1] = (palabra[2] > 0);
  pulsados[2] = (palabra[1] > 0);
  pulsados[3] = (palabra[0] > 0);
  free(palabra);
  return !error;
}
void setup()
{

  // put your setup code here, to run once:
  Serial.begin(19200);
  IniciarRF2272();
}

void loop()
{
  int v = leerRF2272();
  int bit;
  String codigo = "";
  bool *pulsados = new bool[4];
  if (v != 0)
  {
    //comprobamos si la transmisión tiene errores
    if (decodificar((uint8_t)v, pulsados))
    {
      //En caso de que no tenga devolvemos el codigo completo recibido
      Serial.print("No hay error, ");
    } else {
      Serial.print("Hay error, ");
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
      Serial.print("-");

    }
    Serial.print("Los botones pulsados (corregidos en su caso): ");
    for(int i  = 0; i < 4; i++){
      if(pulsados[i] == true){
        Serial.print("a_");
        Serial.print(i);
      }
    }
    Serial.println();
  }
  free(pulsados);

}
