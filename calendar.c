/*
 * calendar.c
 *
 *  Created on: 15-Nov-2023
 *      Author: bilal
 */


#include "calendar.h"

static struct tm current_time = { 0 };
uint32_t last_counter;
bool timer_changed = false;

void init_calendar(void) {
    CMU_ClockEnable(cmuClock_RTCC, true);

    // RTCC initialization structure
    RTCC_Init_TypeDef init = RTCC_INIT_DEFAULT;

    // Set clock source and prescaler
    init.enable = true;
    init.debugRun = false;
    init.presc = rtccCntPresc_32768;
    init.prescMode = rtccCntTickPresc;

    // Initialize the RTCC
    RTCC_Init( & init);
    read_time();

//    RTCC_CCChConf_TypeDef compare = RTCC_CH_INIT_COMPARE_DEFAULT;
//    compare.compMatchOutAction = rtccCompMatchOutActionPulse;
    // Enable RTCC interrupt
    // Initialise RTCC compare with a date, the date when interrupt will occur
//    RTCC_ChannelInit(1, &compare);
//    RTCC_ChannelCCVSet(1, 1);
//
//
//    // Set channel 1 to cause an interrupt
//    RTCC_IntEnable(RTCC_IEN_CC1);
//    NVIC_ClearPendingIRQ(RTCC_IRQn);
//    NVIC_EnableIRQ(RTCC_IRQn);
//    RTCC_Enable(true);
}

void calendar_driver(void) {
  uint32_t counter = RTCC_CounterGet();
  if (counter != last_counter) {
      uint32_t diff = counter - last_counter;
      if (counter < last_counter) {
          diff = counter + 4294967295 - last_counter;
      }
      update_calendar(diff);
      last_counter = counter;
      timer_changed = true;
  }
}

char* get_time(void) {
  char isoTime[21];
  strftime(isoTime, sizeof(isoTime), "%Y-%m-%d %H:%M:%S", &current_time);
  return isoTime;
}

void print_time(void) {
  if (timer_changed) {
    char isoTime[21];
    strftime(isoTime, sizeof(isoTime), "%Y-%m-%d %H:%M:%S", &current_time);
    print_content(isoTime, 11);
  }
}

void update_calendar(int seconds) {
  current_time.tm_sec += seconds;
  if (current_time.tm_sec >= 60) {
      current_time.tm_min += current_time.tm_sec / 60;
      current_time.tm_sec %= 60;
  }
  if (current_time.tm_min >= 60) {
      current_time.tm_hour += current_time.tm_min / 60;
      current_time.tm_min %= 60;
  }
  if (current_time.tm_hour >= 24) {
      current_time.tm_mday += current_time.tm_hour / 24;
      current_time.tm_hour %= 24;
  }

  while (1) {
      int max_days_in_month;
      switch (current_time.tm_mon) {
          case 0: case 2: case 4: case 6: case 7: case 9: case 11:
              max_days_in_month = 31;
              break;
          case 3: case 5: case 8: case 10:
              max_days_in_month = 30;
              break;
          case 1:
              max_days_in_month = (current_time.tm_year % 4 == 0 && (current_time.tm_year % 100 != 0 || current_time.tm_year % 400 == 0)) ? 29 : 28;
              break;
          case 12:
              max_days_in_month = 31;
              break;
          default:
              max_days_in_month = 0;
              break;
      }

      if (current_time.tm_mday > max_days_in_month) {
          current_time.tm_mday -= max_days_in_month;
          current_time.tm_mon++;

          if (current_time.tm_mon > 12) {
              current_time.tm_mon = 1;  // January of the next year
              current_time.tm_year++;
          }
      } else {
          break;
      }
  }
}

void read_time(void) {
  current_time.tm_mon = 1;
  current_time.tm_year = 124;
  current_time.tm_mday = 28;
  current_time.tm_hour = 23;
  current_time.tm_min = 59;
  current_time.tm_sec = 55;
  RTCC_CounterSet(0);
  last_counter = RTCC_CounterGet();
}

void set_time(struct tm time_info) {
  current_time.tm_year = time_info.tm_year - 1900;
  current_time.tm_mon = time_info.tm_mon - 1;
  current_time.tm_mday = time_info.tm_mday;
  current_time.tm_hour = time_info.tm_hour;
  current_time.tm_min = time_info.tm_min;
  current_time.tm_sec = time_info.tm_sec;
}
