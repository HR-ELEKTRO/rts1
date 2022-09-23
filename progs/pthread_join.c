#include "main.h"
#include <pthread.h>
#include <unistd.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

// Simple program to test pthread_join.

void check(int error)
{
    if (error != 0)
    {
        printf("Error: %s\n", strerror(error));
        while (1);
    }
}

void *thread(void *p) {
    printf("thread started\n");
    int i = *(int *)p;
    i = i * i;
    // The thread cannot return a pointer to a local variable

    int* pi = malloc(sizeof(int));
    *pi = i;
    return pi;
}

void *main_thread(void *arg) {
    int i = 12;
    printf("i = %d\n", i);

    pthread_attr_t attr;
    check( pthread_attr_init(&attr) );
    check( pthread_attr_setstacksize(&attr, 1024) );
    pthread_t t;
    check( pthread_create(&t, &attr, &thread, &i) );

    void* res;
    check( pthread_join(t, &res) );
    printf("thread finished. res = %d\n", *(int *)res);
    free(res);
    return NULL;
}

int main(void)
{
    Board_Init();

    pthread_attr_t pta;
    check( pthread_attr_init(&pta) );
    check( pthread_attr_setdetachstate(&pta, PTHREAD_CREATE_DETACHED) );
    check( pthread_attr_setstacksize(&pta, 1024) );

    struct sched_param sp;
    check( pthread_attr_getschedparam(&pta, &sp) );
    // The main thread must have the highest priority because this thread will start
    // the other threads and we want to study the interaction between those other threads
    sp.sched_priority = 15;
    check( pthread_attr_setschedparam(&pta, &sp) );

    pthread_t pt;
    check( pthread_create(&pt, &pta, main_thread, NULL) );

    printf("\n");
	vTaskStartScheduler();
	/* We should never get here as control is now taken by the scheduler */

    check( pthread_attr_destroy(&pta) );

    return EXIT_SUCCESS;
}
