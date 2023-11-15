/*
 * menu.h
 *
 *  Created on: 15-Nov-2023
 *      Author: bilal
 */

#ifndef MENU_H_
#define MENU_H_

#include "em_common.h"
#include "glib.h"
#include "dmd.h"
#include "sl_sleeptimer.h"
#include "time.h"

// Define menu item constants
typedef enum {
    MENU_CLOSED,
    MENU_MAIN,
    MENU_UV,
    MENU_IR,
    MENU_BT,
    MENU_DATE,
    MENU_CLOCK,
    MENU_FW,
} MenuItem;

// Define menu state structure
typedef struct {
    bool uv_on;
    bool ir_on;
    bool bt_on;
    uint8_t brightness; // For Auto, Night, Day modes
    struct tm date_time;
    char firmware_version[20];
} DeviceSetting;

// Function prototypes
void init_device_menu();
void menu_driver();
void print_menu();
void menu_driver();
void down_pressed();
void up_pressed();
void menu_pressed(bool isLongPress);
void print_data(char *content, int line);

#endif /* MENU_H_ */
