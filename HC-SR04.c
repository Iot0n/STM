#include "stm32f10x.h"
#include "func.h"


void trig(){ //PA3
	
	GPIOA->BSRR = GPIO_BSRR_BS3;
	delay_us(10);
	GPIOA->BSRR = GPIO_BSRR_BR3;
	
};

uint32_t echo(uint8_t pin){
	
	return cath_delay(pin);
};