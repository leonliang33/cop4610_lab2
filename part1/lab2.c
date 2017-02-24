#include <pthread.h>
#include <stdio.h>
#include "test_cajigas_liang_pinales.h"
#define PTHREAD_SYNC

pthread_mutex_t lock; //new
pthread_barrier_t barrier; //new

int SharedVariable = 0;
int RAND_MAX = 6;
void *SimpleThread(void *threadID) {
	int num, val, ID = (int)threadID;
	for(num = 0; num < 20; num++) {
		// if (random() > RAND_MAX / 2){usleep(10);}
		#ifdef PTHREAD_SYNC        
		/* include your synchronization-related code here */							
			pthread_mutex_lock(&lock);
		#endif
		val = SharedVariable;
		printf("*** thread %d sees value %d\n",ID, val);
		SharedVariable = val + 1;
		#ifdef PTHREAD_SYNC
			pthread_mutex_unlock(&lock);
		#endif
        }
		#ifdef PTHREAD_SYNC
        		pthread_barrier_wait (&barrier);
		#endif
        val = SharedVariable;
        printf("Thread %d sees final value %d\n", ID, val);
};

int main (int argc, char *argv[]){
        int num_of_threads = atoi(argv[1]);
        pthread_t threads[num_of_threads];
	#ifdef PTHREAD_SYNC
        pthread_barrier_init (&barrier, NULL, num_of_threads); //new
	#endif
        if (argc != 2){
                fprintf(stderr, "usage: a.out <integer value>\n");
                return -1;
        }
        fprintf(stderr,"check %d", atoi(argv[1]));
        int i=0;
        for(i;i<num_of_threads; i++){
                pthread_create(&threads[i], NULL, SimpleThread, (void *)i);
        }

        printf("shared variable = %d\n" , SharedVariable);

	printf("%ld\n",syscall(__NR_cajigas_liang_pinales));
        pthread_exit(NULL);
}

