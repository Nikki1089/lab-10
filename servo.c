#include "servo.h"
#include "Timer.h"
#include "lcd.h"

int RIGHT = 7500; 
int LEFT = 35000;

void servo_init(){
    SYSCTL_RCGCTIMER_R |= 0x2;
    SYSCTL_RCGCGPIO_R |= 0x2;
    while((SYSCTL_PRGPIO_R & 0x2) != 0x2){}
    GPIO_PORTB_DEN_R |= 0x20;
    GPIO_PORTB_DIR_R |= 0x20;
    GPIO_PORTB_AFSEL_R |= 0x20;
    GPIO_PORTB_PCTL_R |= 0x700000;
    TIMER1_CTL_R &= ~0x100;
    TIMER1_CFG_R |= 0x4;
    TIMER1_TBMR_R &= ~0x4;
    TIMER1_TBMR_R |= 0b1010;
    TIMER1_TBILR_R = 0xE200;
    TIMER1_TBPMR_R = 0x04;
    TIMER1_TBMATCHR_R = 0xC4B4;
    TIMER1_CTL_R |= 0x100;
}

void servo_move(uint16_t degrees){
    int cycles = (((LEFT - RIGHT) / 180) * degrees) + RIGHT;
    int match = 320000 - cycles;


    TIMER1_TBPMR_R = (match >> 16) & 0xFF;
    TIMER1_TBMATCHR_R = (match & 0xFFFF);
}

