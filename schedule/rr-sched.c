#define _GNU_SOURCE
#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


int main(int argc, char *argv[]) {
  unsigned long long count=0;
  struct sched_param param;
  cpu_set_t mask;

  if (argc < 2) {
    printf("Usage: %s <priority> [SLEEP]\n", argv[0]);
    return 0;
  }

  printf("SCHED_RR with priority %d about to pin to CPU 0.\n",
	 atoi(argv[1]));
  param.sched_priority = atoi(argv[1]);
  if (sched_setscheduler(0, SCHED_RR, &param) != 0) {
    perror("sched_setscheduler:");
    return 0;
  }
  
  CPU_ZERO(&mask);
  CPU_SET(0, &mask);
  if (sched_setaffinity(0, sizeof(mask), &mask) !=0 ) {
    perror("sched_setaffinity:");
    return 0;
  }

  printf("SCHED_RR pinned to CPU 0.\n");

  while (1) {
    count++;
    if (count % 10000000ULL == 0) {
      printf("SCHED_RR with priority %d in loop iteration %lld running\n",
	     atoi(argv[1]), count);
      if (argc > 2) {
	printf("SLEEP...\n");
	usleep(100);
      }
    }
  }
}
