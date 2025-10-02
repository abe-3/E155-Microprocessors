/*********************************************************************
*                    SEGGER Microcontroller GmbH                     *
*                        The Embedded Experts                        *
**********************************************************************

-------------------------- END-OF-HEADER -----------------------------

File    : main.c
Purpose : Generic application start

*/

#include <stdio.h>
#include "../lib/STM32L432KC_FLASH.h"
#include "../lib/STM32L432KC_GPIO.h"
#include "../lib/STM32L432KC_RCC.h"
#include "../lib/STM32L432KC_TIM.h"

#define C2 65
#define Db2 69
#define Ab2 104
#define A2 110
#define Bb2 117
#define Ab3 208
#define Db4 277
#define F4 349
#define A3 220
#define C3 131
#define Db3 139
#define Eb3 156
#define F3 175
#define Gb3 185
#define Bb3 233
#define Eb4 311
#define Gb4 370
#define Ab4 415
#define A4 440
#define Bb4 466
#define C4 262
#define G4 392
#define C5 523
#define Db5 554
#define Eb5 622
#define F5 698
#define Gb5 740
#define Ab5 831
#define A5 880

// Pitch in Hz, duration in ms
const int fur_elise[][2] = {
{659,	125},
{623,	125},
{659,	125},
{623,	125},
{659,	125},
{494,	125},
{587,	125},
{523,	125},
{440,	250},
{  0,	125},
{262,	125},
{330,	125},
{440,	125},
{494,	250},
{  0,	125},
{330,	125},
{416,	125},
{494,	125},
{523,	250},
{  0,	125},
{330,	125},
{659,	125},
{623,	125},
{659,	125},
{623,	125},
{659,	125},
{494,	125},
{587,	125},
{523,	125},
{440,	250},
{  0,	125},
{262,	125},
{330,	125},
{440,	125},
{494,	250},
{  0,	125},
{330,	125},
{523,	125},
{494,	125},
{440,	250},
{  0,	125},
{494,	125},
{523,	125},
{587,	125},
{659,	375},
{392,	125},
{699,	125},
{659,	125},
{587,	375},
{349,	125},
{659,	125},
{587,	125},
{523,	375},
{330,	125},
{587,	125},
{523,	125},
{494,	250},
{  0,	125},
{330,	125},
{659,	125},
{  0,	250},
{659,	125},
{1319,	125},
{  0,	250},
{623,	125},
{659,	125},
{  0,	250},
{623,	125},
{659,	125},
{623,	125},
{659,	125},
{623,	125},
{659,	125},
{494,	125},
{587,	125},
{523,	125},
{440,	250},
{  0,	125},
{262,	125},
{330,	125},
{440,	125},
{494,	250},
{  0,	125},
{330,	125},
{416,	125},
{494,	125},
{523,	250},
{  0,	125},
{330,	125},
{659,	125},
{623,	125},
{659,	125},
{623,	125},
{659,	125},
{494,	125},
{587,	125},
{523,	125},
{440,	250},
{  0,	125},
{262,	125},
{330,	125},
{440,	125},
{494,	250},
{  0,	125},
{330,	125},
{523,	125},
{494,	125},
{440,	500},
{  0,	50}};

