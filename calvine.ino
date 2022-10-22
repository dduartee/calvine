// robo segue linha preta com o CRT5000

#include <AFMotor.h>

AF_DCMotor motor4(4);
AF_DCMotor motor3(3);

int pinoCentral = 22;
int pinoEsquerda = 24;
int pinoDireita = 26;

int contadorIndicadorDireita = 0;
int contadorIndicadorEsquerda = 0;

int voltas = 0;

void setup()
{
  pinMode(pinoCentral, INPUT);  // pino central do modulo
  pinMode(pinoEsquerda, INPUT); // pino extremo esquerdo do modulo
  pinMode(pinoDireita, INPUT);  // pino extremo direito do modulo
  Serial.begin(9600);

  motor4.setSpeed(255);
  motor3.setSpeed(255);
  motor4.run(FORWARD);
  motor3.run(FORWARD);
};

void loop()
{
  // atualiza o estado dos sensores
  bool indicadorEsquerdo = digitalRead(pinoEsquerda); // s1
  delay(100);                                         // delay para estabilizar o sensor
  bool faixaCentral = digitalRead(pinoCentral);       // s3
  delay(100);
  bool indicadorDireito = digitalRead(pinoDireita); // s5

  countController(esquerda, direita);

  leftIndicatorController(indicadorEsquerdo);
  rightIndicatorController(indicadorDireito);
};

/**
 * @brief Controla a contagem dos indicadores de curva
 *
 */
void countController(esquerda, direita)
{
  if (voltas == 2)
  {
    delay(200); // anda um pouquinho
    contadorIndicadorDireita = 0;
    contadorIndicadorEsquerda = 0;
    voltas = 0;
    stop();
  }
  if (esquerda == 1)
  {
    contadorIndicadorEsquerda++;
  }
  if (direita == 1)
  {
    contadorIndicadorDireita++;
  }
}

/**
 * @brief Controla as ações pelo indicador esquerdo
 *
 */
void leftIndicatorController(indicadorEsquerdo)
{
  if (indicadorEsquerdo)
  {
    if (contadorIndicadorEsquerda % 2 == 0)
    {
      // se o sensor esquerdo detectar um ponto e o contador for par, isso significa que não
      // há curvas, então o robo segue em frente
      moveStraight();
    }
    else
    {
      if (contadorIndicadorEsquerda == 5)
      {
        longTurnRight();
      }
      else if (contadorIndicadorEsquerda == 15)
      {
        turnRight();
      }
      else if (contadorIndicadorEsquerda == 16)
      {
        contadorIndicadorEsquerda++ // pula pro 17
      }
      else
      {
        turnLeft();
      }
    }
  }
}

void rightIndicatorController(indicadorDireito)
{
  if (indicadorDireito)
  {
    if (contadorIndicadorDireita == 2)
    {
      // volta completa
      voltas++;
      contadorIndicadorDireita = 0;
      contadorEsquerda = 0;
      moveStraight();
    }
  }
}
/**
 * @brief Faz o robo seguir em frente
 *
 */
void moveStraight()
{
  motor3.setSpeed(255);
  motor4.setSpeed(255);
  motor4.run(FORWARD);
  motor3.run(FORWARD);
}
void turnRight()
{
  motor3.setSpeed(50);
  motor4.setSpeed(128);
  motor4.run(FORWARD);
  motor3.run(FORWARD);
}
void turnLeft()
{
  motor3.setSpeed(128);
  motor4.setSpeed(50);
  motor4.run(FORWARD);
  motor3.run(FORWARD);
}
void stop()
{
  motor3.setSpeed(0);
  motor4.setSpeed(0);
  motor4.run(FORWARD);
  motor3.run(FORWARD);
}
void longTurnRight()
{
  motor3.setSpeed(128);
  motor4.setSpeed(255);
  motor3.run(FORWARD);
  motor4.run(FORWARD);
}