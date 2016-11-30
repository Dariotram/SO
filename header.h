#include <pthread.h>
#ifndef HEADER
#define HEADER
#define A_TEAM 0
#define B_TEAM 1
#define NUM_THREAD 6
typedef struct{
	unsigned int goal_A;
	unsigned int goal_B;
	int num_lettori;
	int libero;
}partita;

pthread_mutex_t mutex;
pthread_cond_t lib;

void init(partita*);
void Aggiornamento( partita*,int );
void* TB(void*);
void* TA(void*);
void* Utente(void*);
#endif
