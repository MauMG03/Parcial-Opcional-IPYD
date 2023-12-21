#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <sys/time.h>

#define SIZE 16
#define HILOS 8

int resultados[SIZE];

double func(int m, int n){
    if (m == 0) {
        return n + 1;
    } else if (n == 0) {
        return func(m - 1, 1);
    } else {
        return func(m - 1, func(m, n - 1));
    }
}

struct parametros {
    int id;
    int* resultados;
    int* vector;
};

void *miFuncion(void* args){
    struct parametros *p;

    p = ( struct parametros *) args;
    int salto = SIZE/HILOS;

    for(int i=0; i < SIZE/HILOS; i++){
        p -> resultados[(salto * (p -> id)) + i] = func(3, p -> vector[(salto * (p -> id)) + i]);
    }
}

int main(int argc, char *argv[]){
    if (argc < 2) {
        printf("Error al ejecutar, Uso: %s <v1> <v2> ... <vn>\n", argv[0]);
        return 1;
    }

    int size = argc - 1;
    int *vector = (int *)malloc(size * sizeof(int));

    if (vector == NULL) {
        perror("Error de asignación de memoria");
        return 1;
    }

    for (int i = 0; i < size; ++i) {
        vector[i] = atoi(argv[i + 1]);
    }

     struct timeval start, end;

    gettimeofday(&start, NULL);
    

    pthread_t hilos[HILOS];
    struct parametros *parametros_hilos = (struct parametros *)malloc(HILOS * sizeof(struct parametros));

    for(int i = 0; i < HILOS; i++){
        parametros_hilos[i].id = i;
        parametros_hilos[i].resultados = resultados;
        parametros_hilos[i].vector = vector;
        
        pthread_create(&hilos[i],NULL,miFuncion,(void*)&parametros_hilos[i]);
    }

    for(int i = 0; i < HILOS; i++){
        pthread_join(hilos[i],NULL);
    }

    gettimeofday(&end, NULL);


    printf("Vector: [");
    for (int i = 0; i < size; ++i) {
        printf("%d", resultados[i]);

        // Imprime una coma y un espacio si no es el último elemento
        if (i < size - 1) {
            printf(", ");
        }
    }
    printf("]\n");

    double time = (double)(end.tv_sec - start.tv_sec) + (double)(end.tv_usec - start.tv_usec) / 1000000;

    printf("Tiempo de ejecución: %f segundos\n", time);
}