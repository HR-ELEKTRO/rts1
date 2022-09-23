#include "main.h"
#include <pthread.h>
#include <unistd.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

/* This program shows the deadlock problem that can arise
 * if threads lock two mutexes in the same order. */

void check(int error)
{
    if (error != 0)
    {
        printf("Error: %s\n", strerror(error));
        while (1);
    }
}

pthread_mutex_t dinner_fork[5]; // named dinner_fork because fork is a system call

void *philosopher(void *par)
{
    int i = *(int*)par;
    while (1)
    {
        printf("philosopher %d is sleeping\n", i);
        usleep(100000 * (rand() % 5 + 1));
        printf("philosopher %d (tries to) picks up left fork\n", i);
        check( pthread_mutex_lock(&dinner_fork[i]) );
        sleep(1); // This extra sleep ensures the deadlock to appear immediately
        printf("philosopher %d (tries to) picks up right fork\n", i);
        check( pthread_mutex_lock(&dinner_fork[(i + 1) % 5]) );
        printf("philosopher %d is eating\n", i);
        usleep(100000 * (rand() % 5 + 1));
        check( pthread_mutex_unlock(&dinner_fork[i]) );
        printf("philosopher %d lies down left fork\n", i);
        check( pthread_mutex_unlock(&dinner_fork[(i + 1) % 5]) );
        printf("philosopher %d lies down right fork\n", i);
    }
    return NULL;
}

void *main_thread(void *arg)
{
    pthread_mutexattr_t ma;
    check( pthread_mutexattr_init(&ma) );
    for (int i = 0; i < 5; i++)
    {
        check( pthread_mutex_init(&dinner_fork[i], &ma) );
    }

    pthread_attr_t pta;
    check( pthread_attr_init(&pta) );
    check( pthread_attr_setstacksize(&pta, 1024) );

    pthread_t t[5];
    int tid[5];
    for (int i = 0; i < 5; i++)
    {
        tid[i] = i;
        check( pthread_create(&t[i], &pta, &philosopher, &tid[i]) );
    }

    for (int i = 0; i < 5; i++)
    {
        check( pthread_join(t[i], NULL) );
    }

    for (int i = 0; i < 5; i++)
    {
        check( pthread_mutex_destroy(&dinner_fork[i]) );
    }
    check( pthread_mutexattr_destroy(&ma) );
    check( pthread_attr_destroy(&pta) );

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
