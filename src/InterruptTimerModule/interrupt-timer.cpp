// C++ code
//
/* Arduino 101: timer and interrupts
   Timer1 compare match interrupt example
   more infos: http://www.letmakerobots.com/node/28278
   Inspired by RobotFreak

   startInterruptTimer takes the following parameters:
   - hz - int defining the frequency of the interrupt routine
   - outPin - Optional byte specifying the pin for the output signal.
      - Default = 0 - no pin gets the signal

    - Returns int - the actual frequency of the timer
*/
#include "interrupt-timer.h"

// byte boardPin = 13;

byte outputPin = 0;

volatile unsigned long appClock = 0;
volatile byte signal2Hz = LOW;
int appClockFreq = 0;

int startInterruptTimer(int hz, byte outPin)
{
  if (!hz)
    return 0; // Avoid divide by 0

  outputPin = outPin;
  if (outputPin)
    pinMode(outputPin, OUTPUT);

  int realHz = hz % 2 == 0 ? hz : hz + 1;

  const long clockFreq = 16000000;
  const int prescaler = 256;

  // initialize timer1
  noInterrupts(); // disable all interrupts
  TCCR1A = 0;     // Timer Counter Control Register A
  TCCR1B = 0;     // Timer Counter Control Register B
  TCNT1 = 0;      // Timer Counter reset to 0

  // compare match register 16MHz/256/2Hz = 31250
  OCR1A = clockFreq / prescaler / realHz;
  TCCR1B |= (1 << WGM12);  // CTC mode - logical OR with 0001 << 3 = 1000
  TCCR1B |= (1 << CS12);   // 256 prescaler
  TIMSK1 |= (1 << OCIE1A); // enable timer compare interrupt in Timer Mask 1

  interrupts(); // enable all interrupts

  return realHz;
};

void reportTick()
{
  appClock++;
  signal2Hz = (appClock % (appClock >> 1) == 0) ? !signal2Hz : signal2Hz;
}

// timer compare interrupt service routine
ISR(TIMER1_COMPA_vect)
{
  reportTick();
}
