// Módulo 1 - Laboratório: 1
// Aluna: Carla Moreno Barbosa
// DRE: 117250502
// Objetivo: Implementar um programa concorrente, com duas threads
//           (além da thread principal), para incrementar de 1 cada elemento de
//           um vetor de N (10 < N < 100) elementos.

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NTHREADS 2
#define TAMANHOVETOR 10

// Estrutura que armazena argumentos da thread
typedef struct {
	int * vetor;
	int tam;
} t_Args;

// Função executada pelas threads
void * incremento (void *arg) {
	t_Args * input = (t_Args *) arg;
	int * vetor = input -> vetor; // inicio da partição do vetor

// Incremento da partição do vetor
	for (int i = 0; i < input->tam; i++) {
		vetor[i] += 1;
	}
	free(arg);
	pthread_exit(NULL);
}

// Função main
int main(void) {
	pthread_t tid[NTHREADS];
	int thread;
	int vetor[TAMANHOVETOR];
	t_Args *arg;
  int aux = 0;
	int resto = TAMANHOVETOR % NTHREADS;
	int tam = TAMANHOVETOR / NTHREADS;

// Inicializa e imprime vetor original (antes de ser incremetado)
	printf("Vetor original:");
	for(int i = 1; i <= TAMANHOVETOR; i++) {
		vetor[i-1] = i;
		printf(" %d", vetor[i-1]);
	}

//Aloca e dá os argumentos da thread
	for(thread = 1; thread <= NTHREADS; thread++) {
		arg = malloc(sizeof(* arg));
		arg -> vetor = vetor + aux;
	 	aux += tam;
		arg->tam = tam;
		if (resto > 0) {
			resto -= 1;
			arg->tam += 1;
			aux += 1;
		}
		if (pthread_create(&tid[thread-1], NULL, incremento, (void *) arg)) {
			printf("--ERRO: pthread_create()\n"); exit(-1);
		}
	}
  printf("\n");

// Aguarda as threads terminarem para prosseguir
	for (thread=0; thread<NTHREADS; thread++) {
		if (pthread_join(tid[thread], NULL)) {
			printf("--ERRO: pthread_join() \n"); exit(-1);
		}
	}

// Imprime vetor final (vetor original com cada posição incrementada de 1)
	printf("Vetor final:");
	for(int i = 1; i <= TAMANHOVETOR; i++) {
		printf(" %d", vetor[i-1]);
	}
  printf("\n");
	return 0;
}
