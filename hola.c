/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: Natalia
 *
 * Created on 5 de mayo de 2017, 11:01 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define MAXTHREAD 1000

void* guardaIdentificador(void* arg){

    long id = pthread_self();
    printf("hola con hilo %ld\n", id);
    pthread_exit(NULL);
}

int main(int argc, char** argv) {
    int numeroDeHilos;
    pthread_t ptarray[MAXTHREAD]; // almacena 'id' de hilos
    
    if (argc != 2) {
	printf("Por favor digite un numero hilos a usar\n");
	printf("\t%s <numeroDeHilos>\n",argv[0]);
	exit(-1);
	}
    
    	numeroDeHilos = atoi(argv[1]);
	if (numeroDeHilos > MAXTHREAD || numeroDeHilos == 0) {
            printf("Maximo numero de hilos es %d, usted solicito %d\n",MAXTHREAD, numeroDeHilos);
            exit(-1);
	}
    
        for (int i = 0; i < numeroDeHilos; i++) {
	pthread_create(&ptarray[i] ,NULL, guardaIdentificador , NULL);
	}
        pthread_exit(NULL);
    return (EXIT_SUCCESS);
}

