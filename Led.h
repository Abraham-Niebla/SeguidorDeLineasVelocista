/*Led.h*/
#ifndef Led_h
#define Led_h

#include <Arduino.h>

class Led
{
  public:
      Led(int pinLED); // Constructor de objetos
      void begin(); // Inicializador del Led

      void encender();
      void apagar();
      void parpadear(int veces, int milisegundos);
      void parpadearUno(int milisegundos);
      void encenderTemporal(int milisegundos);

  private:
      uint8_t pin; //Pin del Led
};

#endif