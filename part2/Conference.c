/*Implementation using locks and pthread_cond_wait(2).
This is a mess, probably some temporary testing stuff/failed ideas I forgot to take out,
and probably not the best solution, but it works and I need to get some sleep.*/
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include "Conf.h"

pthread_mutex_t speaking;
pthread_mutex_t asking;
pthread_mutex_t room;
pthread_cond_t question;
pthread_cond_t answer;
pthread_cond_t full;
pthread_barrier_t barrier;
int reporters_in_room;
int done = 0;
int ready = 0;
int numReporters;
int roomCapacity;
int active_id;

void *Speaker(){
	pthread_mutex_lock(&speaking);
	while(getDone() < numReporters){
		AnswerStart();
		AnswerDone();
	}
}

void *Reporter(void* arg){
	int id = (int)arg - 1;
	int questions = (id%4)+2;
	EnterConferenceRoom(id);
	for (questions; questions > 0; questions--){
		if(reporters_in_room > 1){
			usleep(1000);
		}
		pthread_mutex_lock(&asking); //no reporter asks until previous is answered
		active_id = id;
		QuestionStart(id);
		pthread_cond_wait(&answer, &speaking);
		QuestionDone(id);
		pthread_mutex_unlock(&asking);
	}
	LeaveConferenceRoom(id);
	pthread_barrier_wait(&barrier);
}

void AnswerStart(){
	ready = 1;
	pthread_cond_wait(&question, &speaking);
	printf("The Speaker starts to answer a question for reporter %d.\n", active_id);
}

void AnswerDone(){
	printf("The Speaker is done with answer for reporter %d.\n", active_id);
	ready = 0;
	pthread_cond_signal(&answer);
}

void QuestionStart(int rid){
	while (ready == 0){
		usleep(10000);
	}
	pthread_mutex_lock(&speaking);
	printf("Reporter %d asks a question.\n", rid);
	pthread_cond_signal(&question);
}

void QuestionDone(int rid){
	printf("Reporter %d is satisfied.\n", rid);
	pthread_mutex_unlock(&speaking);
}

void EnterConferenceRoom(int rid){
	while (getInRoom() == roomCapacity){
		usleep(1000); //prevents thread from spamming processor
	}
	pthread_mutex_lock(&room);
	printf("Reporter %d enters the conference room.\n", rid);
	reporters_in_room++;
	pthread_mutex_unlock(&room);
}

void LeaveConferenceRoom(int rid){
	pthread_mutex_lock(&room);
	printf("Reporter %d leaves the conference room.\n", rid);
	reporters_in_room--;
	pthread_cond_signal(&full);
	done++;
	pthread_mutex_unlock(&room);
}

int getDone(){
	pthread_mutex_lock(&room);
	int d = done;
	pthread_mutex_unlock(&room);
	return d;
}

int getInRoom(){
	pthread_mutex_lock(&room);
	int n = reporters_in_room;
	pthread_mutex_unlock(&room);
	return n;
}

int main (int argc, char *argv[]){
	
	if (argc != 3){
		fprintf(stderr, "usage: a.out <integer value> <integer value>\n");
		return -1;
	}
	numReporters = atoi(argv[1]);
	roomCapacity = atoi(argv[2]);
	pthread_t threads[numReporters + 1]; //1 thread per reporter + speaker
	pthread_barrier_init(&barrier, NULL, numReporters+1);

	pthread_create(&threads[0], NULL, Speaker, NULL);
	int i=1;
	for (i; i < numReporters+1; i++){
		int *arg = malloc(sizeof(*arg));  //Sol. of using malloc to avoid conflicts from SO /19232957   Not sure why it still gets a warning.
		if (arg == NULL){
			fprintf(stderr, "Unable to allocate memory.\n");
			exit(EXIT_FAILURE);
		}
		*arg = i;
		pthread_create(&threads[i], NULL, Reporter, (void *) i);
	}
	pthread_barrier_wait(&barrier);
	return 0;
}
