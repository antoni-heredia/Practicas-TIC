#include <stdio.h>
#include <string>
#include <iostream>

int CANTCARATERES = 31;
#define TAMCODIGO 5

#define DEBUG(a, b) for (int index = 0; index < b; index++) Serial.print(a[index]); Serial.println();
int huffman[59][4] = {
  {'C', -1, -1, 44},
  {'A', -1, -1, 52},
  {'P', -1, -1, 40},
  {'I', -1, -1, 47},
  {'T', -1, -1, 43},
  {'U', -1, -1, 45},
  {'L', -1, -1, 47},
  {'O', -1, -1, 51},
  {' ', -1, -1, 55},
  {'R', -1, -1, 48},
  {'M', -1, -1, 42},
  {'E', -1, -1, 53},
  {'Q', -1, -1, 39},
  {'D', -1, -1, 46},
  {'N', -1, -1, 48},
  {'Y', -1, -1, 38},
  {'J', -1, -1, 34},
  {'F', -1, -1, 35},
  {'S', -1, -1, 49},
  {'H', -1, -1, 37},
  {'G', -1, -1, 38},
  {'.', -1, -1, 34},
  {',', -1, -1, 41},
  {'B', -1, -1, 39},
  {'V', -1, -1, 36},
  {'Z', -1, -1, 33},
  {'X', -1, -1, 31},
  {';', -1, -1, 32},
  {'K', -1, -1, 30},
  {'W', -1, -1, 30},
  {'\0', 29, 28, 31},
  {'\0', 30, 26, 32},
  {'\0', 31, 27, 33},
  {'\0', 32, 25, 35},
  {'\0', 21, 16, 36},
  {'\0', 17, 33, 37},
  {'\0', 34, 24, 40},
  {'\0', 19, 35, 41},
  {'\0', 20, 15, 42},
  {'\0', 23, 12, 43},
  {'\0', 36, 2, 44},
  {'\0', 22, 37, 45},
  {'\0', 38, 10, 46},
  {'\0', 39, 4, 49},
  {'\0', 0, 40, 50},
  {'\0', 41, 5, 50},
  {'\0', 13, 42, 51},
  {'\0', 3, 6, 52},
  {'\0', 9, 14, 53},
  {'\0', 43, 18, 54},
  {'\0', 44, 45, 54},
  {'\0', 7, 46, 55},
  {'\0', 47, 1, 56},
  {'\0', 48, 11, 56},
  {'\0', 49, 50, 57},
  {'\0', 51, 8, 57},
  {'\0', 52, 53, 58},
  {'\0', 54, 55, 58},
  {'\0', 56, 57, -1}
};

int raiz = 58 ;
int * codifica(std::string letra, int tamanio) {
  //codigo que se enviara
  int * o = new int[20 * tamanio];
  for(int i = 0; i < 20*tamanio;i++){
    o[i] = -1;
  }
    
  int topCodigo = 0;
  for (int i = 0; i < tamanio-1; ++i) {
    //pila y tope de la pila
    int p[20];
    int top = 0;


    bool encontrado = false;
    int hoja = 0;
    //buscamos la hoja donde se encuentra el simbolo
    while (hoja <= raiz & !encontrado) {
      if ((char)toupper(letra[i]) == (char)huffman[hoja][0]) {
        encontrado = true;
        std::cout << "hoja: " << hoja << '\n';
      }
      else
        hoja++;
    }


    //mientras  no sea la raiz del arbol
    while (huffman[hoja][3] != -1) {
      int padre = huffman[hoja][3];
      if (huffman[padre][1] == hoja) {
        p[top] = 0;
      } else {
        p[top] = 1;

      }
      top++;
      hoja = padre;
    }

    for (int i = top-1; i >= 0; i--) {
      o[topCodigo] = p[i];
      topCodigo++;
    }
  }
  return o;
}

int main( int argc, const char* argv[] )
{
	int * codigo;
    codigo  = codifica("Hola que tal",13);
    printf("El codigo es: ");
    int pos = 0;
    while (codigo[pos] != -1) {
      pos++;
    }

    
    for (int i = 0; i < pos; ++i) {
      printf("%d,",codigo[i]);
    } 
}