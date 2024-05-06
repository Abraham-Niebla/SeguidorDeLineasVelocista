// /*ControladorMovimiento.cpp*/
// #include "ControladorMovimiento.h"
// #include <Arduino.h>

// /* Constructor de objetos */
// ControladorMovimiento::ControladorMovimiento(int A, int B)
// {
//     pinA = A;
//     pinB = B;
// }

// /* Inicializador de objetos */
// void ControladorMovimiento::begin()
// {
//     pinMode(pinA, OUTPUT);
//     pinMode(pinB, OUTPUT);

//     detener();
// }

// /* Activa una salida PWM para que el ControladorMovimiento gire hacia el sentido A */
// void ControladorMovimiento::avanzar(int pwm)
// {
//     analogWrite(pinA, pwm);
//     analogWrite(pinB, 0);
// }

// /* Activa una salida PWM para que el ControladorMovimiento gire hacia el sentido B */
// void ControladorMovimiento::retroceder(int pwm)
// {
//     analogWrite(pinA, 0);
//     analogWrite(pinB, pwm);
// }

// /* Pone en estado bajo ambos pines del ControladorMovimiento para que deje de girar */
// void ControladorMovimiento::detener()
// {
//     analogWrite(pinA, 0);
//     analogWrite(pinB, 0);
// }
