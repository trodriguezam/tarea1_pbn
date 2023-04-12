#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

//FUNCIONES

// =====================================================================

float distance(float x1, float x2, float y1, float y2){
    return sqrt(pow((x2 - x1), 2) + pow((y2 - y1), 2));
}

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

// =====================================================================

//MAIN

int main(){
    char line[100];
    float teams[20][2], matrix[20][20];
    float distances[8];
    int n = sizeof(matrix[0]) / sizeof(float);
    int k = 0;
    FILE* input;
    FILE* output;
	
    input = fopen("equipos_corto.txt", "r");
    output = fopen("partidos.txt", "w");
    
    while(fgets(line, 100, input)){     //Crea un arreglo con las coordenadas de los equipos
        char* value = strtok(line, ",");
        char* teamx;
        float x;
        float y;
        for(int i = 0; i<3; i++){
            if (i == 0){
                teamx = value;
            }
            else if(i == 1){
                x = atof(value);
            }
            else if(i == 2){
                y = atof(value);
            }
            value = strtok(NULL, ",");
        }
        teams[k][0] = x;
        teams[k][1] = y;
        k++;
    }
    fclose(input);
    fclose(output);

    for(int row = 0; row < 20; row++){      //Crea la matriz de distancias
        for(int col = 0; col < 20; col++){
            if(row == col){
                matrix[row][col] = 0;
            }
            else{
                matrix[row][col] = distance(teams[row][0], teams[col][0], teams[row][1], teams[col][1]);
            }
        }
    }

    for(int i = 0; i <20; i++){     //Crea un arreglo con las 8 distancias mas cortas
        shorter_distances(matrix[i], n, distances);
    }

    for(int i = 0; i < 8; i++){     //Imprime las 8 distancias mas cortas
        printf("%0.1f ", distances[i]);
    }

	return 0;
}