#include <pthread.h>
#include "header.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
int main(){
pthread_t thread[NUM_THREAD];
pthread_attr_t attr;
partita* match;
match=(partita*) malloc(sizeof(partita) ); ;

init(match);
pthread_attr_init(&attr);
pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_JOINABLE);


srand(time(NULL) );
for(int i=0;i<NUM_THREAD;i++){
	if(i==0)
		pthread_create(&thread[i],&attr,TA,(void* )match );
	if(i==1){
		pthread_create(&thread[i],&attr,TB,(void*) match );
	}else{
		pthread_create(&thread[i],&attr,Utente,(void* )match );
	}
}

for(int i=0;i<NUM_THREAD;i++){
pthread_join(thread[i],NULL);
printf("Il thread #%d è terminato \n",i );
}

printf("La partita è FINITA con  Squadra A : [%d] e Squadra B : [%d] \n ",match->goal_A,match->goal_B );

free(match);
pthread_attr_destroy(&attr);
pthread_mutex_destroy(&mutex);
pthread_cond_destroy(&lib);
pthread_exit(0);
}
