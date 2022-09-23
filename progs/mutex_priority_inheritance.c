#include "main.h"
#include <pthread.h>
#include <unistd.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

/* This program shows that FreeRTOS uses priority inheritance.
 * Without priority inheritance NO OUTPUT should occurs because Thead 1 blocks Thread 3
 * With priority inheritance Thead 1 can finish so output will be "count = 501"
 * Call pthread_mutexattr_setprotocol is NOT supported in FreeRTOS
 * */

void check(int error)
{
    if (error != 0)
    {
        printf("Error: %s\n", strerror(error));
        while (1);
    }
}

int count = 0;
pthread_mutex_t m;

// Dummy thread will occupy the processor for ever.
void *dummy(void *par)
{
    while(1);
    return NULL;
}

void *counter1(void *par)
{
    pthread_attr_t pta2;
    check( pthread_attr_init(&pta2) );
    check( pthread_attr_setstacksize(&pta2, 1024) );
    struct sched_param sp2;
    check( pthread_attr_getschedparam(&pta2, &sp2) );
    sp2.sched_priority = 2;
    check( pthread_attr_setschedparam(&pta2, &sp2) );
    pthread_t t2;

    for (int i = 0; i < 500000; i++)
    {
        check( pthread_mutex_lock(&m) );
        // start dummy thread that occupies the processor for ever
        check( pthread_create(&t2, &pta2, &dummy, NULL) );
        count += 1;
        check( pthread_mutex_unlock(&m) );
    }
    check( pthread_attr_destroy(&pta2) );
    return NULL;
}

void *counter2(void *par)
{
    struct timespec delay = {.tv_sec = 0, .tv_nsec = 1};
    for (int i = 0; i < 500; i++)
    {
        check( pthread_mutex_lock(&m) );
        count += 1;
        check( pthread_mutex_unlock(&m) );
        clock_nanosleep(CLOCK_MONOTONIC, 0, &delay, NULL);
    }
    return NULL;
}

void *main_thread(void *arg)
{
    pthread_mutexattr_t ma;
    check( pthread_mutexattr_init(&ma) );
    check( pthread_mutex_init(&m, &ma) );

    pthread_attr_t pta1;
    check( pthread_attr_init(&pta1) );
    check( pthread_attr_setstacksize(&pta1, 1024) );
    struct sched_param sp1;
    check( pthread_attr_getschedparam(&pta1, &sp1) );
    sp1.sched_priority = 1;
    check( pthread_attr_setschedparam(&pta1, &sp1) );

    pthread_attr_t pta3;
    check( pthread_attr_init(&pta3) );
    check( pthread_attr_setstacksize(&pta3, 1024) );
    struct sched_param sp3;
    check( pthread_attr_getschedparam(&pta3, &sp3) );
    sp3.sched_priority = 3;
    check( pthread_attr_setschedparam(&pta3, &sp3) );

    pthread_t t1, t3;
    check( pthread_create(&t1, &pta1, &counter1, NULL) );
    check( pthread_create(&t3, &pta3, &counter2, NULL) );

    // Only wait for most important task
    check( pthread_join(t3, NULL) );
    printf("\ncount = %d\n", count);

    check( pthread_join(t1, NULL) );

    check( pthread_mutexattr_destroy(&ma) );
    check( pthread_mutex_destroy(&m) );

    check( pthread_attr_destroy(&pta1) );
    check( pthread_attr_destroy(&pta3) );

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
