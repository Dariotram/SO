#include <pthread.h>
#include "header.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

void init(partita* p){
p->goal_A=0;
p->goal_B=0;
p->libero=0;
p->num_lettori=0;
pthread_mutex_init(&mutex,NULL);
pthread_cond_init(&lib,NULL);
}

void Aggiornamento(partita* p, int squadra){
	pthread_mutex_lock(&mutex);
	printf("Entro nel mutex e aggiorno il lettore\n");
	p->libero=0;
	if(squadra==A_TEAM){
		p->goal_A=p->goal_A + (rand()%2);
		printf("<SCRIVO> Il risultato del match è stato aggiornato per il team A ora ha <%d> goal \n",p->goal_A);
		}
	if(squadra==B_TEAM){
		p->goal_B=p->goal_B + (rand()%2 );
		printf("<SCRIVO> Il risultato del match è stato aggiornato per il team B ora ha <%d> goal \n",p->goal_B);
	}
	p->libero=1;
	pthread_cond_signal(&lib);	
	pthread_mutex_unlock(&mutex);
}



void* TA(void* p){
	partita* P;
	P=(partita*) p;
	for(int i=0;i<6;i++){
		Aggiornamento(P,A_TEAM);
		sleep(15);
	}
}

void* TB(void* p){
	partita* P;
	P=(partita*) p;
	for(int i=0;i<6;i++){
		Aggiornamento(P,B_TEAM);
		
		sleep(15);
	}
}

void *Utente(void* p){
	partita* P;
	P=(partita*) p;

	for(int i=0;i<18;i++){
	pthread_mutex_lock(&mutex);
	printf("entro nel mutex come lettore e aggiorno il numero \n");
	P->num_lettori=P->num_lettori+1;
	while(P->libero==0)
		pthread_cond_wait(&lib,&mutex);
	
		
	printf("<LEGGO> A <%d> e   B <%d> goal, abbiamo <%d> lettori \n ",P->goal_A,P->goal_B,P->num_lettori);
	pthread_mutex_unlock(&mutex);
	P->num_lettori=P->num_lettori-1;
	sleep(5);
	}
}
