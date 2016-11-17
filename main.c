#ifndef MAIN_C
#define MAIN_C

#include "includes.h"

int main(int argc, char** argv) {
  int i;

  init();

  for(int i = 0; i < 6; i++) {
    thread_calc(i); /* calculate matrix with i amount of threads */
    printStats(i + 1); /* print statistics about calculation */

    if(i != 5) {
      init();
    }
  }

  return 0;
}

#endif /* MAIN_C */
