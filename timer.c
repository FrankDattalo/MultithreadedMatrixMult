#ifndef TIMER_C
#define TIMER_C

/* static variable to keep track of time between calls */
static struct timespec start;
static struct timespec end;

/* resets timer to STARTing time */
void timer_reset() {
  clock_gettime(CLOCK_MONOTONIC, &start);
}

/* returns the elapsed time since timer was reset. */
double timer_elapsed() {
  clock_gettime(CLOCK_MONOTONIC, &end);
  return (end.tv_sec - start.tv_sec) + ((end.tv_nsec - start.tv_nsec) / 1000000000.0);
}

#endif /* TIMER_C */
