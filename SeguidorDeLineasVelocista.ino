#include <QTRSensors.h>
#include "Led.h"
#include "Boton.h"

#define LED 7
#define BTN 9

#define MOTORI_A 3
#define MOTORI_B 11

#define MOTORD_A 5
#define MOTORD_B 6

#define TURBINA 10

#define S2 A5
#define S3 A4
#define S4 A3
#define S5 A2
#define S6 A1
#define S7 A0

const uint8_t SensorCount = 6;
uint16_t sensorValues[SensorCount];

QTRSensors qtr;
Led led(LED);
Boton boton(BTN);


//
float velocidadMax = 0;
float potenciaMax = 0;
float potenciador = 1.8; //1.8
int sp = 2500;  //Valor de referencia para PD
uint16_t position = 0;
//
float kp = 0;
float kd = 0;
//
float derivada = 0, proporcional = 0;
int potencia = 0;
//
int errorAnterior = 0;
int error = 0;
//

void setup() {
  // Serial.begin(9600);

  led.begin();
  boton.begin(0);

  definePines();
  defineSensor();

  led.parpadear(3, 100);

  //esperar boton
  boton.esperarPresionar();
  unsigned long tiempo = millis();

  boton.esperarSoltar();
  tiempo = millis() - tiempo;

  delay(250);

  uint8_t v = 0;

  if (tiempo <= 1000) {
    v = 1;
    velocidadMax = 100;

    kp = 0.3;   // 0.1
    kd = 2.2;  // 1.55
  }
  else if (tiempo <= 2000) {
    v = 2;
    velocidadMax = 150;

    kp = 0.58;  //0.2
    kd = 3.4;  //3.1
  }
  else {
    v = 3;
    velocidadMax = 200;

    kp = 0.7;
    kd = 2.5;
  }

  potenciaMax = velocidadMax * potenciador;
  if (potenciaMax > 255)
    potenciaMax = 255;

  led.parpadear(v, 300);

  delay(1000);

  led.encender();
  calibrateSensor();
  led.apagar();
  led.parpadear(3, 100);

  boton.esperarPresionar();

  led.parpadear(3, 100);

  delay(1000);
}

void loop() {
  // read calibrated sensor values and obtain a measure of the line position
  // from 0 to 5000 (for a white line, use readLineWhite() instead)
  position = qtr.readLineBlack(sensorValues);

  // Serial.println("Sensor:" + String(position));

  error = sp - position;

  // proporcional = kp * error;
  // derivada = kd * (error - errorAnterior);

  // potencia = proporcional + derivada;
  potencia = (kp * error) + (kd * (error - errorAnterior));
  // potencia = (kp * error) + (kd * (errorAnterior - error));

  errorAnterior = error;

  if (potencia > potenciaMax)
    potencia = potenciaMax;

  if (potencia < -potenciaMax)
    potencia = -potenciaMax;

  if (potencia > 0) {
    establecerMotores(velocidadMax - potencia, velocidadMax);
  } else if (potencia < 0) {
    establecerMotores(velocidadMax, velocidadMax + potencia);
  } else {
    establecerMotores(velocidadMax, velocidadMax);
  }
  // Serial.println();
}


void definePines() {
  pinMode(MOTORI_A, OUTPUT);
  pinMode(MOTORI_B, OUTPUT);

  pinMode(MOTORD_A, OUTPUT);
  pinMode(MOTORD_B, OUTPUT);

  // pinMode(TURBINA, OUTPUT);
}

void defineSensor() {
  qtr.setTypeAnalog();
  qtr.setSensorPins((const uint8_t[]){ S7, S6, S5, S4, S3, S2 }, SensorCount);
}

void calibrateSensor() {
  // analogRead() takes about 0.1 ms on an AVR.
  // 0.1 ms per sensor * 4 samples per sensor read (default) * 6 sensors
  // * 10 reads per calibrate() call = ~24 ms per calibrate() call.
  // Call calibrate() 400 times to make calibration take about 10 seconds.
  // Call calibrate() 200 times to make calibration take about  5 seconds.
  for (uint16_t i = 0; i < 200; i++)  // Original: i < 400
  {
    qtr.calibrate();
  }
}

// void establecerMotores(int motorI, int motorD) {
//   if (motorI > 255)
//     motorI = 255;
//   if (motorI < -255)
//     motorI = -255;

//   if (motorD > 255)
//     motorD = 255;
//   if (motorD < -255)
//     motorD = -255;

//   analogWrite(MOTORI_A, 0);
//   analogWrite(MOTORI_B, motorI);

//   analogWrite(MOTORD_A, motorD);
//   analogWrite(MOTORD_B, 0);
// }

void establecerMotores(int motorI, int motorD) {
  establecerMotorIzquierdo(motorI);
  establecerMotorDerecho(motorD);
}

void establecerMotorDerecho(int velocidad) {
  if (velocidad > 255)
    velocidad = 255;

  if (velocidad < -255)
    velocidad = -255;

  // Serial.print("der:" + String(velocidad) + "\t");

  if (velocidad > 0) {
    analogWrite(MOTORD_A, velocidad);
    analogWrite(MOTORD_B, 0);
  }
  else if (velocidad < 0) {
    analogWrite(MOTORD_A, 0);
    analogWrite(MOTORD_B, -velocidad);
  }
  else {
    analogWrite(MOTORD_A, 0);
    analogWrite(MOTORD_B, 0);
  }
}

void establecerMotorIzquierdo(int velocidad) {
  if (velocidad > 255)
    velocidad = 255;

  if (velocidad < -255)
    velocidad = -255;
  
  // Serial.print("izq:" + String(velocidad) + "\t");

  if (velocidad > 0) {
    analogWrite(MOTORI_A, 0);
    analogWrite(MOTORI_B, velocidad);
  }
  else if (velocidad < 0) {
    analogWrite(MOTORI_A, -velocidad);
    analogWrite(MOTORI_B, 0);
  }
  else {
    analogWrite(MOTORI_A, 0);
    analogWrite(MOTORI_B, 0);
  }
}