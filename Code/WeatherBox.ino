#include <avr/sleep.h>

/*
The Watchdog & Sleep Mode code was lovingly adapted from
Nathan Seidle's SparkFun Electronics Arduino code for
H2OhNo!.

An Atmel ATtiny85 microcontroller was made Arduino-
compatible with the AVR Tiny Programmer and ATtiny
Board Support by David Mellis.

This Sketch is ~944 bytes.
Set Internal 8MHz clock for ATtiny85.
Burn Bootloader FIRST, this action sets the clock
fuse to 8MHz.
*/

//Pin Defs
//Arduino-Defined Pin 0 is really pin #5 on the ATtiny85
const byte relayTrigger = 0;

volatile int watchdog_counter;

//This runs each time the watchdog wakes up
ISR(WDT_vect){
  watchdog_counter++;
}

void setup() {
  // put your setup code here, to run once:
pinMode(relayTrigger, OUTPUT);

digitalWrite(relayTrigger, LOW);

watchdog_counter = 0;

//Power down all unnecessary hardware
set_sleep_mode(SLEEP_MODE_PWR_DOWN);
sleep_enable();
ADCSRA &= ~(1<<ADEN); //Disables the ADC

setup_watchdog(7); //Wake up after 2 sec
}

void loop() {
  // put your main code here, to run repeatedly:
sleep_mode(); //Go to sleep

if(watchdog_counter > 150) {
  watchdog_counter = 0;

  triggerSensortag(); //Turn on the TI Sensortag Bluetooth
  digitalWrite(relayTrigger, LOW); //Ensure relay is OFF
}

}

void triggerSensortag(void)
{
  digitalWrite(relayTrigger, HIGH);
  delay(100);
}

void setup_watchdog(int timerPrescaler) {

  if(timerPrescaler > 9) timerPrescaler = 9; //Adjust amount

  byte bb = timerPrescaler & 7;
  if (timerPrescaler > 7) bb |= (1<<5); //Set 5th bit if needed

  // This sequence can NOT be altered
  MCUSR &= ~(1<<WDRF); //Clear the watchdog reset
  WDTCR |= (1<<WDCE) | (1<<WDE); //Set WD_change & WD both enable
  WDTCR = bb; //Set new watchdog timeout
  WDTCR |= _BV(WDIE); //Set interrupt enable
}
