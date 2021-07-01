#include <stdbool.h>
#include <stdint.h>
// includes da biblioteca driverlib
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"
#include "driverlib/systick.h"
#include "inc/hw_memmap.h"

// LED D4 = PF0
#define LED_D4_PERIPHERAL SYSCTL_PERIPH_GPIOF
#define LED_D4_PORT_BASE GPIO_PORTF_BASE
#define LED_D4_PIN GPIO_PIN_0

// From system_TM4C1294_TW.c
#define SYSTEM_CLOCK_CONFIG \
  SYSCTL_XTAL_25MHZ | SYSCTL_OSC_MAIN | SYSCTL_USE_PLL | SYSCTL_CFG_VCO_480
#define SYSTEM_CLOCK (120000000UL)

#define PERIOD_SECONDS 1
#define CLOCKS_PER_EMPTY_LOOP 5

void setup_system_clock() {
  SysCtlClockFreqSet(SYSTEM_CLOCK_CONFIG, SYSTEM_CLOCK);
}

void setup_led_d4() {
  SysCtlPeripheralEnable(LED_D4_PERIPHERAL);
  while (!SysCtlPeripheralReady(LED_D4_PERIPHERAL))
    ;

  GPIOPinTypeGPIOOutput(LED_D4_PORT_BASE, LED_D4_PIN);
  GPIOPadConfigSet(LED_D4_PORT_BASE, LED_D4_PIN, GPIO_STRENGTH_12MA,
                   GPIO_PIN_TYPE_STD);
}

void main(void) {
  setup_system_clock();
  setup_led_d4();

  uint8_t led_d4_state = 0;
  GPIOPinWrite(LED_D4_PORT_BASE, LED_D4_PIN, 0);

  uint32_t counter_max = PERIOD_SECONDS * SYSTEM_CLOCK / CLOCKS_PER_EMPTY_LOOP;
  while (1) {
    for (uint32_t counter = 0; counter < counter_max; counter++) {
    }

    led_d4_state = ~led_d4_state;  // flip state
    GPIOPinWrite(LED_D4_PORT_BASE, LED_D4_PIN, led_d4_state);
  }
}