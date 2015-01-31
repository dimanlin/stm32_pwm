#include "stm32f10x.h"

int main() {
  RCC->APB2ENR |= (RCC_APB2ENR_IOPAEN | RCC_APB2ENR_AFIOEN);
  GPIOA->CRL |= GPIO_CRL_MODE1;
  GPIOA->CRL &= ~GPIO_CRL_CNF1;
  GPIOA->CRL |= GPIO_CRL_CNF1_1;

  RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;

  TIM2->CCMR1 |= (TIM_CCMR1_OC2M_2 | TIM_CCMR1_OC2M_1);//OC2M = 110 - PWM mode 1
	TIM2->CCER |= TIM_CCER_CC2E;
  TIM2->ARR = 1000 - 1;
  TIM2->CCR2 = 500;
  TIM2->CR1 |= TIM_CR1_CEN;

  while(1);
}