const int un_sospiro[][2] = {
//                                         //  In treble                                                              // In bass
{Db2, 31}, {Ab2, 31}, {Db3, 31}, {F3, 31}, {Ab3, 31}, {Db4, 31}, {F4, 31}, {Ab4, 31}, {F4, 31}, {Db4, 31}, {Ab3, 31}, {F3, 31}, {Db3, 31}, {Ab2, 31},
{Db2, 31}, {Ab2, 31}, {Db3, 31}, {F3, 31}, {Ab3, 31}, {Db4, 31}, {F4, 31}, {Ab4, 31}, {F4, 31}, {Db4, 31}, {Ab3, 31}, {F3, 31}, {Db3, 31}, {Ab2, 31},
{Db2, 31}, {Ab2, 31}, {Db3, 31}, {F3, 31}, {Ab3, 31}, {Db4, 31}, {F4, 31}, {Ab4, 31}, {F4, 31}, {Db4, 31}, {Ab3, 31}, {F3, 31}, {Db3, 31}, {Ab2, 31},
{Db2, 31}, {Ab2, 31}, {Db3, 31}, {F3, 31}, {Ab3, 31}, {Db4, 31}, {F4, 31}, {Ab4, 31}, {F4, 31}, {Db4, 31}, {Ab3, 31}, {F3, 31}, {Db3, 31}, {Ab2, 31},

{Db2, 31}, {Ab2, 31}, {Db3, 31}, {F3, 31}, {Ab3, 31}, {Db4, 31}, {F4, 31}, {Ab4, 62}, {F4, 31}, {Db4, 31}, {Ab3, 31}, {F3, 31}, {Db3, 31}, {Ab2, 31},
{Bb4, 62}, {Ab2, 31}, {Db3, 31}, {F3, 31}, {Ab3, 31}, {Db4, 31}, {F4, 31}, {Db5, 62}, {F4, 31}, {Db4, 31}, {Ab3, 31}, {F3, 31}, {Db3, 31}, {Ab2, 31},
{Eb5, 62}, {Bb2, 31}, {Db3, 31}, {Gb3, 31}, {Bb3, 31}, {Db4, 31}, {Gb4, 31}, {F5, 62}, {Gb4, 31}, {Db4, 31}, {Bb3, 31}, {Gb3, 31}, {Db3, 31}, {Bb2, 31},
{Eb5, 62}, {Bb2, 31}, {Db3, 31}, {Gb3, 31}, {Bb3, 31}, {Db4, 31}, {Gb4, 31}, {Bb4, 62}, {Gb4, 31}, {Db4, 31}, {Bb3, 31}, {Gb3, 31}, {Db3, 31}, {Bb2, 31},

{Db5, 62}, {Ab2, 31}, {Db3, 31}, {F3, 31}, {Ab3, 31}, {Db4, 31}, {F4, 31}, {Ab4, 31}, {F4, 31}, {Db4, 31}, {Ab3, 31}, {F3, 31}, {Db3, 31}, {Ab2, 31},
{Db2, 31}, {Ab2, 31}, {Db3, 31}, {F3, 31}, {Ab3, 31}, {Db4, 31}, {F4, 31}, {Ab4, 31}, {F4, 31}, {Db4, 31}, {Ab3, 31}, {F3, 31}, {Db3, 31}, {Ab2, 31},
{Db2, 31}, {Ab2, 31}, {Db3, 31}, {F3, 31}, {Ab3, 31}, {Db4, 31}, {F4, 31}, {Ab4, 62}, {F4, 31}, {Db4, 31}, {Ab3, 31}, {F3, 31}, {Db3, 31}, {Ab2, 31},
{Bb4, 62}, {Ab2, 31}, {Db3, 31}, {F3, 31}, {Ab3, 31}, {Db4, 31}, {F4, 31}, {Db5, 62}, {F4, 31}, {Db4, 31}, {Ab3, 31}, {F3, 31}, {Db3, 31}, {Ab2, 31},

{Eb5, 62}, {Bb2, 31}, {Db3, 31}, {Gb3, 31}, {Bb3, 31}, {Db4, 31}, {Gb4, 31}, {F5, 62}, {Gb4, 31}, {Db4, 31}, {Bb3, 31}, {Gb3, 31}, {Db3, 31}, {Bb2, 31},
{Eb5, 62}, {Bb2, 31}, {Db3, 31}, {Gb3, 31}, {Bb3, 31}, {Db4, 31}, {Gb4, 31}, {Bb4, 62}, {Gb4, 31}, {Db4, 31}, {Bb3, 31}, {Gb3, 31}, {Db3, 31}, {Bb2, 31},
{Db5, 62}, {Ab2, 31}, {Db3, 31}, {F3, 31}, {Ab3, 31}, {Db4, 31}, {F4, 31}, {Ab4, 31}, {F4, 31}, {Db4, 31}, {Ab3, 31}, {F3, 31}, {Db3, 31}, {Ab2, 31},
{Db2, 31}, {Ab2, 31}, {Db3, 31}, {F3, 31}, {Ab3, 31}, {Db4, 31}, {F4, 31}, {Ab4, 31}, {F4, 31}, {Db4, 31}, {Ab3, 31}, {F3, 31}, {Db3, 31}, {Ab2, 31},     // end of page 1

{C2, 31}, {A2, 31}, {Eb3, 31}, {F3, 31}, {A3, 31}, {Eb4, 31}, {F4, 31}, {A4, 31}, {Gb5, 62}, {A4, 31}, {F4, 31}, {Eb4, 31}, {A3, 31}, {F3, 31}, {Eb3, 31}, {A2, 31},
{F5, 62}, {C3, 31}, {Eb3, 31}, {F3, 31}, {C4, 31}, {Eb4, 31}, {F4, 31}, {C5, 62}, {F4, 31}, {Eb4, 31}, {C4, 31}, {F3, 31}, {Eb3, 31}, {C3, 31},
{Eb5, 62}, {Db3, 31}, {F3, 31}, {Bb3, 31}, {Db4, 31}, {F4, 31}, {Bb4, 31}, {Db5, 62}, {Bb4, 31}, {F4, 31}, {Db4, 31}, {Bb3, 31}, {F3, 31}, {Db3, 31},
{Ab5, 62}, {Db3, 31}, {Eb3, 31}, {Bb3, 31}, {Db4, 31}, {Eb4, 31}, {Bb4, 31}, {Gb5, 62}, {Bb4, 31}, {Eb4, 31}, {Db4, 31}, {Bb3, 31}, {Eb3, 31}, {Db3, 31},

{Ab4, 124}, {F3, 31}, {Ab3, 31}, {Db4, 31}, {Db4, 31}, {F4, 31}, {G4, 62}, {F4, 31}, {Db4, 31}, {Db4, 31}, {Ab4, 32}, {F3, 31},
{F5, 124}, {Gb3, 31}, {Ab3, 31}, {C4, 31}, {C4, 31}, {Gb4, 31}, {Ab4, 31}, {F5, 62}, {Ab4, 31}, {Gb4, 31}, {C4, 31}, {C4, 31}, {Ab3, 31}, {Gb3, 31}, {Eb5, 15},
{Db4, 124}, {Ab2, 31}, {Db3, 31}, {F3, 31}, {Ab3, 31}, {Db4, 31}, {F3, 31}, {Ab3, 62}, {F3, 31}, {Db4, 31}, {Ab3, 31}, {F3, 31}, {Db3, 31}, {Ab2, 31},
{Db2, 31}, {Ab2, 31}, {Db3, 31}, {F3, 31}, {Ab3, 31}, {Db4, 31}, {F3, 31}, {Ab3, 62}, {F3, 31}, {Db4, 31}, {Ab3, 31}, {F3, 31}, {Db3, 31}, {Ab2, 31},

{0,50}};
/*********************************************************************
*
*  main()
*
*  Function description
*  Play through Fur Elise and Un Sospiro via button press selection
*  Generate frequency through PWM generation
*
* Abraham Rock
* arock@hmc.edu
* September 30, 2025
*/

