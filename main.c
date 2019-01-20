
/* XDCtools Header files */
#include <xdc/std.h>
#include <xdc/runtime/System.h>

/* BIOS Header files */
#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/knl/Task.h>

/* TI-RTOS Header files */
// #include <ti/drivers/EMAC.h>
#include <ti/drivers/GPIO.h>
// #include <ti/drivers/I2C.h>
// #include <ti/drivers/SDSPI.h>
#include <ti/drivers/SPI.h>
#include <inc/hw_memmap.h>

#include "driverlib/adc.h"

// #include <ti/drivers/UART.h>
// #include <ti/drivers/USBMSCHFatFs.h>
// #include <ti/drivers/Watchdog.h>
// #include <ti/drivers/WiFi.h>

#include "Buzzer/Buzzer.h"

/* Board Header file */
#include "Config/Board.h"
#include "Config/Init.h"

#define TASKSTACKSIZE   512

Task_Struct task0Struct;
Char task0Stack[TASKSTACKSIZE];

#define SPI_MSG_LENGTH    26

unsigned char masterRxBuffer[SPI_MSG_LENGTH];
unsigned char masterTxBuffer[SPI_MSG_LENGTH] = "Hello, this is master SPI";

/* variable to be read by GUI Composer */
int count = 0;

/*
 *  ======== gpioButtonFxn0 ========
 *  Callback function for the GPIO interrupt on Board_BUTTON0.
 */
void gpioButtonFxn0(unsigned int index)
{
    /* Clear the GPIO interrupt and toggle an LED */
    GPIO_toggle(Board_LED0);

    //    Buzzer_on();

    if (count++ == 100) {
        count = 0;
    }
}

/*
 *  ======== gpioButtonFxn1 ========
 *  Callback function for the GPIO interrupt on Board_BUTTON1.
 *  This may not be used for all boards.
 */
void gpioButtonFxn1(unsigned int index)
{
    /* Clear the GPIO interrupt and toggle an LED */
    GPIO_toggle(Board_LED1);

    //    Buzzer_off();

    if (count++ == 100) {
        count = 0;
    }
}

/*
 *  ======== heartBeatFxn ========
 *  Toggle the Board_LED0. The Task_sleep is determined by arg0 which
 *  is configured for the heartBeat Task instance.
 */
Void heartBeatFxn(UArg arg0, UArg arg1)
{
    //    SPI_Handle masterSpi;
    //    SPI_Transaction masterTransaction;
    //    bool transferOK;
    //
    //    /* Initialize SPI handle as default master */
    //    masterSpi = SPI_open(Board_SPI0, NULL);
    //    if (masterSpi == NULL) {
    //        System_abort("Error initializing SPI\n");
    //    }
    //    else {
    //        System_printf("SPI initialized\n");
    //    }
    //
    //    /* Initialize master SPI transaction structure */
    //    masterTransaction.count = SPI_MSG_LENGTH;
    //    masterTransaction.txBuf = (Ptr)masterTxBuffer;
    //    masterTransaction.rxBuf = (Ptr)masterRxBuffer;
    //
    //    /* Initiate SPI transfer */
    //    transferOK = SPI_transfer(masterSpi, &masterTransaction);

    //    Buzzer_march();
    uint32_t pui32ADC0Value[2];

    while (1)
    {
        //
        // Trigger the ADC conversion.
        //
        ADCProcessorTrigger(ADC0_BASE, 0);

        //
        // Wait for conversion to be completed.
        //
        while(!ADCIntStatus(ADC0_BASE, 0, false))
        {
        }

        //
        // Clear the ADC interrupt flag.
        //
        ADCIntClear(ADC0_BASE, 0);

        //
        // Read ADC Value.
        //
        ADCSequenceDataGet(ADC0_BASE, 0, pui32ADC0Value);

        System_printf("ADC: %u - %u\r\n", pui32ADC0Value[0], pui32ADC0Value[1]);
        System_flush();

        Task_sleep(200);
    }
}

/*
 *  ======== main ========
 */
int main(void)
{
    Init_Edu();

    Task_Params taskParams;
    /* Construct heartBeat Task  thread */
    Task_Params_init(&taskParams);
    taskParams.arg0 = 1000;
    taskParams.stackSize = TASKSTACKSIZE;
    taskParams.stack = &task0Stack;
    Task_construct(&task0Struct, (Task_FuncPtr)heartBeatFxn, &taskParams, NULL);

    //     /* Turn on user LED */
    //    GPIO_write(Board_LED0, Board_LED_ON);
    //
    //    System_printf("Starting the example\nSystem provider is set to SysMin. "
    //                  "Halt the target to view any SysMin contents in ROV.\n");
    //    /* SysMin will only print to the console when you call flush or exit */
    //    System_flush();
    //
    //    /* install Button callback */
    //    GPIO_setCallback(EDU_BUTTON_1, gpioButtonFxn0);
    //
    //    /* Enable interrupts */
    //    GPIO_enableInt(EDU_BUTTON_1);
    //
    //    /*
    //     *  If more than one input pin is available for your device, interrupts
    //     *  will be enabled on Board_BUTTON1.
    //     */
    //    if (EDU_BUTTON_1 != EDU_BUTTON_2)
    //    {
    //        /* install Button callback */
    //        GPIO_setCallback(EDU_BUTTON_2, gpioButtonFxn1);
    //        GPIO_enableInt(EDU_BUTTON_2);
    //    }

    /* Start BIOS */
    BIOS_start();

    return (0);
}
