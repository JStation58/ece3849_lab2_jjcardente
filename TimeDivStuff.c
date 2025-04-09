/*
 * TimeDivStuff.c
 *
 *  Created on: Apr 9, 2025
 *      Author: jason
 */

#include <stdint.h>
#include <stdbool.h>
#include <math.h>
#include "inc/hw_memmap.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/timer.h"
#include "driverlib/interrupt.h"
#include "driverlib/adc.h"
#include "sysctl_pll.h"
#include "buttons.h"
#include "inc/tm4c1294ncpdt.h"

extern uint32_t gSystemClock;
int tscales[11] = {125000, 62500, 25000, 12500, 6250, 2500, 1250, 625, 250, 125, 62}; //FILL IN WITH MAX COUNTS FOR EVERY SETTING LATER


void init_ADC_Timer(void) {
    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER2);
    TimerDisable(TIMER2_BASE, TIMER_BOTH);
    TimerConfigure(TIMER2_BASE, TIMER_CFG_PERIODIC);
    TimerLoadSet(TIMER2_BASE, TIMER_A, tscales[0]);
    TimerControlTrigger(TIMER2_BASE, TIMER_A, true);
    TimerEnable(TIMER2_BASE, TIMER_BOTH);

}

void Time_Scale(volatile int tSet) {

    if (tSet == 11) {
        ADCSequenceConfigure(ADC1_BASE, 0, ADC_TRIGGER_ALWAYS, 0);
    } else {
        ADCSequenceConfigure(ADC1_BASE, 0, ADC_TRIGGER_TIMER, 0);
        TimerDisable(TIMER2_BASE, TIMER_BOTH);
        TimerLoadSet(TIMER2_BASE, TIMER_A, tscales[tSet]); //gSystemClock * tscales[tSet] - 1);
        TimerEnable(TIMER2_BASE, TIMER_BOTH);
    }
    ADCSequenceEnable(ADC1_BASE, 0);

}


//TimerControlTrigger() can be used to set the timer as the trigger for the ADC
