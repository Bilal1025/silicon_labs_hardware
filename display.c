/*
 * display.c
 *
 *  Created on: 15-Nov-2023
 *      Author: bilal
 */


#include "display.h"

static GLIB_Context_t glibContext;
static int currentLine = 2;

void memlcd_init(void) {
    uint32_t status;

    /* Enable the memory lcd */
    status = sl_board_enable_display();
    EFM_ASSERT(status == SL_STATUS_OK);

    /* Initialize the DMD support for memory lcd display */
    status = DMD_init(0);
    EFM_ASSERT(status == DMD_OK);

    /* Initialize the glib context */
    status = GLIB_contextInit( & glibContext);
    EFM_ASSERT(status == GLIB_OK);

    glibContext.backgroundColor = White;
    glibContext.foregroundColor = Black;

    /* Fill lcd with background color */
    GLIB_clear( & glibContext);

    /* Use Narrow font */
    GLIB_setFont( & glibContext, (GLIB_Font_t * ) & GLIB_FontNarrow6x8);
}

void print_content(char * content, int line) {
    GLIB_drawStringOnLine( & glibContext,
        "                                           ",
        line,
        GLIB_ALIGN_LEFT,
        5,
        5,
        true);
    GLIB_drawStringOnLine( & glibContext,
        content,
        line,
        GLIB_ALIGN_LEFT,
        5,
        5,
        true);
    DMD_updateDisplay();
}

void print_space(int current_line, int blink_index) {
  size_t pixels = glibContext.font.fontWidth;
  GLIB_drawStringOnLine( & glibContext,
          " ",
          current_line,
          GLIB_ALIGN_LEFT,
          (blink_index * pixels) + 5,
          5,
          true);
  DMD_updateDisplay();
}