int main(void) {
  configureFlash();
  configureClock();

  // enables GPIO port A
  RCC -> AHB2ENR |= (1 << 0);
  RCC -> APB1ENR1 &= ~(1 << 2);

  // enables timers
  RCC -> APB2ENR |= (1 << 16);
  RCC -> APB2ENR |= (1 << 17);

  // sets PA6 to alternating function
  pinMode(6, 2);

  // sets PA5 and PA4 to inputs
  pinMode(4, 0);
  pinMode(5, 0);

  // disconnect the analog switch for PA4 and PA5
   GPIO->ASCR &= ~((1 << 4) | (1 << 5));

  // clear the PURPDR
  GPIO->PURPDR &= ~(0b11 << (4 * 2));
  GPIO->PURPDR &= ~(0b11 << (5 * 2));
    
  // set the PURPDR bits to 1 for PA4 and PA5 to enable pull-ups
  GPIO->PURPDR |=  ((0b01 << (4 * 2)) | (0b01 << (5 * 2)));

  // clear alt function for PA5
  GPIO->AFRL &= ~(0b1111 << (5 * 4));

  // enables AF14 for the GPIO pin PA6
  GPIO->AFRL &= ~(0b1111 << 24);   // clear bits 27:24
  GPIO->AFRL |=  (0b1110 << 24);   // set to AF14

  initTIM(TIM15); // Used for delays
  initPWM(TIM16); // Used for PWM sound generation

  int fe_notes = sizeof(fur_elise) / sizeof(fur_elise[0]);
  int us_notes = sizeof(un_sospiro) / sizeof(un_sospiro[0]);

  while (1) {
    if (digitalRead(5) == 0) {
      for (int i = 0; i < fe_notes; i++) {
        int pitch = fur_elise[i][0];
        int duration = fur_elise[i][1];
        analogWrite(TIM16, pitch, 50);
        delay_ms(TIM15, duration);
      }
      while (digitalRead(5) == 0);
    } else if (digitalRead(4) == 0) {
      for (int i = 0; i < us_notes; i++) {
        int pitch = un_sospiro[i][0];
        int duration = un_sospiro[i][1];
        int dut_cyc = 0;
        if (duration == 31) {
          dut_cyc = 25;
        } else {
          dut_cyc = 75;
        }
        analogWrite(TIM16, pitch, dut_cyc);
        delay_ms(TIM15, duration);
      }
      while (digitalRead(4) == 0);
    }
  }
}
/*************************** End of file ****************************/
