#include "stm32f10x.h"
#include "func.h"


void set0(){
	
	GPIOA->BSRR = GPIO_BSRR_BR2;
	
};


void set1(){
	
	GPIOA->BSRR = GPIO_BSRR_BS2;
	
};


uint8_t reset_ds(){
	int connect;
	set0();
	delay_us(480);
	set1();
	delay_us(80);
	connect = ~read_pin();
	delay_us(400);
	set1();
return connect;
};



void write_bit(uint8_t bit){
	
	if (bit){
		set0();
		delay_us(5);
		set1();
		delay_us(55);
	}
	else{
		set0();
		delay_us(60);
		set1();
	}
	delay_us(1);
};

uint8_t read_bit(){
	
	uint8_t bit = 0;
    set0();
    delay_us(1);
    set1();
    delay_us(14);
    bit = read_pin();
    delay_us(45);
    return bit;
	
}


void write_byte(uint8_t byte){
    for (uint8_t i = 0; i < 8; i++) {
        write_bit(byte & 0x01);
        byte >>= 1;
    }
}

void comp_start(){
	
	write_byte(0x44);
	delay_us(750000);
	
};

void Skip_ROM(){
	
		write_byte(0xCC);

};

void read_temp(){
	
	write_byte(0xBE);
	
};

uint8_t read_byte() {
    uint8_t byte = 0;
    for (uint8_t i = 0; i < 8; i++) {
        byte >>= 1;
        if (read_bit()) byte |= 0x80;
    }
    return byte;
}

uint16_t read_2byte(){
	reset_ds();
	write_byte(0xCC);
	write_byte(0xBE);
	uint16_t temp=0;
	//uint16_t dw = 1;
	for (uint8_t i = 0; i < 12; i++){
		temp >>=1;
		if (read_bit()){
		temp |= 0x800;
		};
		}
	temp>>=5;
	return temp;
};

float read_temp_dat() {
    uint8_t temp_lsb, temp_msb;
    int16_t temp_raw;
    
    //reset_ds();
    //write_byte(0xCC);  // Skip ROM
    write_byte(0xBE);  // Read Scratchpad
    
    temp_lsb = read_byte();
    temp_msb = read_byte();
    
    temp_raw = (temp_msb << 8) | temp_lsb;
    return (temp_raw >> 4);
}

