#include "servo.h"
#include "Timer.h"
#include "lcd.h"

int RIGHT = 8000; // 320000;
int LEFT = 32000; // 1280000;

void servo_init()
{
    SYSCTL_RCGCTIMER_R |= 0x2;
    SYSCTL_RCGCGPIO_R |= 0x2;
    while ((SYSCTL_PRTIMER_R & 0x2) != 0x2)
    {
    }
    while ((SYSCTL_PRGPIO_R & 0x2) != 0x2)
    {
    }
    GPIO_PORTB_DEN_R |= 0x20;
    GPIO_PORTB_DIR_R |= 0x20;
    GPIO_PORTB_AFSEL_R |= 0x20;
    GPIO_PORTB_PCTL_R |= 0x700000;

    // Configure timer for PWM Mode
    TIMER1_CTL_R &= ~0x100;
    TIMER1_CFG_R |= 0x4;
    TIMER1_TBMR_R &= ~0x4; // Timer B Mode Register
    TIMER1_TBMR_R |= 0b1010;
//    TIMER1_TBPR_R = 0x04;
    TIMER1_TBILR_R = PWM_PERIOD_TSTEPS & 0xffff; //0xE200; // Timer B Interval Load
    TIMER1_TBPR_R = (PWM_PERIOD_TSTEPS >> 16) & 0xff; //0x04;
    TIMER1_TBMATCHR_R = 0xC4B4; // Timer B Match Register
    TIMER1_CTL_R |= 0x100;
}

void servo_move(uint16_t degrees)
{
    // 5ms per degree
//    TIMER1_CTL_R &= ~0x100;
//    int cycles = (((LEFT - RIGHT) / 180) * degrees) + RIGHT;
//    int match = PWM_PERIOD_TSTEPS - cycles;
    pulse_width = RIGHT + ((LEFT - RIGHT) * degrees) / 180;
    match = PWM_PERIOD_TSTEPS - pulse_width;
    TIMER1_TBMATCHR_R = match & 0xffff; // &= ~0x110000
    TIMER1_TBPMR_R = (match >> 16) & 0xff;
//    for (i = 0; i < 5 * degrees; ++i) {
//        lcd_printf("%d", TIMER1_TBMATCHR_R);
//    }
//    timer_waitMillis(5 * degrees);
//    TIMER1_TBMATCHR_R = TIMER1_TBPMR_R = 0;
//    TIMER1_CTL_R |= 0x100;

}
