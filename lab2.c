#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>

pthread_t speaker;
pthread_barrier_t begin;
pthread_barrier_t stop;

void speaker(){
	pthread_create(&speaker,NULL,speakerAnswer,NULL);
}

void* speakerAnswer(){
	answerStart();
	answerDone();
}
void reporter(int id){

}
void answerStart(){

}
void answerDone(){

}
void enterConferenceRoom(){

}
void leaveConferenceRoom(){

}
void questionStart(){

}
void questionDone(){

}
