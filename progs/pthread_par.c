#include "main.h"
#include <pthread.h>
#include <unistd.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

/* This program shows how to pass arguments to a thread. */

void check(int error)
{
    if (error != 0)
    {
        printf("Error: %s\n", strerror(error));
        while (1);
    }
}

typedef struct
{
    char *msg;
    useconds_t us;
} par_t;

void *print(void *par)
{
    par_t* p = par;
    for (int i = 0; i < 10; i++)
    {
        usleep(p->us);
        printf(p->msg);
    }
    return NULL;
}

void *main_thread(void *arg)
{
    pthread_attr_t pta;
    check( pthread_attr_init(&pta) );
    check( pthread_attr_setstacksize(&pta, 1024) );

    pthread_t t1, t2;
    par_t p1 = {"print1\n", 100000};
    par_t p2 = {"print2\n", 200000};
    check( pthread_create(&t1, &pta, &print, &p1) );
    check( pthread_create(&t2, &pta, &print, &p2) );

    check( pthread_join(t1, NULL) );
    check( pthread_join(t2, NULL) );

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
