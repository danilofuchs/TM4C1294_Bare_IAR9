// Displays Gray code counting on builtin LEDs

#include <stdbool.h>
#include <stdint.h>

#include "driverleds.h"  // Projects/drivers
#include "driverlib/systick.h"

typedef enum {
  State_0,
  State_1,
  State_2,
  State_3,
  State_4,
  State_5,
  State_6,
  State_7
} state_t;

volatile uint8_t Evento = 0;

void SysTick_Handler(void) { Evento = 1; }

void main(void) {
  static state_t Estado = State_0;

  LEDInit(LED1);
  LEDInit(LED2);
  LEDInit(LED3);
  SysTickPeriodSet(12000000);  // f = 1Hz for clock = 24MHz
  SysTickIntEnable();
  SysTickEnable();

  while (1) {
    if (Evento) {
      Evento = 0;
      switch (Estado) {
        case State_0:
          // 000
          LEDOff(LED1);
          LEDOff(LED2);
          LEDOff(LED3);
          Estado = State_1;
          break;
        case State_1:
          // 001
          LEDOff(LED1);
          LEDOff(LED2);
          LEDOn(LED3);
          Estado = State_2;
          break;
        case State_2:
          // 011
          LEDOff(LED1);
          LEDOn(LED2);
          LEDOn(LED3);
          Estado = State_3;
          break;
        case State_3:
          // 010
          LEDOff(LED1);
          LEDOn(LED2);
          LEDOff(LED3);
          Estado = State_4;
          break;
        case State_4:
          // 110
          LEDOn(LED1);
          LEDOn(LED2);
          LEDOff(LED3);
          Estado = State_5;
          break;
        case State_5:
          // 111
          LEDOn(LED1);
          LEDOn(LED2);
          LEDOn(LED3);
          Estado = State_6;
          break;
        case State_6:
          // 101
          LEDOn(LED1);
          LEDOff(LED2);
          LEDOn(LED3);
          Estado = State_7;
          break;
        case State_7:
          // 100
          LEDOn(LED1);
          LEDOff(LED2);
          LEDOff(LED3);
          Estado = State_0;
          break;
      }
    }
  }
}
