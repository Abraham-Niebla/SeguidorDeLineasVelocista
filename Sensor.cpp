// /*Sensor.cpp*/
// #include "Sensor.h"
// #include <Arduino.h>
// #include <QTRSensors.h>

// /* Constructor de objetos */
// Sensor::Sensor(const uint8_t sensorPins[], uint8_t sensorsNo)
// {
//   sensorCount = sensorsNo;
//   pins = new uint8_t[sensorCount];  // Asignar memoria para los pines
//   memcpy(pins, sensorPins, sensorCount);     // Copiar los valores de los pines
//   sensorValues = new uint16_t[sensorCount];  // Asignar memoria para los valores del sensor
//   delete[] sensorPins;
// }

// /* Inicializador de objetos */
// void Sensor::begin(bool analog)
// {
//   if (analog) //Si es de tipo analogico
//     qtr.setTypeAnalog();
//   else //Si es de tipo digital
//     qtr.setTypeRC();

//   qtr.setSensorPins(pins, SensorCount);
// }

// /* Va a calibrar el sensor un determinado número de veces */
// void Sensor::calibrar(uint16_t veces)
// {
//   // analogRead() takes about 0.1 ms on an AVR.
//   // 0.1 ms per sensor * 4 samples per sensor read (default) * 6 sensors
//   // * 10 reads per calibrate() call = ~24 ms per calibrate() call.
//   // Call calibrate() 400 times to make calibration take about 10 seconds.
//   // Call calibrate() 200 times to make calibration take about  5 seconds.
//   for (uint16_t i = 0; i < veces; i++)  // Original: i < 400
//   {
//     qtr.calibrate();
//   }
// }

// /* Devuelve el valor de la posición respecto a la linea blanca (0) o negra (1) */
// uint16_t Sensor::leerLinea(bool color)
// {
//   if(color) //Si pide linea blanca
//     return qtr.readLineWhite(sensorValues);
//   else //Si pide linea negra
//     return qtr.readLineBlack(sensorValues);
// }
