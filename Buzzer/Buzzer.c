/*
 * Buzzer.c
 *
 *  Created on: 19.01.2019
 *      Author: Buffo
 */
#include <stddef.h>

/* XDCtools Header files */
#include <xdc/std.h>
#include <xdc/runtime/System.h>

/* BIOS Header files */
#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/knl/Task.h>

#include <ti/drivers/PWM.h>

#include "Config/Board.h"
#include "Buzzer/Buzzer.h"


#define note_cc 261
#define note_dd 294
#define note_ee 329
#define note_ff 349
#define note_g 391
#define note_gS 415
#define note_a 440
#define note_aS 455
#define note_b 466
#define note_cH 523
#define note_cSH 554
#define note_dH 587
#define note_dSH 622
#define note_eH 659
#define note_fH 698
#define note_fSH 740
#define note_gH 784
#define note_gSH 830
#define note_aH 880

static PWM_Handle pwm1;

static uint32_t duty;

void Buzzer_init(void)
{
    PWM_Params params;
    uint16_t   pwmPeriod = 10000; // Period and duty in microseconds

    PWM_Params_init(&params);
    params.period = pwmPeriod;
    pwm1 = PWM_open(Board_PWM0, &params);
    if (pwm1 == NULL)
    {
        System_abort("Board_PWM0 did not open");
    }

    duty = pwmPeriod / 2;
}

void Buzzer_on(void)
{
    // ToDo: check duty cycle? full period does not work
    PWM_setDuty(pwm1, duty);
}

void Buzzer_off(void)
{
    PWM_setDuty(pwm1, 0);
}

void Buzzer_setDuty(uint32_t newDuty)
{
    duty = newDuty;
}

void Buzzer_march(void)
{
    loop();
}

void beep(int note, int duration)
{
  PWM_setDuty(pwm1, note);
  Task_sleep(duration);
//  PWM_setDuty(pwm1, 0);
//  Task_sleep(duration + 20);
}

void loop(void)
{
  beep(note_a, 500);
  beep(note_a, 500);
  beep(note_a, 500);
  beep(note_ff, 350);
  beep(note_cH, 150);
  beep(note_a, 500);
  beep(note_ff, 350);
  beep(note_cH, 150);
  beep(note_a, 650);

  Task_sleep(150);
  //end of first bit

  beep(note_eH, 500);
  beep(note_eH, 500);
  beep(note_eH, 500);
  beep(note_fH, 350);
  beep(note_cH, 150);
  beep(note_gS, 500);
  beep(note_ff, 350);
  beep(note_cH, 150);
  beep(note_a, 650);

  Task_sleep(150);
  //end of second bit...

  beep(note_aH, 500);
  beep(note_a, 300);
  beep(note_a, 150);
  beep(note_aH, 400);
  beep(note_gSH, 200);
  beep(note_gH, 200);
  beep(note_fSH, 125);
  beep(note_fH, 125);
  beep(note_fSH, 250);

  Task_sleep(250);

  beep(note_aS, 250);
  beep(note_dSH, 400);
  beep(note_dH, 200);
  beep(note_cSH, 200);
  beep(note_cH, 125);
  beep(note_b, 125);
  beep(note_cH, 250);

  Task_sleep(250);

  beep(note_ff, 125);
  beep(note_gS, 500);
  beep(note_ff, 375);
  beep(note_a, 125);
  beep(note_cH, 500);
  beep(note_a, 375);
  beep(note_cH, 125);
  beep(note_eH, 650);


  beep(note_aH, 500);
  beep(note_a, 300);
  beep(note_a, 150);
  beep(note_aH, 400);
  beep(note_gSH, 200);
  beep(note_gH, 200);
  beep(note_fSH, 125);
  beep(note_fH, 125);
  beep(note_fSH, 250);

  Task_sleep(250);

  beep(note_aS, 250);
  beep(note_dSH, 400);
  beep(note_dH, 200);
  beep(note_cSH, 200);
  beep(note_cH, 125);
  beep(note_b, 125);
  beep(note_cH, 250);

  Task_sleep(250);

  beep(note_ff, 250);
  beep(note_gS, 500);
  beep(note_ff, 375);
  beep(note_cH, 125);
  beep(note_a, 500);
  beep(note_ff, 375);
  beep(note_cH, 125);
  beep(note_a, 650);
  //end of the song
}

