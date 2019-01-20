/*
 * Buzzer.h
 *
 *  Created on: 19.01.2019
 *      Author: Buffo
 */

#ifndef BUZZER_BUZZER_H_
#define BUZZER_BUZZER_H_

#include <stdint.h>

void Buzzer_init(void);

void Buzzer_on(void);

void Buzzer_off(void);

void Buzzer_setDuty(uint32_t newDuty);

void Buzzer_march(void);

void loop(void);

#endif /* BUZZER_BUZZER_H_ */
