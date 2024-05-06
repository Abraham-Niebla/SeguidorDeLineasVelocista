// /*Sensor.h*/
// #ifndef Sensor_h
// #define Sensor_h

// #include <Arduino.h>
// #include <QTRSensors.h>

// class Sensor
// {
//   public:
//       Sensor(const uint8_t sensorPins[], uint8_t sensorsNo); // Constructor de objetos
//       void begin(bool analog); // Inicializador del Sensor

//       void calibrar(uint16_t veces);
//       uint16_t leerLinea(bool color);

//   private:
//       const uint8_t* pins; //Pines del Sensor
//       uint8_t sensorCount; //Total de Sensores
//       uint16_t* sensorValues; //Valores de los Sensores
//       QTRSensors qtr; //Objeto de la clase QTRSensors
// };

// #endif