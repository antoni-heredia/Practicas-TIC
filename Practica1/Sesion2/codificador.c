#include <stdio.h>
#include <string.h>



int CANTCARATERES = 31;
#define TAMCODIGO 5

struct caracter 
{ 
   char caracter; 
   int codigo[TAMCODIGO]; 
};

struct caracterCodigo
{ 
   char caracter; 
   char codigo[TAMCODIGO+1]; 
};

struct caracterCodigo decode[31] = {
    {'a',  "00000\0"},
    {'b',  "00001\0"},
    {'c',  "00010\0"}, 
    {'d',  "00011\0"}, 
    {'e',  "00100\0"}, 
    {'f',  "00101\0"}, 
    {'g',  "00110\0"}, 
    {'h',  "00111\0"}, 
    {'i',  "01000\0"}, 
    {'j',  "01001\0"}, 
    {'k',  "01010\0"}, 
    {'l',  "01011\0"}, 
    {'m',  "01100\0"}, 
    {'n',  "01101\0"}, 
    {'o',  "01110\0"}, 
    {'p',  "01111\0"}, 
    {'q',  "10000\0"}, 
    {'r',  "10001\0"}, 
    {'s',  "10010\0"}, 
    {'t',  "10011\0"}, 
    {'u',  "10100\0"}, 
    {'v',  "10101\0"}, 
    {'w',  "10110\0"}, 
    {'x',  "10111\0"}, 
    {'y',  "11000\0"}, 
    {'z',  "11001\0"},
    {'.',  "11010\0"}, 
    {',',  "11011\0"}, 
    {';',  "11100\0"}, 
    {' ',  "11101\0"}, 
    {')',  "11110\0"}
};
struct caracter characters[31] = {
    {'a',  {0,0,0,0,0}},
    {'b',  {0,0,0,0,1}},
    {'c',  {0,0,0,1,0}}, 
    {'d',  {0,0,0,1,1}}, 
    {'e',  {0,0,1,0,0}}, 
    {'f',  {0,0,1,0,1}}, 
    {'g',  {0,0,1,1,0}}, 
    {'h',  {0,0,1,1,1}}, 
    {'i',  {0,1,0,0,0}}, 
    {'j',  {0,1,0,0,1}}, 
    {'k',  {0,1,0,1,0}}, 
    {'l',  {0,1,0,1,1}}, 
    {'m',  {0,1,1,0,0}}, 
    {'n',  {0,1,1,0,1}}, 
    {'o',  {0,1,1,1,0}}, 
    {'p',  {0,1,1,1,1}}, 
    {'q',  {1,0,0,0,0}}, 
    {'r',  {1,0,0,0,1}}, 
    {'s',  {1,0,0,1,0}}, 
    {'t',  {1,0,0,1,1}}, 
    {'u',  {1,0,1,0,0}}, 
    {'v',  {1,0,1,0,1}}, 
    {'w',  {1,0,1,1,0}}, 
    {'x',  {1,0,1,1,1}}, 
    {'y',  {1,1,0,0,0}}, 
    {'z',  {1,1,0,0,1}},
    {'.',  {1,1,0,1,0}}, 
    {',',  {1,1,0,1,1}}, 
    {';',  {1,1,1,0,0}}, 
    {' ',  {1,1,1,0,1}}, 
    {')',   {1,1,1,1,0}}
};
int * codificador(char letra){
    for(int i = 0; i < CANTCARATERES; ++i) {
        if(characters[i].caracter == letra){
            return characters[i].codigo;
        }    
    }
}

char decodificador(int * codigo){
    char  codigoS[] = {codigo[0] + 48,codigo[1] + 48,codigo[2] + 48,codigo[3] + 48,codigo[4] + 48,'\0'};
    for(int i = 0; i < CANTCARATERES; ++i) {
        if(strcmp(codigoS, decode[i].codigo) == 0){
            return decode[i].caracter;
        }    
    }

}
int main( int argc, const char* argv[] )
{
	int * codigo;
    codigo  = codificador('.');
    char letra = decodificador(codigo);
    printf("El codigo es: ");
    for(int i = 0; i < TAMCODIGO; ++i) 
        printf("%d-",codigo[i]);

    printf("\nLa letra decodificada es %c\n",letra);
}