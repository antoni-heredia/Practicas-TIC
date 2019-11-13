#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
typedef enum
{
    false,
    true
} bool;

struct probabilidad
{
    int nodo;
    double prob;
};
void  Ordenar(struct probabilidad *Nodos, int s)
{

    for (int i = 0; i < s - 1; i++)
    {

        for (int j = i + 1; j < s; j++)
        {
            if (Nodos[i].prob < Nodos[j].prob )
            {
                double interP = Nodos[i].prob ;
                Nodos[i].prob  = Nodos[j].prob ;
                Nodos[j].prob  = interP;

                int interN = Nodos[i].nodo;
                Nodos[i].nodo = Nodos[j].nodo;
                Nodos[j].nodo = interN;
            }
        }
    }
}
int main(int argc, const char *argv[])
{
    FILE *archivo;
    archivo = fopen("quijote.txt", "r");

    int CANT_CAR = 30;
    char caracter;

    int apariciones[CANT_CAR];
    char alfabeto[CANT_CAR];
    float prob[CANT_CAR];

    for (int x = 0; x < CANT_CAR; x++)
    {
        alfabeto[x] = '\0';
        apariciones[x] = 0;
    }

    if (archivo == NULL)
    {
        printf("\nError de apertura del archivo. \n\n");
    }
    else
    {
        //Codigo para contar el numero total de simbolos y las apariciones de cada uno
        int numeroTotalSimbolos = 0;
        while ((caracter = fgetc(archivo)) != EOF)
        {
            caracter = toupper(caracter);
            numeroTotalSimbolos++;
            //Recorremos todo el vector en busca de coincidencias
            bool encontrado = false;
            for (int x = 0; x < CANT_CAR && !encontrado; x++)
            {
                if (alfabeto[x] == caracter)
                {                     //Si el caracter se corresponde al caracter de esta posicion
                    apariciones[x]++; //incrementamos el numero de apariciones
                    encontrado = true;
                }
                else if (alfabeto[x] == '\0' && caracter != '\n')
                {                           //Si hemos recorrido todas las letras aparecidas sin encontrar la actual
                    apariciones[x]++;       //decimos que ya ha aparecido una vez
                    alfabeto[x] = caracter; //añadimos el caracter
                    encontrado = true;
                }
            }
        }

        //Codig para calcular la probabilidad
        float suma = 0;
        //Una vez leidos todos los caracteres, calculo las probabilidades
        for (int x = 0; x < CANT_CAR; x++)
        {
            prob[x] = (float)apariciones[x] / numeroTotalSimbolos; //calculo la probabilidad
            //printf("probabilidad %c es de %f\n", alfabeto[x], prob[x]);
        }
    }
    fclose(archivo);

    int mSize = CANT_CAR;
    int Huffman[63][4];
    struct  probabilidad * nodos;
    nodos =  (struct  probabilidad *)malloc(CANT_CAR*sizeof(struct  probabilidad*));
    //inicializo el codigo huffman
    for (int i = 0; i < mSize; i++)
    {

        Huffman[i][0] = alfabeto[i];
        Huffman[i][1] = -1;
        Huffman[i][2] = -1;
        Huffman[i][3] = -1;

        nodos[i].nodo = i;
        nodos[i].prob = prob[i];

    }
    Ordenar(nodos,CANT_CAR);

    int tam = CANT_CAR;
    while(tam > 1){

        Ordenar(nodos,CANT_CAR);

        struct probabilidad Nodo1 = nodos[tam-1];
        struct probabilidad Nodo2 = nodos[tam-2];
        Huffman[mSize][0]='\0';

        Huffman[mSize][1]=Nodo1.nodo;
        Huffman[mSize][2]=Nodo2.nodo;
        Huffman[Nodo1.nodo][3]=mSize;
        Huffman[Nodo2.nodo][3]=mSize;
        Huffman[mSize][3]=-1;

        nodos[tam-2].prob=nodos[tam-2].prob+nodos[tam-1].prob;
        tam = tam-1;
        nodos[tam-1].nodo = mSize;
        mSize++;
    }
    int raiz = mSize - 1;
    for(int i = 0; i < mSize; i++){
        printf("{'%c',%d,%d,%d},\n",Huffman[i][0],Huffman[i][1],Huffman[i][2],Huffman[i][3]);
    }
    printf("raiz:%d",raiz);
    return 0;
}
