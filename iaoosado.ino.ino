// robo segue linha preta com o CRT5000

#include <AFMotor.h>

AF_DCMotor motor4(4);
AF_DCMotor motor3(3);

int pinoCentral = 22;
int pinoEsquerda = 24;
int pinoDireita = 26;

int contadorDireita = 0;
int contadorIndicadorEsquerda = 0;

bool indicadorDireito = false;
bool indicadorEsquerdo = false;
bool faixaCentral = false;

void setup() {
  pinMode(pinoCentral, INPUT); // pino central do modulo
  pinMode(pinoEsquerda, INPUT); // pino extremo esquerdo do modulo
  pinMode(pinoDireita, INPUT); // pino extremo direito do modulo
  Serial.begin(9600);
};

void loop() {
  faixaCentral = digitalRead(pinoCentral);
  indicadorEsquerdo = digitalRead(pinoEsquerda);
  indicadorDireito = digitalRead(pinoDireita);
  
  countController();

};
/*
  Controla a contagem de pontos de cada sensor
*/
void countController() {
  countAdder();
  if(indicadorEsquerdo) {
    if (contadorIndicadorEsquerda % 2 == 0) {
    // se o sensor esquerdo detectar um ponto e o contador for par, isso significa que não 
    // há curvas, então o robo segue em frente
    } else {
      // array de numeros das curvas a direita
      int curvasDireita[] = {5, 15};
      // se a contagem for igual a um dos numeros do array, o robo faz uma curva a direita
    }
  } else if(indicadorDireito) {
    if(contadorDireita == 4) {
      // se o sensor direito detectar um ponto e o contador for 4 (2 voltas completas),
      // isso significa que o robo chegou ao fim da linha, então ele para tl;dr
    } else {
      // se não, o robo segue em frente
    }
  }
};

void countAdder() {
  if (esquerda == 1) {
    contadorIndicadorEsquerda++;
  }
  if (direita == 1) {
    contadorDireita++;
  }
}