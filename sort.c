#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

void order(float list[], int n){  //Algoritmo bubble sort
    float aux;
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (list[i] > list[j]) {
                aux = list[i];
                list[i] = list[j];
                list[j] = aux;
            }
        }
    }
}

void shorter_distances (float list[], int n, float shorters[]) {
    float copy_list[n];
    for (int i = 0; i < n; i++){
        copy_list[i] = list[i];
    }
    order(copy_list, n);
    for (int i = 0; i < 8; i++){
        shorters[i] = copy_list[i]; 
    }
}

int main(){

    float values[20]; //Ese numero depende de la cantidad de equipos
    float distances[8];
    int n = sizeof(values) / sizeof(float);
    
    shorter_distances(values, n, distances);

    printf("Lista original: \n");
    for (int i = 0; i < n; i++) {
        printf("%0.1f ", values[i]);
    }
    printf("\n ");

    printf("Los 4 elementos mas pequenios son: \n");
    for (int i = 0; i < 4; i++) {
        printf("%0.1f ", distances[i]);
    }
    printf("\n");

	return 0;
}