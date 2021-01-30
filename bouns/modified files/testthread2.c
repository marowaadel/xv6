#include "types.h"
#include "stat.h"
#include "user.h"
#include "kthread.h"

#define LOCKS_ON 1
#define NULL 0


void idkifthisworks(void* arg)
{
    printf(1, "it works!\n");
    exit();
}

// global lock for product
lock_t lock;
// our product
volatile int things = 0;
volatile int things_made = 0;
#define MAX_CONSUME 1000000
void consumer(void* arg)
{
    volatile int i;
    int consumed = 0;
    // dumb little busy sleep
    for (i = 0; i < 200; i++);

    while (consumed < MAX_CONSUME)
    {
        // not thread safe but give producers time
        while(things <= 0) sleep(0);
        #if LOCKS_ON
        lock_acquire(&lock);
        #endif
        if (things > 0)
        {
            // useful consumption of resources algorithm
            // guaranteed optimal usage
            --things;
            ++consumed;
        }
        #if LOCKS_ON
        lock_release(&lock);
        #endif
    }

    printf(1, "consumer %d consumed: %d\n", *(int*)arg, consumed);


    exit();
}

#define NUM_PROD 2
#define NUM_CONS 4
#define TOTAL_PRODUCTS 10000000
void producer(void* arg)
{
    int cont = 1;
    while (cont)
    {
        #if LOCKS_ON
        lock_acquire(&lock);
        #endif
        // magical producing algorithm
        if (things_made < TOTAL_PRODUCTS)
        {
            ++things;
            ++things_made;
        }
        else
        {
            cont = 0;
        }
        #if LOCKS_ON
        lock_release(&lock);
        #endif
    }
    exit();
}

int main(void)
{
    int i;
    init_lock(&lock);
    int indices[NUM_CONS];
    kthread_t producers[NUM_PROD];
    kthread_t consumers[NUM_CONS];
    for (i = 0; i < NUM_CONS; i++)
    {
        indices[i] = i;
        consumers[i] = thread_create(consumer, &indices[i]);
    }
    for (i = 0; i < NUM_PROD; i++)
    {
        producers[i] = thread_create(producer, NULL);
    }
    // printf(1,"complete create prod and cons\n");
    // printf(1,"==========================================\n");
    // printf(1,"enter prod join\n");
    for (i = 0; i < NUM_PROD; i++)
    {
        thread_join(producers[i]);
    }
    //printf(1,"enter cons join\n");
    for (i = 0; i < NUM_CONS; i++)
    {
        thread_join(consumers[i]);
    }
    //printf(1,"==========================================\n");
    printf(1, "Remaining products: %d\n", things);
    printf(1, "Things made: %d\n", things_made);
    #define REMAINING (int)(TOTAL_PRODUCTS - NUM_CONS * (double)MAX_CONSUME)
    if (things != (REMAINING))
    {
        printf(1, "Lock/thread issue detected, should be %d things left\n", REMAINING);
    }
    else
    {
        printf(1, "Test passed!\n");
    }

    kthread_t works = thread_create(idkifthisworks, NULL);
    thread_join(works);
    exit();
}
