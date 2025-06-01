#include "stm32f10x.h"
#include "func.h"



void init_usart1(){ //  PA9 PA10
	
	RCC->APB2ENR |= RCC_APB2ENR_USART1EN;
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
	
	GPIOA->CRH &= ~(GPIO_CRH_MODE9 | GPIO_CRH_CNF9);
	GPIOA->CRH |= GPIO_CRH_MODE9;
	GPIOA->CRH |= GPIO_CRH_CNF9_1;
	
	GPIOA->CRH &= ~(GPIO_CRH_MODE10 | GPIO_CRH_CNF10);
	GPIOA->CRH |= GPIO_CRH_CNF10_1;
	GPIOA->BSRR |= GPIO_BSRR_BS10;
	
	USART1->CR1 = USART_CR1_UE;
	
	USART1->BRR = 7500;
	USART1->CR1 |= (USART_CR1_TE | USART_CR1_RE);
	USART1->CR2 = 0;
	USART1->CR3 = 0;
	
	//uint8_t word = 0;
	
};

uint8_t data = 0;

void USART1_TX(uint8_t data){
	
		USART1->DR = data;
	
};


uint8_t USART1_RX (){
	
		data = USART1->DR;
	return data;
};