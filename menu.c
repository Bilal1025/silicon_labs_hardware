/*
 * menu.c
 *
 *  Created on: 15-Nov-2023
 *      Author: bilal
 */


#include "menu.h"

#define MENU_START 7
#define MENU_END 9

static int current_line = 7;
int counter = 0;

MenuItem menu_state[10] = {MENU_CLOSED};
int state_index = 0;
DeviceSetting settings = {true, true, true, 1, {0, 0, 17, 3, 9, 123, 1, 275, -1}, "1.0"};


sl_sleeptimer_timer_handle_t my_sleeptimer_handle;

char *main_menu_items[6] = {"UV", "IR", "Bluetooth", "Date", "Time", "Version"};
int main_menu_index = 0;
int seconds_passed = 0;

bool blink_enabled = false;
int blink_index = 0;

void init_device_menu(void) {
  print_menu();
}

MenuItem currentState() {
  return menu_state[state_index];
}

void menu_driver() {
  if (currentState() != MENU_CLOSED) {
      if (seconds_passed % 2 == 0) {
          print_menu();
      } else {
          if (blink_enabled) {
              print_space(current_line + 1, blink_index);
          }
      }

      seconds_passed++;
      if (seconds_passed >= 10) {
          seconds_passed = 0;
//          state_index = 0;
      }
  }
}

void print_uv_menu() {
  print_content("Set UV:", current_line);
  if (settings.uv_on) {
      print_content("ON", current_line + 1);
  } else {
      print_content("OFF", current_line + 1);
  }
}

void print_ir_menu() {
  print_content("Set IR:", current_line);
    if (settings.ir_on) {
        print_content("ON", current_line + 1);
    } else {
        print_content("OFF", current_line + 1);
    }
}

void print_bt_menu() {
  print_content("Set Bluetooth:", current_line);
    if (settings.bt_on) {
        print_content("ON", current_line + 1);
    } else {
        print_content("OFF", current_line + 1);
    }
}

void print_date_menu() {
  print_content("Set Date:", current_line);
  char isoTime[21];
  strftime(isoTime, sizeof(isoTime), "%Y-%m-%d", &settings.date_time);
  print_content(isoTime, current_line + 1);
}

void print_clock_menu() {
  print_content("Set Time:", current_line);
  char isoTime[21];
  strftime(isoTime, sizeof(isoTime), "%H:%M", &settings.date_time);
  print_content(isoTime, current_line + 1);
}

void print_fw_menu() {
  print_content("Firmware Version:", current_line);
  print_content(settings.firmware_version, current_line + 1);
}

void print_menu() {
  if (currentState() == MENU_CLOSED) {
      print_content("Settings Closed", current_line);
  } else if (currentState() == MENU_MAIN) {
      print_content(main_menu_items[main_menu_index], current_line);
  } else if (currentState() == MENU_UV) {
      print_uv_menu();
  } else if (currentState() == MENU_IR) {
      print_ir_menu();
  } else if (currentState() == MENU_BT) {
      print_bt_menu();
  } else if (currentState() == MENU_DATE) {
      print_date_menu();
  }  else if (currentState() == MENU_CLOCK) {
      print_clock_menu();
  } else if (currentState() == MENU_FW) {
      print_fw_menu();
  }
}

void toggleUV() {
  settings.uv_on = !settings.uv_on;
  print_menu();
}

void toggleIR() {
  settings.ir_on = !settings.ir_on;
  print_menu();
}

void toggleBT() {
  settings.bt_on = !settings.bt_on;
  print_menu();
}

void handleClockDown() {
  if (blink_index == 0) {
        settings.date_time.tm_hour -= 10;
    } else if (blink_index == 1) {
        settings.date_time.tm_hour--;
    } else if (blink_index == 3) {
        settings.date_time.tm_min -= 10;
    } else if (blink_index == 4) {
        settings.date_time.tm_min--;
    }

    if (settings.date_time.tm_hour < 0) {
        settings.date_time.tm_hour = 0;
    }

    if (settings.date_time.tm_min < 0) {
        settings.date_time.tm_min = 0;
    }
}

void handleClockUp() {
  if (blink_index == 0) {
        settings.date_time.tm_hour += 10;
    } else if (blink_index == 1) {
        settings.date_time.tm_hour++;
    } else if (blink_index == 3) {
        settings.date_time.tm_min += 10;
    } else if (blink_index == 4) {
        settings.date_time.tm_min++;
    }

    if (settings.date_time.tm_hour > 23) {
        settings.date_time.tm_hour = 23;
    }

    if (settings.date_time.tm_min > 59) {
        settings.date_time.tm_min = 59;
    }
}

