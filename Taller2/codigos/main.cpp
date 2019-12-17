// Para compilar ejecutar: g++ main.cpp
using namespace std;
#include <stdio.h>
#include <string>
#include <iostream>
#include <vector>
#include <math.h>

//Funcion ejercicio 2
float *calcularProbEmision(float **prob, int tam)
{
    //Declaro el vector donde guardar las probabilidades
    float *probEm = new float[tam];
    //La probabilidad de que el elemento A sea emitido es la sumatoria de que habiendo emitido A se reciba A o cualquier otro.
    //Pagina 27 diapositivas tema 2
    float comprobacion = 0;
    for (int i = 0; i < tam; i++)
    {

        float suma = 0;
        for (int j = 0; j < tam; j++)
        {
            suma += prob[i][j];
        }
        probEm[i] = suma;

        //Para comprobar que la suma no es mayor que uno
        comprobacion += suma;
    }


    if (comprobacion != 1)
    {
        cout << "La suma de las probabilidades del emisor es erronea. "  << endl;
        exit(EXIT_FAILURE);
    }
    return probEm;
}
//Funcion ejercicio 3
float *calcularProbRecep(float **prob, int tam)
{
    float *probRecep = new float[tam];
    float comprobacion = 0;

        float *probEm = new float[tam];
    //La probabilidad de que el elemento A sea recibido es la sumatoria de que habiendo recibido A se haya emitido A o cualquier otro.
    //Pagina 27 diapositivas tema 26
    for (int j = 0; j < tam; j++)
    {
        float suma = 0;
        for (int i = 0; i < tam; i++)
        {
            suma += prob[i][j];
        }
        probRecep[j] = suma;
        //Para comprobar que la suma no es mayor que uno
        comprobacion += suma;
    }
    if (comprobacion != 1)
    {
        cout << "La suma de las probabilidades de emtir es erronea." << endl;
        exit(EXIT_FAILURE);
    }
    return probRecep;
}
//Realizar logaritmo de base n
float log_n(int base, float x) {
    return (float)(log(x) / log(base));
}
//Ejercicio 4

float entropia(float * probabilidades,int tam, int cantSimbolos){
    float sumatorio = 0;
    for(int i = 0; i < tam; i++){
        if(probabilidades[i] != 0)
            sumatorio += probabilidades[i]*log_n(cantSimbolos,probabilidades[i]);
    }
    return -sumatorio;
}

//Ejercicio 6
float entropiaConjunta(float ** probabilidad, int tam, int cantSimbolos){
    float sumatorio = 0;
    for(int i = 0; i < tam; i ++){
        for(int j = 0; j < tam; j++){
            if(probabilidad[i][j] != 0)
                sumatorio+= probabilidad[i][j]*log_n(cantSimbolos,probabilidad[i][j]);
        }
    }
    return -sumatorio;
}

//Ejercicio 7
float entropiaCondicional(float ** probabilidad, int tam, int cantSimbolos){
    //vamos a necesitar la entropia del receptor
    float * probReceptor = calcularProbRecep(probabilidad,tam);
    float ent = entropia(probReceptor,tam,cantSimbolos);
    //y tambien necesiatoms la entropia conjunta
    float entConjunta = entropiaConjunta(probabilidad,tam,cantSimbolos);
    //La formula viene descrita en la pagina 35 del pdf del Tema 2
    return entConjunta-ent;
}

//Ejercicio 8
float informacionMutua(float ** probabilidad, int tam, int cantSimbolos){
    //la informacion mutua viene dada por una formula de la paigna 47 del pdf del Tema 2
    //necesitamos la entropia del emisor
    float ent = entropia(calcularProbEmision(probabilidad,tam),tam,cantSimbolos);
    //Y la condicional
    float condicional = entropiaCondicional(probabilidad,tam,cantSimbolos);
    return ent-condicional;
}

