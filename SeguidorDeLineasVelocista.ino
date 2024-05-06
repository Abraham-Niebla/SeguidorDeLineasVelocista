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
int velocidadMax = 0;
// int potenciaMax = 0;
// int potenciador = 0;
int sp = 2500;  //Valor de referencia para PD
uint16_t position = 0;
//
float kp = 0;
float kd = 0;
//
// float derivada = 0, proporcional = 0;
int signal = 0;
//
int errorAnterior = 0;
int error = 0;
//

void setup()
{
  led.begin();
  boton.begin(0);

  definePines();
  defineSensor();

  led.parpadear(3, 100);

  //esperar boton
  // while (digitalRead(BTN) == 1) {};
  boton.esperarPresionar();
  unsigned long tiempo = millis();

  // while (digitalRead(BTN) == 0) {};
  boton.esperarSoltar();
  tiempo = millis() - tiempo;

  delay(250);

  uint8_t v = 0;

  if (tiempo <= 1000)
  {
    v = 1;
    velocidadMax = 70;

    kp = 0.8; // 0.8
    kd = 2.6; // 2.6
  }
  else if (tiempo <= 2000)
  {
    v = 2;
    velocidadMax = 120;

    kp = 1.0;
    kd = 3.6;                                                                                                              
  }
  else
  {
    v = 3;
    velocidadMax = 160;

    kp = 0.7;
    kd = 2.5;
  }

  // potenciaMax = velocidadMax;// * potenciador;
  // if (potenciaMax > 255)
  //   potenciaMax = 255;

  led.parpadear(v, 300);

  delay(1000);

  led.encender();
  calibrateSensor();
  led.apagar();
  led.parpadear(3, 100);

  // while (digitalRead(BTN) == 1) {};
  boton.esperarPresionar();

  led.parpadear(3, 100);

  delay(1000);
}

void loop() 
{
  // read calibrated sensor values and obtain a measure of the line position
  // from 0 to 5000 (for a white line, use readLineWhite() instead)
  position = qtr.readLineBlack(sensorValues);

  error = sp - position;

  signal = ((kp * error) + (kd * (error - errorAnterior)));

  errorAnterior = error;

  if (signal > velocidadMax)
    signal = velocidadMax;

  if (signal < -velocidadMax)
    signal = -velocidadMax;

  if (signal > 0)
  {
    establecerMotores(velocidadMax - signal, velocidadMax);
  }
  else
  {
    establecerMotores(velocidadMax, velocidadMax + signal);
  }
}


void definePines()
{
  // pinMode(LED, OUTPUT);
  // pinMode(BTN, INPUT_PULLUP);  //Lectura de 0 al presionar

  pinMode(MOTORI_A, OUTPUT);
  pinMode(MOTORI_B, OUTPUT);

  pinMode(MOTORD_A, OUTPUT);
  pinMode(MOTORD_B, OUTPUT);

  // pinMode(TURBINA, OUTPUT);
}

void defineSensor()
{
  qtr.setTypeAnalog();
  qtr.setSensorPins((const uint8_t[]){ S7, S6, S5, S4, S3, S2 }, SensorCount);
}

void calibrateSensor()
{
  // analogRead() takes about 0.1 ms on an AVR.
  // 0.1 ms per sensor * 4 samples per sensor read (default) * 6 sensors
  // * 10 reads per calibrate() call = ~24 ms per calibrate() call.
  // Call calibrate() 400 times to make calibration take about 10 seconds.
  // Call calibrate() 200 times to make calibration take about  5 seconds.
  for (uint16_t i = 0; i < 200; i++) // Original: i < 400
  {
    qtr.calibrate();
  }
}

void establecerMotores(int motorI, int motorD)
{
  analogWrite(MOTORI_A, 0);
  analogWrite(MOTORI_B, motorI);

  analogWrite(MOTORD_A, motorD);
  analogWrite(MOTORD_B, 0);
}