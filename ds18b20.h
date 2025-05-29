#include "stm32f10x.h"

uint8_t reset_ds();

void comp_start();

void Skip_ROM();

void read_temp();

uint8_t read_bit();

void write_byte(uint8_t byte);

void write_bit(uint8_t bit);

uint16_t read_2byte();

uint8_t read_byte();

float read_temp_dat();

void set0();
	
void set1();
