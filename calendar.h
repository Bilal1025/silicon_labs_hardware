/*
 * calendar.h
 *
 *  Created on: 15-Nov-2023
 *      Author: bilal
 */

#ifndef CALENDAR_H_
#define CALENDAR_H_

#include "app_assert.h"
#include "em_common.h"
#include "display.h"
#include "time.h"
#include "em_rtcc.h"
#include "em_cmu.h"

void init_calendar(void);
void calendar_driver(void);
char* get_time(void);
void print_time(void);
void read_time(void);
void update_calendar(int seconds);
void set_time(struct tm time_info);

#endif /* CALENDAR_H_ */
