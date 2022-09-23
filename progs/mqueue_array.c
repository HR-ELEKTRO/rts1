#include "main.h"
#include <pthread.h>
#include <mqueue.h>
#include <fcntl.h>
#include <unistd.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

typedef int ints[4];

void check_errno(int error)
{
    if (error < 0)
    {
        perror("Error");
        while (1);
    }
}

void check(int error)
{
    if (error != 0)
    {
        printf("Error: %s\n", strerror(error));
        while (1);
    }
}

void *producer(void *p)
{
    mqd_t mq = *(mqd_t *)p;
    ints a1 = {0, 1, 2, 3};
    check_errno( mq_send(mq, (char *)a1, sizeof(ints), 0) );
    ints a2 = {10, 11, 12, 13};
    check_errno( mq_send(mq, (char *)a2, sizeof(ints), 0) );
    return NULL;
}

void *consumer(void *p)
{
    mqd_t mq = *(mqd_t *)p;
    for (int i = 0; i < 2; i++)
    {
        ints a;
        check_errno( mq_receive(mq, (char *)a, sizeof(ints), NULL) );
        printf("Array ontvangen: ");
        for (int j = 0; j < sizeof a / sizeof a[0]; j++)
        {
            printf("%d ", a[j]);
        }
        printf("\n");
    }
    return NULL;
}

void *main_thread(void *arg)
{
    mqd_t mqdes;
    struct mq_attr mqAttrs;
    mqAttrs.mq_maxmsg = 1;
    mqAttrs.mq_msgsize = sizeof(ints);
    mqAttrs.mq_flags = 0;
    check_errno((int)( mqdes = mq_open("/arrays", O_RDWR | O_CREAT, 0666, &mqAttrs) ));

    pthread_t tp, tc;
    pthread_attr_t attr;
    check (pthread_attr_init(&attr) );
    check (pthread_attr_setstacksize(&attr, 1024) );
    check (pthread_create(&tp, &attr, &producer, &mqdes) );
    check (pthread_create(&tc, &attr, &consumer, &mqdes) );

    check( pthread_join(tp, NULL) );
    check( pthread_join(tc, NULL) );

    check( pthread_attr_destroy(&attr) );
    check( mq_close(mqdes) );
    check( mq_unlink("/arrays") );

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
