# arduino-robo-servo-motor

## Objetivo

Robô desenvolvido com materiais recicláveis em uma placa Arduino, com dois micro servo motores e uma placa de som KY-038. O robô reage com os olhos e a boca ao som de duas palmas.

### Vídeo

[![Vídeo](https://user-images.githubusercontent.com/22710963/77988240-33818600-72f2-11ea-90d7-3b26ab14ccb1.png)](https://youtu.be/NDME2-helR8)

### Circuito
  
![image](https://user-images.githubusercontent.com/22710963/78057168-ab849600-735c-11ea-923e-fc8b906a689a.png)
  
### Hardware necessário

```
- a) 1 Placa Arduino com cabo USB
- b) 2 Micro servo motores
- c) 1 Sensor som ky-038  
- d) 1 Protoboard
- h) 10-15 Cabos de conexão
```

#### a) Placa Arduino Uno

![image](https://user-images.githubusercontent.com/22710963/77551422-16cbf500-6e91-11ea-850d-7e3989c9f1f2.png)

#### b) Micro servo motores

![image](https://user-images.githubusercontent.com/22710963/77988474-d63a0480-72f2-11ea-905d-bb5b899f1170.png)

#### c) Sensor Som KY-038
  
![image](https://user-images.githubusercontent.com/22710963/77604369-14998300-6ef1-11ea-977d-2bbdb8241a28.png)

#### d) Protoboard

![image](https://user-images.githubusercontent.com/22710963/77499362-a8574a80-6e30-11ea-9744-a15c3206fd50.png)

#### e) Cabos de conexão

![image](https://user-images.githubusercontent.com/22710963/77499606-5662f480-6e31-11ea-96fd-9e268dceb50f.png)

### Material utilizado para confeccionar a estrutura do robô

- Corpo do Robô: 1  isopor 40x25cm ( veio num gabinete de computador)

- Olhos: 25 cm cano PVC de 40mm para dar movimento com dois parafusos fixados para serem os olhos

- Boca: 1 tampa de pacote de lenço umedecido do tipo abre/fecha

- Arames firmes mas maleáveis: 1m para fixar os servo motores no isopor e para dar a movimentação dos servos aos olhos e a boca

- 3 Prendedores de roupa: as pernas separadas foram utilizadas para passar o arame e fixar os servos ao isopor

### Funcionamento

Velocidade em que os motores movimentam-se pode ser alterada nessa variável

``` 
// velocidade dos movimentos
#define VEL_MOVIMENTO 30

```

Declaração do ângulo máximo e mínimo de movimentação dos servos. Se a movimentaçao do motor ficar presa por um ângulo inserido errado ele pode estragar ou impedir a execução correta das outras instruções uma vez que ele aguarda o movimento completo do eixo para seguir com as instruções.

```
// create servo objects
VarSpeedServo servoOlhos;
int ANG_MAX_MIN_OLHOS[] = {0, 70};

VarSpeedServo servoBoca;
int ANG_MAX_MIN_BOCA[] = {20, 90};
```
Ao escutar 2 palmas [...]

``` 
    if (((millis() - esperaPalmas) > intervaloPalmas) && (quantidadePalmas != 0))
    {
        if (quantidadePalmas == 2)
        {

            movimentarOlhosBoca();
        }

        delay(delayfinal);
        quantidadePalmas = 0;  
    }
```

[...] o robô vai movimentar-se 100 vezes com ângulos gerados randomicamente, dentro da faixa de limites declarada.

```
void movimentarOlhosBoca()
{
    // define como verdadeiro para impedir que o ruído do motor do servo
    // invoque o método novamente

    emMovimentacao = true;

    for (size_t i = 0; i < 100; i++)
    {
        Serial.println(i);
        /*  (angulo, velocidade, aguarda movimento completo para ir proxima instrucao) */
        servoOlhos.write(gerarNumeroRandomico(ANG_MAX_MIN_OLHOS), VEL_MOVIMENTO, true);
        servoBoca.write(gerarNumeroRandomico(ANG_MAX_MIN_BOCA), VEL_MOVIMENTO, true);
    };

    posicionarAnguloInicioServo();
    delay(2000);
    emMovimentacao = false;
}

```

Enquanto o robô movimenta-se ele para de ouvir, para que o ruído do motor não acione novamente os movimentos.

```
void loop()
{
    if (!emMovimentacao)
        escutarPalmas();
}

```

#### Links úteis

- [VarSpeedServo](https://github.com/netlabtoolkit/VarSpeedServo) - Biblioteca com controle de velocidade dos movimentos

### Aplicações

- Desenvolver criatividade de crianças e adultos

- Brinquedo infantil
