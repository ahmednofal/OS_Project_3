#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <stdio.h>
#include <time.h>

#include <sys/types.h>

// macros

#define NUM_THREADS 5

#define trylock_on_2(philo_num)\
        (pthread_mutex_trylock(&mutex[philo_num%NUM_THREADS]) != 0)


// && (pthread_mutex_trylock(&mutex[philo_num+1]) != 0)

#define mutex_locked(philo_num)\
        (mutex[philo_num].__data.__lock > 0)

// && (mutex[(philo_num+1)%NUM_THREADS].__data.__lock > 0

#define cond_wait_on(philo_num)\
        do{pthread_cond_wait(&cond_var[philo_num], &mutex[philo_num]);\
            }while(0)

//pthread_cond_wait(&cond_var[philo_num+1%NUM_THREADS], &mutex[philo_num+1%NUM_THREADS]);\

#define mutex_lock(philo_num)\
        do{\
        pthread_mutex_lock(&mutex[philo_num%NUM_THREADS]);\
            }while(0)

//pthread_mutex_lock(&mutex[philo_num+1%NUM_THREADS]);\

#define mutex_unlock_2(philo_num)\
        do{\
        pthread_mutex_unlock(&mutex[philo_num]);\
        pthread_mutex_unlock(&mutex[(philo_num+1)%NUM_THREADS]);\
            }while(0)

#define cond_signal_2(philo_num)\
        do{\
        pthread_cond_signal(&cond_var[philo_num]);\
        pthread_cond_signal(&cond_var[(philo_num+1)%NUM_THREADS]);\
            }while(0)

// Shared Resources
pthread_t philosophers[NUM_THREADS]; /* the thread identifier */
pthread_attr_t philosophers_attr[NUM_THREADS]; /* set of thread attributes */
pthread_mutex_t mutex[NUM_THREADS];
pthread_cond_t cond_var[NUM_THREADS];

// Function Prototypes

void* runner(void *param); /* threads call this function*/
void pickup_forks(int philo_num);
void return_forks(int philo_num);
struct arguments{
	pthread_mutex_t mutex;
	pthread_cond_t cond_var;
};


int main(int argc, char *argv[])
{
    srand(time(NULL));
	struct arguments args;
	/* get the default attributes */
	/* Just a brain storm*/
	/* what I need to do
		I need to initialize 5 threads one for each philo_num
	what I do not know how are threads simulating this behavior 
	of philosophers when they do not know the resources
	allocated for each other thread*/
	for (int i =0; i < NUM_THREADS; i++)
		pthread_attr_init(&philosophers_attr[i]);
	/* create the thread */
	for (int i =0; i < NUM_THREADS; i++)
		pthread_mutex_init(&mutex[i], NULL);
	for (int i =0; i <NUM_THREADS; i++)
    {
        //printf("inside pthread_create loop with i:%d \n", i);
        pthread_create(&philosophers[i],&philosophers_attr[i], &runner, &i);

    }
	/* wait for the thread to exit */
	for (int i =0; i < NUM_THREADS; i++)
		pthread_join(philosophers[i],NULL);	
}
/* The thread will begin control in this function */
void* runner(void *param)
{
    int secs_to_slp = rand()+1%3;

    int philo_num = *((int*) param);
    // The philosopher will start by trying to eat, all of them will
    // which means it will try to lock the corresponding mutex and the mutex of the next philosopher
    // if any of them fails it will wait on that mutex
    // Waiting should be executed using the cond_var
    // it will wait on both mutexes if both are not available
    //printf("inside runner with philosopher :%d \n", *((int*) param));
    //sprintf("mutex[philo_num].__data.__lock %d", mutex[*((int*) param)].__data.__lock );
    pickup_forks(philo_num);
    sleep(1);
    return_forks(philo_num);
    pthread_exit(0);

}
// Requesting resources
void pickup_forks(int philo_num)
{
    int right = philo_num;
    int left = (philo_num+1)%NUM_THREADS;
//    printf("philo_num %d\n",philo_num);
//    printf("mutex %d   state is :    %d\t\n", right,mutex[philo_num].__data.__lock );
//    printf("mutex %d   state is :    %d\t\n", left,mutex[philo_num].__data.__lock );
    if (!mutex_locked(right) && !mutex_locked(left))
    {
        mutex_lock(right);
        mutex_lock(left);
//        printf("inside 1");
//        printf("mutex %d   state is :    %d\t\n", right,mutex[philo_num].__data.__lock );
//        printf("mutex %d   state is :    %d\t\n", left,mutex[philo_num].__data.__lock );
    }
    else
        if (!mutex_locked(right) && mutex_locked(left))
        {
            printf("inside 2");
            mutex_lock(right);
            while(mutex_locked(left))
            cond_wait_on(right);
//            printf("mutex %d   state is :    %d\t\n", right,mutex[philo_num].__data.__lock );
//            printf("mutex %d   state is :    %d\t\n", left,mutex[philo_num].__data.__lock );
        }

        else
            if (!mutex_locked(left) && mutex_locked(right))
            {
                printf("inside 3");
                mutex_lock(left);
                while(mutex_locked(right))
                {
                    cond_wait_on(left);
                }
//                printf("mutex %d   state is :    %d\t\n", right,mutex[philo_num].__data.__lock );
//                printf("mutex %d   state is :    %d\t\n", left,mutex[philo_num].__data.__lock );
            }
    //printf("inside pickup forks with philosopher :%d \n", philo_num);

}
// Returning resources
void return_forks(int philo_num)
{
    //printf("inside return forks with philosopher :%d \n", philo_num);
    cond_signal_2(philo_num);
    mutex_unlock_2(philo_num);

}
