#include "stm32f10x.h"
#include "func.h"
#include "ds18b20.h"



int main() {
	
	init_GPIOA_AF_pp();
	init_GPIOA_open_drain();
	init_GPIOB();
	init_TIM_PWM();
	init_timer();
	reset_ds();
	
	uint16_t temp = 0;
	
	while(1){
		
		Skip_ROM();
		comp_start();
		reset_ds();
		Skip_ROM();
		temp = read_temp_dat();
		reset_ds();
		//float time;
		
		/*if (temp < 28)
			time = 0;
		else
			if (temp > 38)
				time = 1000;
			else*/
			/*	time = (temp-28)*100;
			TIM2->CCR2 = (time);*/
		

		TIM2->PSC = (72000*(36-temp));

		
	}
	
}