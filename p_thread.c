#include <pthread.h>

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct parametros {
    int resultado;
    int m;
    int n;
    int id;
};

double func(int m, int n){
    if (m == 0) {
        return n + 1;
    } else if (n == 0) {
        return func(m - 1, 1);
    } else {
        return func(m - 1, func(m, n - 1));
    }
}

void *funcionHilo(void *args) {
    struct parametros *p;

    p = ( struct parametros *) args;

    p -> resultado = func(p ->m, p-> n);
}

int main(int argc, char *argv[]){
    if (argc < 2) {
        printf("Error al ejecutar, Uso: %s <v1> <v2> ... <vn>\n", argv[0]);
        return 1;
    }

    int size = argc - 1;
    int *vector = (int *)malloc(size * sizeof(int));

    int *resultados = (int *)malloc(size * sizeof(int));

    if (vector == NULL) {
        perror("Error de asignación de memoria");
        return 1;
    }

    for (int i = 0; i < size; ++i) {
        vector[i] = atoi(argv[i + 1]);
    }







    clock_t start, end;

    int num_hilos = 2;
    pthread_t hilos[num_hilos];

    for(int i = 0; i < num_hilos; i++){
        struct parametros p = {1,3}


        pthread_create(&hilos[i],NULL,funcionHilo,NULL);
    }

    start = clock();



    end = clock();

    printf("Vector: [");
    for (int i = 0; i < size; ++i) {
        printf("%d", resultados[i]);

        // Imprime una coma y un espacio si no es el último elemento
        if (i < size - 1) {
            printf(", ");
        }
    }
    printf("]\n");

    double time = ((double)(end - start)) / CLOCKS_PER_SEC;

    printf("Tiempo de ejecución: %f segundos\n", time);
}