// robo segue linha preta com o CRT5000

#include <AFMotor.h>

AF_DCMotor motor4D(4);
AF_DCMotor motor3E(3);

#define pinoE 24;
#define pinoD 26;
#define pinoIndicadorE 28;
#define pinoIndicadorD 30;
#define velocidade 70;

int contagemE = 0;
int contagemD = 0;
int voltas = 0;
void setup()
{
  pinMode(pinoE, INPUT);
  pinMode(pinoD, INPUT);
  pinMode(pinoIndicadorE, INPUT);
  pinMode(pinoIndicadorD, INPUT);
}

void loop()
{
  bool indicadorE = !digitalRead(pinoIndicadorE);
  bool indicadorD = !digitalRead(pinoIndicadorD);
  controladorContagem(indicadorE, indicadorD);

  if (voltas == 2) // se tiver 2 voltas registradas
  {
    motor4D.run(RELEASE);
    motor3E.run(RELEASE);
  }
  else
  {
    bool sensorEsquerdo = !digitalRead(pinoE);
    bool sensorDireito = !digitalRead(pinoD);

    motor4D.setSpeed(velocidade);
    motor3E.setSpeed(velocidade);

    if (sensorEsquerdo && sensorDireito) // se os dois detectarem brancos
    {
      motor4D.run(FORWARD);
      motor3E.run(FORWARD);
    }

    if (!sensorDireito && !sensorEsquerdo) // se os dois detectarem preto
    {
      // para
      motor4D.setSpeed(0);
      motor3E.setSpeed(0);
      motor4D.run(RELEASE);
      motor3E.run(RELEASE);
    }

    if (sensorEsquerdo && !sensorDireito) // se o direito detectar preto
    {
      motor4D.run(BACKWARD); // motor direito gira ao contrario
      motor3E.run(FORWARD);
    }

    if (!sensorEsquerdo && sensorDireito) // se o esquerdo detectar preto
    {
      motor4D.run(FORWARD);
      motor3E.run(BACKWARD); // motor esquerdo gira ao contrario
    }
  }
}
void controladorContagem(indicadorE, indicadorD)
{
  if (indicadorE)
  {
    contagemE++;
  }
  else if (indicadorD)
  {
    contagemD++;
  }

  if (contagemD == 2)
  {
    voltas++;
    contagemD = 0;
    contagemE = 0;
  }
}