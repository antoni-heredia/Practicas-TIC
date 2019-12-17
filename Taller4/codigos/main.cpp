// Para compilar ejecutar: g++ main.cpp -lm
#include <stdio.h>
#include <string>
#include <iostream>
#include <math.h>

//Funcion auxiliar para quitar el primero de un vector de enterors
int * eliminarPrimero( int * a , int longA){
    int nuevaLong = longA-1;
    int * nuevoVec = new int[nuevaLong];
    int pos = 0;
    for(int i = 1; i < longA;i++){
        nuevoVec[pos] = a[i];
        pos++;
    }
    return nuevoVec;
}

//Función para obtener el resto de la division binaria
int * restoDivision(int * a, int longA, int * b,int longB){
    int * resto = new int[longB];
    int posResto = 0;
    //Para conseguir el resto tendremos que ir elimiando bits del dividiendo hasta que la longitud sea menor que la del divisor.
    while (longB <= longA){
        //Si se encuentra un 1 en el dividiendo
        if (a[0] == 1){ //Cuando tengamos un 1 
            //eliminamos el primer bit de a
            a = eliminarPrimero(a,longA);
            longA--;
            //tenemos que hacer el and de todos los siguiente n bits de a con los bits de b, n es la longitud de b
            for (int i = 0; i < longB-1;i++){
                a[i] ^= b[i+1];
            }      
        }else{ //Si se encuentra un 0 seguimos sacando bits 
            a = eliminarPrimero(a,longA);
            longA--;
        }
    }
    //En a se encontrara  el resto de la division, no nos quedamos con el cocciente por que no lo necesitamos
    return a;
}

//Funcion para codificar una palabra dado un polinomio
int * codifica(int * palabra, int longPalabra, int * polinomio,int longPol){
    //Genero un vector para guardar la nueva palabra una vez codificada
    int longResul = longPalabra+longPol-1;
    int * resultado = new int[longResul];
    //Copio la palabra original y los restantes los pongo a 0
    for(int i = 0; i < longResul; i++){
        if(i < longPalabra)
            resultado[i] = palabra[i];
        else
            resultado[i] = 0;
    }
    //obtengo el resultado de la división
    int * resto = restoDivision(resultado,longResul,polinomio,longPol);
    int pos = longPalabra;
    //Copio el resto al final de palabra
    for(int i = 0; i < longPol-1; i++){
        resultado[pos] = resto[i];
        pos++;
    }
    //Devuelvo la palabra codificada
    return resultado;
}

//Funcion que devuelve si una palabra se ha recibido de forma correcta dado un polinomio
bool decodifica(int * vector, int longVec, int * polinomio, int longPol, int * resultado){
    //Obtengo el resultado de la divisions
    int * resto = restoDivision(vector,longVec,polinomio,longPol);
    //Guardo la palabra original en el vector pasado por referencia. Solo se copian hasta los digitos de control
    for(int i = 0; i < longVec - longPol+1; i++){
        resultado[i] = vector[i];
    }
    //Compruebo si el resto es 0
    for(int i = 0; i < longPol-1;i++){
        if(resto[i] != 0)
            return false; //En caso de que no sea cero devuelvo false
    }
    return true;//Si es 0 el resto devuelvo true
}

int main(int argc, char *argv[])
{
    //Polinomio y palabra de ejemplo
    int longPol = 4;
    int longPala = 9;
    int polinomio[] = {1,0,1,1};
    int palabra[] = {1,0,1,0,1,0,0,1,1,1};

    printf("----------------Ejercicio 1----------------\n");
    printf("Palabra sin codificar: ");
        for(int i = 0; i < longPala; i++)
        printf("%d",palabra[i]);
    printf("\n");

    int * resultado = codifica(palabra,longPala,polinomio,longPol);
    printf("Palabra codificada: ");
    for(int i = 0; i < longPol+longPala-1; i++)
        printf("%d",resultado[i]);
    printf("\n");



    printf("----------------Ejercicio 2----------------\n");
    printf("Partimos de la codificación del ejercicio anterior.\n");
    int * decodificado = new int[longPala];
    if(decodifica(resultado,longPol+longPala-1,polinomio,longPol,decodificado)){
        printf("Transmisión correcta\n  -Palabra decodificada: ");
        for(int i = 0; i < longPala; i++)
            printf("%d",decodificado[i]);
        printf("\n");
    }else{
        printf("Transmisión incorrecta\n");
    }
    printf("Ahora probamos a enviar habiendo un error en la transmision del tercer bit.\n");
    resultado[2] = 0;
    printf("Palabra recibida: ");
    for(int i = 0; i < longPol+longPala-1; i++)
        printf("%d",resultado[i]);
    printf("\n");
    if(decodifica(resultado,longPol+longPala-1,polinomio,longPol,decodificado)){
        printf("Transmisión correcta\n  -Palabra decodificada: ");
        for(int i = 0; i < longPala; i++)
            printf("%d",decodificado[i]);
        printf("\n");
    }else{
        printf("Transmisión incorrecta\n");
    }


    printf("----------------Ejercicio 3----------------\n");
    int * palabra2 = new int[longPala];
    int valorLeido = -1;
    int pos = 0;
    printf("Introduzca el numero en binario de uno en uno. Desde el bit mas significativo al menos significativo\n");
    for(int i = longPala-1; i >=0; i--){
        printf("Introduzca a%d: ",i);
        scanf("%d", &valorLeido);
        while(valorLeido != 0 && valorLeido != 1){
            printf("Introduzca a%d: ",i);
            scanf("%d", &valorLeido);
        }
        palabra2[pos] = valorLeido;
        valorLeido = -1;
        pos++;
    }

    printf("Numero  leido: ");
    for(int i = 0; i < longPala; i++)
        printf("%d",palabra2[i]);
    printf("\n");
    int * resultado2 = codifica(palabra2,longPala,polinomio,longPol);
    printf("Palabra codificada: ");
    for(int i = 0; i < longPol+longPala-1; i++)
        printf("%d",resultado2[i]);
    printf("\n");

    printf("----------------Ejercicio 4----------------\n");
    int * palabraRecibida = new int[longPol+longPala-1];
    valorLeido = -1;
    pos = 0;
    printf("Introduzca la palabra recibida en binario de uno en uno. Desde el bit mas significativo al menos significativo\n");
    for(int i = longPol+longPala-2; i >=0; i--){
        printf("Introduzca a%d: ",i);
        scanf("%d", &valorLeido);
        while(valorLeido != 0 && valorLeido != 1){
            printf("Introduzca a%d: ",i);
            scanf("%d", &valorLeido);
        }
        palabra2[pos] = valorLeido;
        valorLeido = -1;
        pos++;
    }

    if(decodifica(palabra2,longPol+longPala-1,polinomio,longPol,decodificado)){
        printf("Transmisión correcta\n  -Palabra decodificada: ");
        for(int i = 0; i < longPala; i++)
            printf("%d",decodificado[i]);
        printf("\n");
    }else{
        printf("Transmisión incorrecta\n");
    }
    return 0;

}

