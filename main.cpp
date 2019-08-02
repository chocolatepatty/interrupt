/* mbed Microcontroller Library
 * Copyright (c) 2018 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"
#include "stats_report.h"

DigitalOut led1(LED1);
InterruptIn button(BUTTON1);

#define SLEEP_TIME                  250 // (msec)
#define PRINT_AFTER_N_LOOPS         20

bool alive = 1;

void flip() {
    alive = !alive;
};

// main() runs in its own thread in the OS
int main()
{
    SystemReport sys_state( SLEEP_TIME * PRINT_AFTER_N_LOOPS /* Loop delay time in ms */);

    int count = 0;
    while (true) {
        button.rise(flip);
        while (alive) {
            // Blink LED and wait 0.5 seconds
            led1 = !led1;
            wait_ms(SLEEP_TIME);

            if ((0 == count) || (PRINT_AFTER_N_LOOPS == count)) {
                // Following the main thread wait, report on the current system status
                sys_state.report_state();
                count = 0;
            }
            ++count;
        }
    }
}
