#include <VarSpeedServo.h>
#include <stdlib.h>

// create servo objects
VarSpeedServo servoOlhos;
int ANG_MAX_MIN_OLHOS[] = {30, 50};

VarSpeedServo servoBoca;
int ANG_MAX_MIN_BOCA[] = {50, 90};

// velocidade dos movimentos
#define VEL_MOVIMENTO 50

#define SEN_SOM_PIN 11

// Essas variáveis definem alguns parâmetros do programa e auxiliam na detecção e contagem das palmas.
int delayfinal = 100;      // Valor representa um tempo em milissegundos, esse tempo é aguardado pelo programa para que se inicie novamente o loop.
int duracaoPalma = 200;    // Valor representa um tempo em milissegundos, é o tempo que dura o som de uma palma, precisa ser calibrado entre 100 e 250.
int intervaloPalmas = 500; // Valor representa um tempo em milissegundos, é o intervalo máximo permitido entre uma sequência de palmas.
int quantidadePalmas = 0;  // Quantidade de palmas registradas.
long momentoPalma = 0;     // Marcador usado para a detecção das palmas, será utilizado junto com a função millis.
long esperaPalmas = 0;     // Marcador usado para contagem dos intervalos de tempo, será utilizado junto com a função millis.

bool emMovimentacao = false;

void setup()
{
    setandoPinos();
    Serial.begin(9600);
}

void loop()
{
    if (!emMovimentacao)
        escutarPalmas();
}

void setandoPinos()
{
    // setando pino para servo e definindo grau min e máximo (pino, angulo minimo, angulo maximo)
    servoOlhos.attach(7, ANG_MAX_MIN_OLHOS[0], ANG_MAX_MIN_OLHOS[1]);
    servoBoca.attach(5, ANG_MAX_MIN_BOCA[0], ANG_MAX_MIN_BOCA[1]);

    pinMode(SEN_SOM_PIN, INPUT);
}

void escutarPalmas()
{
    // Faz a leitura digital do sensor de som, quando este sensor detecta som ele desliga a porta de entrada, mudando seu estado para LOW e quando não detecta mantem em HIGH.
    int leituraSom = digitalRead(SEN_SOM_PIN);

    // Ações quando o sensor detectar som, ou seja, entrar em LOW.
    if (leituraSom == HIGH)
    {
        // Marca o momento da palma, soma a quantidade de palmas e aguarda um intervalo para não marcar a mesma palma mais de uma vez.
        if (momentoPalma == 0)
        {
            momentoPalma = esperaPalmas = millis();
            quantidadePalmas = quantidadePalmas + 1;
        }
        else if ((millis() - momentoPalma) >= duracaoPalma)
        {
            momentoPalma = 0;
        }
    }

    // Verifica se nenhuma palma mais pode ser dada
    if (((millis() - esperaPalmas) > intervaloPalmas) && (quantidadePalmas != 0))
    {
        Serial.println(quantidadePalmas);
        if (quantidadePalmas == 2)
        {

            movimentarOlhosBoca();
        }

        delay(delayfinal);    // Tempo de espera para continuar o programa, esse tempo é importante para evitar efeitos de possiveis detecções truncadas de ecos e reverberações no som.
        quantidadePalmas = 0; // Retoma a condição inicial da quantidade de palmas.
    }
}

void movimentarOlhosBoca()
{
    // define como verdadeiro para impedir que o ruído do motor do servo
    // invoque o método novamente

    emMovimentacao = true;
 
    for (size_t i = 0; i < 5; i++) {
        /*  (angulo, velocidade, aguarda movimento completo para ir proxima instrucao) */
        servoOlhos.write(gerarNumeroRandomico(ANG_MAX_MIN_OLHOS), VEL_MOVIMENTO, true);
        servoBoca.write(gerarNumeroRandomico(ANG_MAX_MIN_BOCA), VEL_MOVIMENTO, true);
    };

    delay(2000);
    emMovimentacao = false;
}

int gerarNumeroRandomico(int vetorMinMax[])
{
    return rand() % vetorMinMax[1] + vetorMinMax[0];
}