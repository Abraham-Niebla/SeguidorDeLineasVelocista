// /*Turbina.cpp*/
// #include "Turbina.h"
// #include <Arduino.h>

// /* Constructor de objetos */
// Turbina::Turbina(int pinTurbina)
// {
//     pin = pinTurbina;
// }

// /* Inicializador de objetos */
// void Turbina::begin()
// {
//     pinMode(pin, OUTPUT);

//     detener();
// }

// /* Activa una salida PWM para que el Turbina gire */
// void Turbina::activar(int pwm)
// {
//     analogWrite(pin, pwm);
// }

// /* Pone en estado bajo el pin para que la Turbina deje de girar */
// void Turbina::detener()
// {
//     analogWrite(pin, 0);
// }
