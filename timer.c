#ifndef TIMER_C
#define TIMER_C

/* static variable to keep track of time between calls */
static time_t timer;

/* resets timer to STARTing time */
void timer_reset() {
  timer = time(NULL);
}

/* returns the elapsed time since timer was reset. */
long timer_elapsed() {
  return (long) (time(NULL) - timer);
}

#endif /* TIMER_C */
