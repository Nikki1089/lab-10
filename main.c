#include <inc/tm4c123gh6pm.h>
#include "Timer.h"
#include "servo.h"

int main(void)
{
    timer_init();
    servo_init();

    servo_move(90);
    servo_move(30);
    servo_move(150);
    servo_move(90);

    while (1)
    {
        // Hold position at 90 degrees
    }
}
