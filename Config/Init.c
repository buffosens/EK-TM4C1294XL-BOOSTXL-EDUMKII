/*
 * Init.c
 *
 *  Created on: 19.01.2019
 *      Author: Buffo
 */


/* Board Header file */
#include "Config/Board.h"

#include "Buzzer/Buzzer.h"

#include "Init.h"

void Init_Edu(void)
{
    /* Call board init functions */
    Board_initGeneral();
    // Board_initEMAC();
    Board_initGPIO();
    // Board_initI2C();
    // Board_initSDSPI();
    Board_initSPI();
    // Board_initUART();
    // Board_initUSB(Board_USBDEVICE);
    // Board_initUSBMSCHFatFs();
    // Board_initWatchdog();
    // Board_initWiFi();
    Board_initPWM();
    Board_initADC();

    Buzzer_init();
}

