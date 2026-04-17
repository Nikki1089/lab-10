#include "servo.h"
#include "Timer.h"
#include "lcd.h"

int pulse_period  = 320000;
int mid_width = 22000;

void servo_init(){
    SYSCTL_RCGCTIMER_R |= 0x02;   // Timer1
   SYSCTL_RCGCGPIO_R  |= 0x02;   // Port B
     TIMER1_CTL_R &= ~TIMER_CTL_TBEN;
     GPIO_PORTB_AFSEL_R |= 0x20;       
     GPIO_PORTB_PCTL_R &= ~0x00F00000; 
     GPIO_PORTB_PCTL_R |=  0x00700000;  
    GPIO_PORTB_DIR_R   |= 0x20;    
    GPIO_PORTB_DEN_R   |= 0x20;

     TIMER1_TBMR_R &= ~TIMER_TBMR_TBCMR;
     TIMER1_CFG_R |= 0x4;
     TIMER1_TBMR_R |= 0x2;
     TIMER1_TBMR_R |= TIMER_TBMR_TBAMS; 
     TIMER1_TBILR_R = pulse_period & 0xFFFF; 
     TIMER1_TBPR_R = pulse_period >> 16 ;

     TIMER1_TBMATCHR_R = (pulse_period - mid_width ) & 0xFFFF;
     TIMER1_TBPMR_R = (pulse_period - mid_width) >> 16;
     TIMER1_CTL_R |= TIMER_CTL_TBEN; 
}

void servo_move(uint16_t degrees){
   {
     unsigned pulse_width;
     pulse_width = (36000 -7500)*degrees /180.0 + 7500;    // 7500->0 degree    36000->180 degree
     TIMER1_TBMATCHR_R = (pulse_period - pulse_width ) & 0xFFFF;
     TIMER1_TBPMR_R = (pulse_period - pulse_width) >> 16;
     timer_waitMillis(500);
}
}

