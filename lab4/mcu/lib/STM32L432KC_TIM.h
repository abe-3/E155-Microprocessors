// STM32L432KC_TIM.h
// Header for Timer functions

#ifndef STM32L4_TIM_H
#define STM32L4_TIM_H

#include <stdint.h>

///////////////////////////////////////////////////////////////////////////////
// Definitions
///////////////////////////////////////////////////////////////////////////////

#define __IO volatile

// Base addresses
#define TIM15_BASE (0x40014000UL) // base address of TIM15
#define TIM16_BASE (0x40014400UL) // base address of TIM16

/**
  * @brief Reset and Clock Control
  */

typedef struct
{
  __IO uint32_t CR1;         /*!< TIM Control Register 1,                                                  Address offset: 0x00 */
  __IO uint32_t CR2;         /*!< TIM Control Register 2,                                                  Address offset: 0x04 */
  __IO uint32_t SMCR;        /*!< Slave Mode Control Register,                                             Address offset: 0x08 */
  __IO uint32_t DIER;        /*!< DMA / Interrupt Enable Register,                                         Address offset: 0x0C */
  __IO uint32_t SR;          /*!< Status Register,                                                         Address offset: 0x10 */
  __IO uint32_t EGR;         /*!< Event Generation Register,                                               Address offset: 0x14 */
  __IO uint32_t CCMR1_OUT;   /*!< Capture / Compare Mode Register 1 Output,                                Address offset: 0x18 */
  __IO uint32_t CCMR1_IN;    /*!< Capture / Compare Mode Register 1 Input,                                 Address offset: 0x1C */
  __IO uint32_t CCER;        /*!< Capture / Compare Enable Register,                                       Address offset: 0x20 */
  __IO uint32_t CNT;         /*!< Counter,                                                                 Address offset: 0x24 */
  __IO uint32_t PSC;         /*!< Prescaler,                                                               Address offset: 0x28 */
  __IO uint32_t ARR;         /*!< Auto-Reload Register,                                                    Address offset: 0x2C */
  __IO uint32_t RCR;         /*!< Repetition Counter Register,                                             Address offset: 0x30 */
  __IO uint32_t CCR1;        /*!< Capture / Compare Register 1,                                            Address offset: 0x34 */
  __IO uint32_t CCR2;        /*!< Capture / Compare Register 2,                                            Address offset: 0x38 */
  uint32_t ReservedOne;      /*!<                                                                          Address offset: 0x3C */
  uint32_t ReservedTwo;      /*!<                                                                          Address offset: 0x40 */
  __IO uint32_t BDTR;        /*!< Break and Dead Time Register,                                            Address offset: 0x44 */
  __IO uint32_t DCR;         /*!< DMA Control Register,                                                    Address offset: 0x48 */
  __IO uint32_t DMAR;        /*!< DMA Address for Full Transfer Register,                                  Address offset: 0x4C */
  __IO uint32_t OR1;         /*!< Option Register 1,                                                       Address offset: 0x50 */
  uint32_t ReservedThree;    /*!<                                                                          Address offset: 0x54 */
  uint32_t ReservedFour;     /*!<                                                                          Address offset: 0x58 */
  uint32_t ReservedFive;     /*!<                                                                          Address offset: 0x5C */
  __IO uint32_t OR2;         /*!< Option Register 2,                                                       Address offset: 0x60 */
} TIM15_TypeDef;

typedef struct
{
  __IO uint32_t CR1;         /*!< TIM Control Register 1,                                                  Address offset: 0x00 */
  __IO uint32_t CR2;         /*!< TIM Control Register 2,                                                  Address offset: 0x04 */
  uint32_t ReservedOne;      /*!<                                                                          Address offset: 0x08 */
  __IO uint32_t DIER;        /*!< DMA / Interrupt Enable Register,                                         Address offset: 0x0C */
  __IO uint32_t SR;          /*!< Status Register,                                                         Address offset: 0x10 */
  __IO uint32_t EGR;         /*!< Event Generation Register,                                               Address offset: 0x14 */
  __IO uint32_t CCMR1_OUT;   /*!< Capture / Compare Mode Register 1 Output,                                Address offset: 0x18 */
  __IO uint32_t CCMR1_IN;    /*!< Capture / Compare Mode Register 1 Input,                                 Address offset: 0x1C */
  __IO uint32_t CCER;        /*!< Capture / Compare Enable Register,                                       Address offset: 0x20 */
  __IO uint32_t CNT;         /*!< Counter,                                                                 Address offset: 0x24 */
  __IO uint32_t PSC;         /*!< Prescaler,                                                               Address offset: 0x28 */
  __IO uint32_t ARR;         /*!< Auto-Reload Register,                                                    Address offset: 0x2C */
  __IO uint32_t RCR;         /*!< Repetition Counter Register,                                             Address offset: 0x30 */
  __IO uint32_t CCR1;        /*!< Capture / Compare Register 1,                                            Address offset: 0x34 */
  uint32_t ReservedTwo;      /*!<                                                                          Address offset: 0x38 */
  uint32_t ReservedThree;    /*!<                                                                          Address offset: 0x3C */
  uint32_t ReservedFour;     /*!<                                                                          Address offset: 0x40 */
  __IO uint32_t BDTR;        /*!< Break and Dead Time Register,                                            Address offset: 0x44 */
  __IO uint32_t DCR;         /*!< DMA Control Register,                                                    Address offset: 0x48 */
  __IO uint32_t DMAR;        /*!< DMA Address for Full Transfer Register,                                  Address offset: 0x4C */
  __IO uint32_t OR1;         /*!< Option Register 1,                                                       Address offset: 0x50 */
  uint32_t ReservedFive;     /*!<                                                                          Address offset: 0x54 */
  uint32_t ReservedSix;      /*!<                                                                          Address offset: 0x58 */
  uint32_t ReservedSeven;    /*!<                                                                          Address offset: 0x5C */
  __IO uint32_t OR2;         /*!< Option Register 2,                                                       Address offset: 0x60 */
} TIM16_TypeDef;

#define TIM15 ((TIM15_TypeDef *) TIM15_BASE)
#define TIM16 ((TIM16_TypeDef *) TIM16_BASE)

///////////////////////////////////////////////////////////////////////////////
// Function prototypes
///////////////////////////////////////////////////////////////////////////////

void initTIM(TIM15_TypeDef *TIMx);
void delay_ms(TIM15_TypeDef *TIMx, uint32_t ms);

void initPWM(TIM16_TypeDef *TIMx);
void analogWrite(TIM16_TypeDef *TIMx, uint32_t freq, uint32_t duty_cycle_percentage);
#endif