// /*Motor.cpp*/
// #include "Motor.h"
// #include <Arduino.h>

// /* Constructor de objetos */
// Motor::Motor(int A, int B)
// {
//     pinA = A;
//     pinB = B;
// }

// /* Inicializador de objetos */
// void Motor::begin()
// {
//     pinMode(pinA, OUTPUT);
//     pinMode(pinB, OUTPUT);

//     detener();
// }

// /* Activa una salida PWM para que el motor gire hacia el sentido A */
// void Motor::avanzar(int pwm)
// {
//     analogWrite(pinA, pwm);
//     analogWrite(pinB, 0);
// }

// /* Activa una salida PWM para que el motor gire hacia el sentido B */
// void Motor::retroceder(int pwm)
// {
//     analogWrite(pinA, 0);
//     analogWrite(pinB, pwm);
// }

// /* Pone en estado bajo ambos pines del motor para que deje de girar */
// void Motor::detener()
// {
//     analogWrite(pinA, 0);
//     analogWrite(pinB, 0);
// }
