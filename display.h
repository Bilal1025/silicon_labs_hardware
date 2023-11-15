/*
 * display.h
 *
 *  Created on: 15-Nov-2023
 *      Author: bilal
 */

#ifndef DISPLAY_H_
#define DISPLAY_H_

#include "glib.h"
#include "app_assert.h"
#include "em_common.h"

void print_content(char * content, int line);
void memlcd_init(void);
void print_space(int current_line, int blink_index);

#endif /* DISPLAY_H_ */
