#include <VarSpeedServo.h>

// create servo objects
VarSpeedServo servoOlhos;
VarSpeedServo servoBoca;
// velocidade dos movimentos
int SPEED = 50;

void setup()
{
    // setando pino para servo e definindo grau min e máximo (pino, angulo minimo, angulo maximo)
    servoOlhos.attach(13, 40, 100);
    servoBoca.attach(12, 40, 100);
}

void loop()
{

    movimentarOlhosBoca();
}

void movimentarOlhosBoca()
{
    delay(1000);

    // (angulo, velocidade, aguarda movimento completo para ir proxima instrucao)
    servoOlhos.write(40, SPEED, true);
    servoBoca.write(40, SPEED, true);

    servoOlhos.write(80, SPEED, true);
    servoBoca.write(80, SPEED, true);

    servoOlhos.write(100, SPEED, true);
    servoBoca.write(100, SPEED, true);

    servoOlhos.write(60, SPEED, true);
    servoBoca.write(60, SPEED, true);

    servoOlhos.write(100, SPEED, true);
    servoBoca.write(100, SPEED, true);

    servoOlhos.write(70, SPEED, true);
    servoBoca.write(70, SPEED, true);

    servoOlhos.write(90, SPEED, true);
    servoBoca.write(90, SPEED, true);

    servoOlhos.write(50, SPEED, true);
    servoBoca.write(50, SPEED, true);
}
