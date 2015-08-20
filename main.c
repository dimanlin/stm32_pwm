#include "stm32f10x.h"

unsigned short int per = 500;
int up_dw = 1;

int main() {
  RCC->APB2ENR |= (RCC_APB2ENR_IOPAEN | RCC_APB2ENR_AFIOEN);
	
	GPIOA->CRL |= GPIO_CRL_MODE0;
  GPIOA->CRL &= ~GPIO_CRL_CNF0;
  GPIOA->CRL |= GPIO_CRL_CNF0_1;
	
  GPIOA->CRL |= GPIO_CRL_MODE1;
  GPIOA->CRL &= ~GPIO_CRL_CNF1;
  GPIOA->CRL |= GPIO_CRL_CNF1_1;

  RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
	
	TIM2->CCMR1 |= (TIM_CCMR1_OC2M_2 | TIM_CCMR1_OC2M_1); //OC2M = 110 - PWM mode 1
	TIM2->CCMR1 |= (TIM_CCMR1_OC1M_2 | TIM_CCMR1_OC1M_1);  // 110 - PWM mode 1
	TIM2->CCER |= TIM_CCER_CC1E;
	TIM2->CCER |= TIM_CCER_CC2E;
	
  TIM2->ARR = 1000 - 1;
  TIM2->CCR2 = 100;
	TIM2->CCR1 = 400;
	TIM2->DIER |= TIM_DIER_UIE;
	NVIC_EnableIRQ(TIM2_IRQn);
	TIM2->CR1 |= TIM_CR1_CMS_1;
  TIM2->CR1 |= TIM_CR1_CEN;

  while(1);
}

void TIM2_IRQHandler() 
{
	TIM2->SR&=~TIM_SR_UIF;
}
