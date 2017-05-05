/**
* FILE: riemann_erroneo.c
* DESCRIPTION:
* 	Implementacion de la suma de Riemann para calcular el area bajo la
*	curva.
* AUTHOR: John Sanabria - john.sanabria@correounivalle.edu.co
* Modificado: Nathalia Ceballos - 5/05/2017 
* LAST REVISED: 14/04/16
* REFERENCES: http://mathinsight.org/calculating_area_under_curve_riemann_sums
******************************************************************************/

#include <stdio.h>
#include <pthread.h>
#include <math.h>

#define MAXRECT 1000000
#define MAXTHREAD 10
#define BASE 0.0
#define LIMIT 1.0

double length = LIMIT - BASE; // La longitud en el eje 'x'
double numRectxThread = (double)(MAXRECT/MAXTHREAD); // Cuantos hilos/rectangulo
double base_length = 0; // Variable que tiene el ancho de cada rectangulo
double sumTotal = 0; // Variable que tendra la suma total
double partialSums[MAXTHREAD]; // Variable que tien la suma parcial de c/hilo

// Funcion a la que se le calculara la integral, x^2
double function(double x) {
	return x * x; 
}
void* calcular(void *arg) {
        int id = (int)arg;
        partialSums[id]=0;
        double loslimit = id * base_length * numRectxThread;
	for (int i = 0; i < numRectxThread; i++) {
            partialSums[id] += (base_length * function(loslimit));
            loslimit += base_length;     
        }

	printf("El hilo %d calculo una suma parcial de: %lf\n", id, partialSums[id]);
	pthread_exit(NULL);
}

int main(int argc, char** argv) {
    int taskids[MAXTHREAD];
    long count=0; // almacena el total de primos en el rango [ HIGH - LOW ]
    int i, numworkers, forMistake; // numero de hilos para esta ejecucion
    pthread_t ptarray[MAXTHREAD]; // almacena 'id' de hilos
    base_length = length/MAXRECT; // esta variable contiene el ancho de
				      // cada base de cada rectangulo
    printf("base length: %lf numRectxThread: %lf\n",base_length, numRectxThread);
	// Creacion de los hilos que calcularan el area bajo la curva
    for (int i = 0; i < MAXTHREAD; i++) {
	taskids[i] = i;
        forMistake = pthread_create(&ptarray[i],NULL, calcular, (void*)taskids[i]);
        
        if(forMistake){
            printf("Error creando el hilo\n");
            exit(-1);
        }
    }
	// Ciclo donde se espera el resultado de cada hilo
    for (int i = 0; i < MAXTHREAD; i++) {
        pthread_join(ptarray[i],NULL);
        printf("Total sumas parciales %d : %f \n ", i, partialSums[i]);
        sumTotal += partialSums[i];
	}
	printf("Suma total %lf\n",sumTotal);
	pthread_exit(NULL);
}