#include "servo.h"
#include "Timer.h"

static int RIGHT = 7500;
static int LEFT  = 36000;

void servo_init(void)
{

    SYSCTL_RCGCTIMER_R |= 0x02;
    SYSCTL_RCGCGPIO_R  |= 0x02;

    while ((SYSCTL_PRGPIO_R & 0x02) == 0) {}
    while ((SYSCTL_PRTIMER_R & 0x02) == 0) {}

    GPIO_PORTB_DEN_R   |= 0x20;
    GPIO_PORTB_DIR_R   |= 0x20;
    GPIO_PORTB_AFSEL_R |= 0x20;
    GPIO_PORTB_PCTL_R &= ~0x00F00000;
    GPIO_PORTB_PCTL_R |=  0x00700000;
    TIMER1_CTL_R &= ~0x0100;
    TIMER1_CFG_R = 0x04;
    TIMER1_TBMR_R &= ~0x3;   
    TIMER1_TBMR_R |= 0x0A;  
    TIMER1_TBPR_R   = 0x04;
    TIMER1_TBILR_R  = 0xE200;
    servo_move(90);

    TIMER1_CTL_R |= 0x0100;
}

void servo_move(uint16_t degrees)
{
    if (degrees > 180)
    {
        degrees = 180;
    }


    int pulse_width = RIGHT + ((LEFT - RIGHT) * degrees) / 180;

    int match = 320000 - pulse_width;

    TIMER1_TBPMR_R    = (match >> 16) & 0xFF;
    TIMER1_TBMATCHR_R = match & 0xFFFF;

    timer_waitMillis(500);
}