void handleDateDown() {
  if (blink_index == 0) {
        settings.date_time.tm_year -= 1000;
    } else if (blink_index == 1) {
        settings.date_time.tm_year -= 100;
    } else if (blink_index == 2) {
        settings.date_time.tm_year -= 10;
    } else if (blink_index == 3) {
        settings.date_time.tm_year--;
    } else if (blink_index == 5) {
        settings.date_time.tm_mon -= 10;
    } else if (blink_index == 6) {
        settings.date_time.tm_mon--;
    } else if (blink_index == 8) {
        settings.date_time.tm_mday -= 10;
    } else if (blink_index == 9) {
        settings.date_time.tm_mday--;
    }

    if (settings.date_time.tm_year < 0) {
        settings.date_time.tm_year = 0;
    }

    if (settings.date_time.tm_mon < 0) {
        settings.date_time.tm_mon = 0;
    }

    if (settings.date_time.tm_mday < 1) {
        settings.date_time.tm_mday = 1;
    }
}

void handleDateUp() {
  if (blink_index == 0) {
        settings.date_time.tm_year += 1000;
    } else if (blink_index == 1) {
        settings.date_time.tm_year += 100;
    } else if (blink_index == 2) {
        settings.date_time.tm_year += 10;
    } else if (blink_index == 3) {
        settings.date_time.tm_year++;
    } else if (blink_index == 5) {
        settings.date_time.tm_mon += 10;
    } else if (blink_index == 6) {
        settings.date_time.tm_mon++;
    } else if (blink_index == 8) {
        settings.date_time.tm_mday += 10;
    } else if (blink_index == 9) {
        settings.date_time.tm_mday++;
    }

    if ((settings.date_time.tm_year + 1900) > 9999) {
        settings.date_time.tm_year = 9999 - 1900;
    }

    if (settings.date_time.tm_mon > 11) {
        settings.date_time.tm_mon = 11;
    }

    if (settings.date_time.tm_mday > 31) {
        settings.date_time.tm_mday = 31;
    }
}

void handleClock(bool down) {
  if (down) {
      handleClockDown();
  } else {
      handleClockUp();
  }
}

void handleDate(bool down) {
  if (down) {
      handleDateDown();
  } else {
      handleDateUp();
  }
}


void down_pressed() {
  seconds_passed = 0;
  if (currentState() == MENU_MAIN) {
      main_menu_index--;
      if (main_menu_index < 0) {
          main_menu_index = 4;
      }
  } else if (currentState() == MENU_UV) {
      toggleUV();
  } else if (currentState() == MENU_IR) {
      toggleIR();
  } else if (currentState() == MENU_BT) {
      toggleBT();
  } else if (currentState() == MENU_CLOCK) {
      handleClock(true);
  } else if (currentState() == MENU_DATE) {
      handleDate(true);
  }

  print_menu();
}

void up_pressed() {
  seconds_passed = 0;
  if (currentState() == MENU_MAIN) {
      main_menu_index++;
      if (main_menu_index > 4) {
          main_menu_index = 0;
      }
  } else if (currentState() == MENU_UV) {
      toggleUV();
  } else if (currentState() == MENU_IR) {
      toggleIR();
  } else if (currentState() == MENU_BT) {
      toggleBT();
  } else if (currentState() == MENU_CLOCK) {
      handleClock(false);
  } else if (currentState() == MENU_DATE) {
      handleDate(false);
  }

  print_menu();
}

void handleBlinkIndex() {
  if (currentState() == MENU_CLOCK) {
      blink_index++;
      if (blink_index >= 5) {
          blink_index = 0;
      } else if (blink_index == 2) {
          blink_index++;
      }
  } else if (currentState() == MENU_DATE) {
      blink_index++;
      if (blink_index >= 10) {
          blink_index = 0;
      } else if (blink_index == 4) {
          blink_index++;
      } else if (blink_index == 7) {
          blink_index++;
      }
  }
}

void menu_pressed(bool isLongPress) {
  seconds_passed = 0;
  if (isLongPress) {
      if (currentState() == MENU_CLOSED) {
          menu_state[state_index + 1] = MENU_MAIN;
          state_index++;
      } else {
          print_content("", current_line + 1);
          state_index--;
          if (state_index < 0) {
              state_index = 0;
          }
      }
  } else {
      if (currentState() == MENU_MAIN) {
          menu_state[state_index + 1] = main_menu_index + 2;
          blink_index = 0;
          state_index++;

          if (currentState() == MENU_CLOCK || currentState() == MENU_DATE) {
              blink_enabled = true;
          } else {
              blink_enabled = false;
          }
      } else {
          handleBlinkIndex();
      }
  }

//  if (currentState() == MENU_MAIN) {
//      main_menu_index = 0;
//  }
  print_menu();
}

