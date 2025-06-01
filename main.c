#include "stm32f10x.h"
#include "func.h"
#include "ds18b20.h"
#include "usart.h"
#include "HC-SR04.h"

		
//TIM2->CCR2 = (time);
//TIM2->PSC = (2000*(36-temp));

//	init_usart1();
//	while (1)
//  {

//		while ((USART1->SR & USART_SR_RXNE) == 0) {}
//		uint8_t d = USART1->DR;
//		
//			
//			
//		while ((USART1->SR & USART_SR_TXE) == 0) {}
//		USART1->DR = (d - 1);
//  }


int main(){

	init_GPIOA4();
	init_GPIOA3();
	while(1){
		trig();
		while(!(GPIOA->IDR & GPIO_IDR_IDR4));
		uint32_t time = echo((GPIOA->IDR & GPIO_IDR_IDR4) != 0);
		uint32_t length = time/54;
		delay_us(60000);
	};
};



