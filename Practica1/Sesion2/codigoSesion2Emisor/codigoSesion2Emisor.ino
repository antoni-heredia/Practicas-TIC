int TAU = 4;
int pin = 8;

int CANTCARATERES = 31;
#define TAMCODIGO 5
struct caracter
{
  char caracter;
  int codigo[TAMCODIGO];
};

struct caracter characters[31] = {
  {'a',  {0, 0, 0, 0, 0}},
  {'b',  {0, 0, 0, 0, 1}},
  {'c',  {0, 0, 0, 1, 0}},
  {'d',  {0, 0, 0, 1, 1}},
  {'e',  {0, 0, 1, 0, 0}},
  {'f',  {0, 0, 1, 0, 1}},
  {'g',  {0, 0, 1, 1, 0}},
  {'h',  {0, 0, 1, 1, 1}},
  {'i',  {0, 1, 0, 0, 0}},
  {'j',  {0, 1, 0, 0, 1}},
  {'k',  {0, 1, 0, 1, 0}},
  {'l',  {0, 1, 0, 1, 1}},
  {'m',  {0, 1, 1, 0, 0}},
  {'n',  {0, 1, 1, 0, 1}},
  {'o',  {0, 1, 1, 1, 0}},
  {'p',  {0, 1, 1, 1, 1}},
  {'q',  {1, 0, 0, 0, 0}},
  {'r',  {1, 0, 0, 0, 1}},
  {'s',  {1, 0, 0, 1, 0}},
  {'t',  {1, 0, 0, 1, 1}},
  {'u',  {1, 0, 1, 0, 0}},
  {'v',  {1, 0, 1, 0, 1}},
  {'w',  {1, 0, 1, 1, 0}},
  {'x',  {1, 0, 1, 1, 1}},
  {'y',  {1, 1, 0, 0, 0}},
  {'z',  {1, 1, 0, 0, 1}},
  {'.',  {1, 1, 0, 1, 0}},
  {',',  {1, 1, 0, 1, 1}},
  {';',  {1, 1, 1, 0, 0}},
  {' ',  {1, 1, 1, 0, 1}},
  {3,   {1, 1, 1, 1, 0}}
};

int * codificador(char letra) {
  for (int i = 0; i < CANTCARATERES; ++i) {
    if (characters[i].caracter == letra) {
      return characters[i].codigo;
    }
  }
}
void setup() {
  // put your setup code here, to run once:
  pinMode(pin, OUTPUT);
  Serial.begin(9600);
}
void loop() {
  int * codigo;
  bool leido = false;
  while (Serial.available() > 0) {
    leido = true;
    codigo  = codificador(Serial.read ());
    for (int i = 0; i < TAMCODIGO; ++i) {
      sendBit(codigo[i], pin);
    }
  }
  if (leido) {
    codigo  = codificador(3);
    for (int i = 0; i < TAMCODIGO; ++i) {
      sendBit(codigo[i], pin);
    }
  }
}

void sendBit(int value, int pin) {
  digitalWrite(pin, HIGH);

  if (value == 0)
    delay(TAU);
  else if (value == 1)
    delay(2 * TAU);

  digitalWrite(pin, LOW);
  delay(TAU);

};
