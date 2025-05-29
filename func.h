#include "stm32f10x.h"



void init_ADC_7();

uint16_t read_ADCdata();

//_____________________timer________________

void init_GPIOA_open_drain();

void init_GPIOA_AF_pp();

void init_TIM_PWM();

void PWM_set(uint16_t time);

void init_GPIOB();

void init_timer();

void delay_us(int us);

uint8_t read_pin();