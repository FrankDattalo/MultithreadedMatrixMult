#ifndef TIMER_C
#define TIMER_C

#include "include.h"

/* START = time(NULL) */
#define START time(&((time_t) 0))

/* static variable to keep track of time between calls */
static time_t timer;

/* resets timer to STARTing time */
void timer_reset() {
  timer = START;
}

/* returns the elapsed time since timer was reset. */
long timer_elapsed() {
  return (long) (START - timer);
}

#endif /* TIMER_C */
