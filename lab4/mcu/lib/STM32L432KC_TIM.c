// STM32L432KC_TIM.c
// Source code for Timer functions

#include <math.h>
#include "STM32L432KC_RCC.h"
#include "STM32L432KC_TIM.h"

#define PSC_Val_Delay 2500
#define PSC_Val_PWM 16

#define MCU_CLK 80000000.0
#define MAX_TIMER 0xFFFF

void initTIM(TIM15_TypeDef *TIMx) {
    // Enable Clock for Timers
    RCC->APB2ENR |= (1 << 16); // TIM15EN Bit

    // f_clk / (PSC + 1)
    // 80 MHz / 2500 = 32000 Hz (Right above max human hearing)
    TIMx->PSC = PSC_Val_Delay - 1;

    // Max out Auto-Reload
    TIMx->ARR = 0xFFFF;

    // Update Generation
    TIMx->EGR |= (1 << 0);

    // Counter Enable
    TIMx->CR1 |= (1 << 0);
}

void delay_ms(TIM15_TypeDef *TIMx, uint32_t ms){
     // Cycle period is _ us
     // convert to ms
    uint32_t clk_speed = MCU_CLK / (PSC_Val_Delay + 1);  // In Hz
    uint32_t desired_cycles = (clk_speed * ms) / 1000;

    // Ensures ARR doesn't overflow over 16 bits
    TIMx->ARR = (desired_cycles > MAX_TIMER) ? MAX_TIMER : desired_cycles;

    // Reset Update Interrupt Flag (UIF)
    TIMx->SR &= ~(1 << 0);

    // Reset Counter
    TIMx->CNT = 0;

    // when UIF bit is 1, ARR max value has been reached, so stop
    while ((TIMx->SR & 1) == 0);
}



void initPWM(TIM16_TypeDef *TIMx) {
  // Enable Clock for Timers
  RCC->APB2ENR |= (1 << 17); // TIM16EN Bit
  
  // Output Compare Mode 1 to PWM mode (110)
  TIMx->CCMR1_OUT = (0b110 << 4);

  // pwm set as active high
  TIMx->CCER &= ~(1 << 1);

  // CCER Enabled with 1
  TIMx->CCER |= (1 << 0);

  // Output Enabled (MOE)
  TIMx->BDTR |= (1 << 15);

  // enable update generation
  TIMx->EGR |= (1 << 0);

  // enabling clock
  TIMx->CR1 |= (1 << 0);
}


void analogWrite(TIM16_TypeDef *TIMx, uint32_t freq, uint32_t duty_cycle_percentage) {
  // Ensures realistic values
  if (duty_cycle_percentage > 100) {
    duty_cycle_percentage = 100;
  }
  if (freq == 0) {
    TIMx->CCR1 = 0;
    return;
  }

  uint32_t arr_val = 0;
  uint32_t psc_val = 0;

  // Calculate the ratio difference between starting and desired
  float freq_difference = MCU_CLK / freq;
  
  

  // ARR = clk_freq / note_freq
  if (freq_difference <= (MAX_TIMER + 1.0)) {
    psc_val = 0; //maximum resolution
    arr_val = (uint32_t)round(freq_difference) - 1;
  } else {
    psc_val = (uint32_t)ceil(freq_difference / (MAX_TIMER + 1.0)) - 1;

    // With the optimal PSC found, calculate the corresponding ARR value.
    float arr_plus_1 = freq_difference / (psc_val + 1.0);
    arr_val = (uint32_t)round(arr_plus_1) - 1;
  }

  TIMx->PSC = psc_val;
  TIMx->ARR = arr_val;

  // CCR1 = (ARR+1) * duty_cycle / 100
  TIMx->CCR1 = ((arr_val + 1) * duty_cycle_percentage) / 100;

  // Update Generation to use new PSC and ARR values
  TIMx->EGR |= (1 << 0);

  // Reset Counter
  TIMx->CNT = 0;
}
