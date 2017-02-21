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
void answerStart(int id){
	printk("Speaker starts to answer question for reporter %d\n",id);
}
void answerDone(int id){
	printk("Speaker is done with answer for reporter %d.\n",id);
}
void enterConferenceRoom(int id){
	printk("Reporter %d enters the conference room",id);
}
void leaveConferenceRoom(int id){
	printk("Reporter %d leaves the conference room",id);
}
void questionStart(int id){
	printk("Reporter %d asks a question.",id);
}
void questionDone(int id){
	printk("Reporter %d is satisfied.",id);
}
int main(int argc, char* argv[]){
	
	speaker();
}