int main(int argc, char *argv[])
{
    //Pedimos que se introduzca nS
    cout << "Por favor introduzca el numero nS: ";
    int nS;
    cin >> nS;

    //hacemos comprobaciones necesarias
    if (nS < 1 || nS > 10)
    {
        cout << "Numero invalido." << endl;
        exit(EXIT_FAILURE);
    }

    //Declaro la matriz de probabilidades conjuntas y pido los datos
    float ** prob = new float*[nS];
    for(int x = 0; x < nS;x++)
        prob[x]=new float[nS];
    cout << "Por  favor introduzca la matriz de probabilidades conjuntas" << endl;
    float suma = 0;
    for (int i = 0; i < nS; i++)
    {
        for (int j = 0; j < nS; j++)
        {
            cout << " p(S=x(" << i << "), R=x(" << j << "))= ";
            float dato;

            cin >> dato;
            prob[i][j] = dato;
            suma += dato;
        }
    }
    //compruebo que la suma no sea mayor que 1
    if (suma != 1)
    {
        cout << "La suma de probabilidades conjuntas debe ser 1" << endl;
        exit(EXIT_FAILURE);
    }

    int nC;
    //Pido que se introduzca nC
    cout << "Por favor introduzca el numero nC: ";
    cin >> nC;

    //Mostramos todos los ejemplos pedidios en el enunciado
    //Ejercicio 5
    string s;
    cout << "Por favor pulse enter para continuar con el ejercicio 5: " << endl;
    cin.ignore();
    
    float * probEmisor = calcularProbEmision(prob,nS);
    float entr = entropia(probEmisor,nS,nC);
    cout << "Cantidad de simbolos promedio del emisor " << nC <<"-ario: " << entr << endl;
    
    //Ejercicio 6
    cout << "Por favor pulse enter para continuar con el ejercicio 6: ";
    cin.ignore();

    entr = entropiaConjunta(prob,nS,nC);
    cout << "La entropia conjunta es: " << entr << endl;

    //Ejercicio 7
    cout << "Por favor pulse enter para continuar con el ejercicio 7: ";
    cin.ignore();

    entr = entropiaCondicional(prob,nS,nC);
    cout << "La entropia condicional es: " << entr << endl;

    //Ejercicio 8
    cout << "Por favor pulse enter para continuar con el ejercicio 8: ";
    cin.ignore();
    
    entr = informacionMutua(prob,nS,nC);
    cout << "La información mutua es: " << entr << endl;

    //eliminamos de memoria el array
    for(int i = 0; i < nS; i++)
        delete[] prob[i];
    delete[] prob;

    //Ejercicio 9
    cout << "Por favor pulse enter para continuar con el ejercicio 9: ";
    cin.ignore();

    cout << "-----------Ejemplo de canal sin ruido-----------" << endl;

    //Declaro la matriz de probabilidades para un canal de ejemplo sin ruido
    float ** sinRuido = new float*[2];
    for(int x = 0; x < 2;x++)
        sinRuido[x]=new float[2];
    sinRuido[0][0] = 0.3 ;
    sinRuido[0][1] = 0.0 ;
    sinRuido[1][0] = 0.0 ;
    sinRuido[1][1] = 0.7 ;
    float datosEje9;
    datosEje9 = entropia(calcularProbEmision(sinRuido,2),2,2);
    cout << "La entropia del emisor es: " << datosEje9 << endl;
    datosEje9 = entropia(calcularProbRecep(sinRuido,2),2,2);
    cout << "La entropia del receptor es: " << datosEje9 << endl;
    datosEje9 = entropiaConjunta(sinRuido,2,2);
    cout << "La entropia conjunta es: " << datosEje9 << endl;
    datosEje9 = entropiaCondicional(sinRuido,2,2);
    cout << "La entropia condicional es: " << datosEje9 << endl;
    datosEje9 = informacionMutua(sinRuido,2,2);
    cout << "La información mutua es: " << datosEje9 << endl;
    cout << "---------Explicación de los datos objetenidos---------" << endl;
    cout << "\t-La entropia conjunta es igual a la entropia del emisor y esto se debe a la ley de las entropias totales."
         << " Como H(X,Y) = H(X)+H(Y|X) y tenemos que la entropia condicional es igual a 0 (porque se conoce uníquivocamente "
         << "el símbolo recibido), nos queda que H(X,Y)=H(X). " << endl;
    cout << "\t-La entropia condicional es igual a 0 por lo explicado arriba de que al conocerse unívocamente el simbolo recibido"
         << " en el receptor sabiendo que ha enviado el emisor" << endl;
    cout << "\t-La información mutua tambien sera igual a la entropia del emisor. Esto se debe a que como I(X;Y) = H(X) - H(X|Y) y"
         << " volvemos a tener que la probabilidad condicionada es 0, tendremos I(X;Y) = H(X) " << endl;
    //eliminamos de memoria el array
    for(int i = 0; i < 2; i++)
        delete[] sinRuido[i];
    delete[] sinRuido;

    //Ejercicio 10
    cout << "Por favor pulse enter para continuar con el ejercicio 10: ";
    cin.ignore();

    cout << "-----------Ejemplo de canal con ruido-----------" << endl;

    //Declaro la matriz de probabilidades para un canal de ejemplo con ruido
    float ** conRuido = new float*[2];
    for(int x = 0; x < 2;x++)
        conRuido[x]=new float[2];
    conRuido[0][0] = 0.3 ;
    conRuido[0][1] = 0.3 ;
    conRuido[1][0] = 0.3 ;
    conRuido[1][1] = 0.1 ;
    float datosEje10;
    datosEje10 = entropia(calcularProbEmision(conRuido,2),2,2);
    cout << "La entropia del emisor es: " << datosEje10 << endl;
    datosEje10 = entropia(calcularProbRecep(conRuido,2),2,2);
    cout << "La entropia del receptor es: " << datosEje10 << endl;
    datosEje10 = entropiaConjunta(conRuido,2,2);
    cout << "La entropia conjunta es: " << datosEje10 << endl;
    datosEje10 = entropiaCondicional(conRuido,2,2);
    cout << "La entropia condicional es: " << datosEje10 << endl;
    datosEje10 = informacionMutua(conRuido,2,2);
    cout << "La información mutua es: " << datosEje10 << endl;
    cout << "---------Explicación de los datos objetenidos---------" << endl;
    cout << "\t-La entropia condicional esta vez no es 0. Esto es porque no sabemos con seguridad el elemento que se ha enviado a partir del elemento recibido." << endl;
    cout << "\t-Al no ser la entropia condicional 0, la información mutua sera menor que la entropia del emisor." << endl;
    cout << "\t-La entropia conjunta ademas debe ser H(X,Y)=H(Y)+H(X|Y), que como podemos ver, en este caso se cumple." << endl;
    //eliminamos de memoria el array
    for(int i = 0; i < 2; i++)
        delete[] conRuido[i];
    delete[] conRuido;
    
}