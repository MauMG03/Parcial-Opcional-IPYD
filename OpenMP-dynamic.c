#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

double func(int m, int n){
    if (m == 0) {
        return n + 1;
    } else if (n == 0) {
        return func(m - 1, 1);
    } else {
        return func(m - 1, func(m, n - 1));
    }
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
    




    //clock_t start, end;
    //start = clock();

    double start = omp_get_wtime();

    int num_hilos = 8;
    omp_set_num_threads(num_hilos);

    #pragma omp parallel for schedule(dynamic, size/num_hilos)
    for(int i = 0; i < size; i++){
        double resultado = func(3, vector[i]);
        resultados[i] = resultado;
    }

    double end = omp_get_wtime(); 

    printf("Vector: [");
    for (int i = 0; i < size; ++i) {
        printf("%d", resultados[i]);

        // Imprime una coma y un espacio si no es el último elemento
        if (i < size - 1) {
            printf(", ");
        }
    }
    printf("]\n");

    double time = end - start;

    printf("Tiempo de ejecución: %f segundos\n", time);
}