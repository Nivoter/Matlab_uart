#include <ch.h>
#include <hal.h>
#include <chprintf.h>

static THD_WORKING_AREA(waBlinker1,128);
static THD_FUNCTION(Blinker1,arg)
{
    (void)arg;
    while(true)
    {
        palToggleLine(LINE_LED1);
        chThdSleepMilliseconds(100);
    }
}

static THD_WORKING_AREA(waBlinker2,128);
static THD_FUNCTION(Blinker2,arg)
{
    (void)arg;
    while(true)
    {
        palToggleLine(LINE_LED2);
        chThdSleepMilliseconds(200);
    }
}

static THD_WORKING_AREA(waBlinker3,128);
static THD_FUNCTION(Blinker3,arg)
{
    (void)arg;
    while(true)
    {
        palToggleLine(LINE_LED3);
        chThdSleepMilliseconds(300);
    }
}

int main(void)
{

    chSysInit();    //#
    halInit(); //#
    chThdCreateStatic(waBlinker1, sizeof(waBlinker1), NORMALPRIO, Blinker1, NULL);
    chThdCreateStatic(waBlinker2, sizeof(waBlinker2), NORMALPRIO - 1, Blinker2, NULL);
    chThdCreateStatic(waBlinker3, sizeof(waBlinker3), NORMALPRIO - 2, Blinker3, NULL);
    while ( 1 )
    {

            chThdSleepMilliseconds(500);

    }
}
