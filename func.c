#include "stm32f10x.h"
#include "func.h"




void init_ADC_17(){
	
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
	GPIOA->CRL &= ~(GPIO_CRL_MODE7 | GPIO_CRL_CNF7);
	RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;
	RCC->CFGR &= ~RCC_CFGR_ADCPRE_0;
	RCC->CFGR |= RCC_CFGR_ADCPRE_1;
	ADC1->CR1 = 0;
	ADC1->CR2 = 0;
	ADC1->CR2 |= ADC_CR2_ADON;
	ADC1->SMPR2 |= (ADC_SMPR2_SMP7_1 | ADC_SMPR2_SMP7_0);
	ADC1->SMPR2 &= ~ADC_SMPR2_SMP7_2;
	ADC1->SQR2 |= (ADC_SQR2_SQ7_0 | ADC_SQR2_SQ7_1 | ADC_SQR2_SQ7_2);
	delay_us(10);
	ADC1->CR2 |= ADC_CR2_CAL;
	while ((ADC1->CR2 & ADC_CR2_CAL) != 0) ;
	ADC1->CR2 |= ADC_CR2_EXTSEL;
	ADC1->CR2 |= ADC_CR2_EXTTRIG;
	ADC1->CR2 &= ~ADC_CR2_ALIGN;
	
};

uint16_t read_ADCdata(){
	
	uint16_t data = 0;
			
	data |= ADC_DR_DATA;
			
	return data;
	
};


//________________timer____________________//

void init_GPIOA_open_drain(){ //PA2
	
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
	GPIOA->CRL &= ~(GPIO_CRL_MODE2 | GPIO_CRL_CNF2);
	GPIOA->CRL |= GPIO_CRL_MODE2_1;
	GPIOA->CRL |= GPIO_CRL_CNF2_0;
	
	GPIOA->BSRR |= GPIO_BSRR_BS2;
	
}

void init_GPIOA_AF_pp(){ //PA1
	
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
	GPIOA->CRL &= ~(GPIO_CRL_CNF1 | GPIO_CRL_MODE1);
	GPIOA->CRL |= GPIO_CRL_CNF1_1;
	GPIOA->CRL |= GPIO_CRL_MODE1_1;
		
}

void init_TIM_PWM(){ //PA1
	
	RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
	TIM2->CR1 &= ~TIM_CR1_CMS;
	TIM2->PSC = 72;
	TIM2->ARR = 3600;
	TIM2->CCR2 = 1800;
	TIM2->CCMR1 |= (TIM_CCMR1_OC2M_1 | TIM_CCMR1_OC2M_2);
	TIM2->CCER |= TIM_CCER_CC2E;
	TIM4->CR1 |= TIM_CR1_URS;
	TIM4->DIER |= TIM_DIER_UIE;
	TIM4->EGR |= TIM_EGR_UG;
	TIM2->CR1|= TIM_CR1_CEN;
	NVIC_EnableIRQ(TIM2_IRQn);

	
	
}

void TIM2_IRQHandler (){
	
		TIM2->SR &= ~TIM_SR_UIF;

	
}


void PWM_set(uint16_t time){
	
	TIM2->CCR2 = time;
	
}

void init_GPIOB(){ //PB2
	
	RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;
	GPIOB->CRL |= GPIO_CRL_MODE2;
	GPIOB->CRL &= ~GPIO_CRL_CNF2;
	
}

void init_GPIOA3(){ //PA3
	
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
	GPIOB->CRL |= GPIO_CRL_MODE3;
	GPIOB->CRL &= ~GPIO_CRL_CNF3;
	
}

void init_GPIOA4(){ //PA4
	
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
	GPIOB->CRL &= ~GPIO_CRL_MODE4;
	GPIOB->CRL |= GPIO_CRL_CNF4_0;
	
}



void init_timer(){
	
	RCC->APB1ENR |= RCC_APB1ENR_TIM4EN;
	TIM4->PSC = 1;
	TIM4->ARR = 72 - 1;
	TIM4->CR1 |= TIM_CR1_URS;
	TIM4->DIER |= TIM_DIER_UIE;
	TIM4->EGR |= TIM_EGR_UG;
	NVIC_EnableIRQ(TIM4_IRQn);

};


int my_ticks = 0;


void TIM4_IRQHandler(){
	
	my_ticks++;
	TIM4->SR &= ~TIM_SR_UIF;
	
};

void delay_us(int us){
	
	TIM4->CR1 |= TIM_CR1_CEN;
	my_ticks = 0;
	while(my_ticks < us);
	TIM4->CR1 &= ~TIM_CR1_CEN;

};

uint32_t cath_delay(uint16_t pin){
	
	TIM4->CR1 |= TIM_CR1_CEN;
	my_ticks = 0;
	while(pin);
	TIM4->CR1 &= ~TIM_CR1_CEN;	
	
	return my_ticks;
};



void GPIOA_read_mod(){
	
	GPIOA->CRL &= ~GPIO_CRL_MODE2;
	//GPIOA->CRL &= ~GPIO_CRL_CNF2;
	//GPIOA->CRL |= GPIO_CRL_CNF2_1;
	
};

uint8_t read_pin() {
	return (GPIOA->IDR & GPIO_IDR_IDR2) >> 0;
}

