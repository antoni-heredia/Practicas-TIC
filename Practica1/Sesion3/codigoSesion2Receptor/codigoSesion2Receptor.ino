int TAU = 4;
int n = 2;
int pin = 7;
int cantRecibidos = 0 ;
int cantCar = 0 ;

int CANTCARATERES = 31;
#define TAMCODIGO 5
int codigo [TAMCODIGO];
char cadena [61];
struct caracterCodigo
{
  char caracter;
  char codigo[TAMCODIGO + 1];
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
  {3,  "11110\0"}
};

char decodificador(int * codigo) {
  char  codigoS[] = {codigo[0] + 48, codigo[1] + 48, codigo[2] + 48, codigo[3] + 48, codigo[4] + 48, '\0'};
  for (int i = 0; i < CANTCARATERES; ++i) {
    if (strcmp(codigoS, decode[i].codigo) == 0) {
      return decode[i].caracter;
    }
  }

}

void setup() {
  // put your setup code here, to run once:
  pinMode(pin, INPUT);
  Serial.begin(9600);
}

void loop() {

  int bitRecibido = recvBit(pin);
  while (bitRecibido != -1) {
    codigo[cantRecibidos] = bitRecibido;
    bitRecibido = recvBit(pin);
    cantRecibidos += 1;
    if (cantRecibidos >= 5) {
      char recibido = decodificador(codigo);
      cadena[cantCar] = recibido;
      if (cadena[cantCar] == 3) {
        cadena[cantCar] = '\0';
        Serial.println(cadena);
        cantCar = -1;
      }
      cantRecibidos = 0;
      cantCar += 1;
    }
  }

}

int recvBit(int pin) {
  int cont = 0;
  while (cont <= n && digitalRead(pin) == LOW) {
    cont++;
    delay(TAU / n);
  }
  if (cont > n)
    return -1;
  else {
    cont  = 0;
    while (digitalRead(pin) == HIGH) {
      cont++;
      delay(TAU / n);
    }
    if (cont > n)
      return 1;
    else
      return 0;

  }

}
