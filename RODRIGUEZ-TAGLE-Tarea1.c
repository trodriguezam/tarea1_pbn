#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
 
float distance(float x1, float x2, float y1, float y2){
    return sqrt(pow((x2 - x1), 2) + pow((y2 - y1), 2));
}

void bubble_sort(float values[], char **names, int index[], int n){
    int sorted = 1;

    for(int current = 0; current < n - 1; current++){
        if(values[current] > values[current + 1]){
            char *naux;

            float vaux = values[current];
            int iaux = index[current];
            naux = names[current];

            values[current] = values[current + 1];
            index[current] = index[current + 1];
            names[current] = names[current + 1];

            values[current + 1] = vaux;
            index[current + 1] = iaux;
            names[current + 1] = naux;
            
            sorted = 0;
        }
    }

    if(sorted == 0) bubble_sort(values, names, index, n);
}

int main(){

    char line[100];
    int N = 0;
    FILE *input;
    FILE *output;

    input = fopen("equipos.txt", "r");
    output = fopen("partidos.txt", "w");

    while(fgets(line, 100, input)){
        N++;
    }

    fclose(input);
    fclose(output);

    char *team_names[N];
    char *copy_name[N];
    float teams[N][2], matrix[N][N], copy_matrix[N][N], daverage[N];
    int matches[N][4];
    int counters[N];
    int team_index[N];
    int copy_index[N];
    int k = 0;
 
    printf("El numero de equipos es: %d \n", N);
	
    for(int i = 0; i < N; i++){
        team_index[i] = i;
        copy_index[i] = i;
        counters[i] = 0;
    }

    input = fopen("equipos.txt", "r");
    output = fopen("partidos.txt", "w");

    while(fgets(line, 100, input)){
        char *value = strtok(line, ",");
        float x;
        float y;
        for(int i = 0; i < 3; i++){
            if (i == 0) team_names[k] = strdup(value);
            else if(i == 1) x = atof(value);
            else if(i == 2) y = atof(value);
            value = strtok(NULL, ",");
        }
        
        teams[k][0] = x;
        teams[k][1] = y;
        k++;
    }

    fclose(input);
    fclose(output);
    
    // distance matrix
    for(int row = 0; row < N; row++){
        for(int col = 0; col < N; col++){
                matrix[row][col] = distance(teams[row][0], teams[col][0], teams[row][1], teams[col][1]);
                copy_matrix[row][col] = distance(teams[row][0], teams[col][0], teams[row][1], teams[col][1]);
        }
    }
    printf("\n");
    
    // Avg distance from teamx to each team
    for(int i = 0; i < N; i++){
        float sum = 0;
        for(int k = 0; k < N; k++){
            sum += matrix[i][k];
        }
        daverage[i] = sum/(N - 1);
    }

    int n = sizeof(daverage) / sizeof(daverage[0]);

    for(int i = 0; i < n; i++) {
        copy_name[i] = team_names[i];
    }

    bubble_sort(daverage, team_names, team_index, n);  //Bubble sort, ordena las distancias promedio

    for(int i = 0; i < n; i++) {
        copy_index[i] = team_index[i];
    }

    for(int i = 0; i < n; i++) {
        for(int a = 0; a < n; a++){
            team_index[a] = a;
        }
        bubble_sort(matrix[copy_index[(N - 1) - i]], team_names, team_index, n);  
        for (int j = 0; j < N; j++){
            if (((counters[copy_index[(N - 1) - i]] < 4) && (counters[team_index[j + 1]] < 4))){
                matches[copy_index[(N - 1) - i]][counters[copy_index[(N -1) - i]]] = team_index[j + 1];  
                matches[team_index[j + 1]][counters[team_index[j + 1]]] = copy_index[(N - 1) - i];
                counters[copy_index[(N - 1) - i]]++;
                counters[team_index[j + 1]]++;
            }
        }
    }

    float distance_average = 0;
    float suma = 0;

    for(int i = 0; i < N; i++){
        for(int j = 0; j < 4; j++){
            distance_average += copy_matrix[i][matches[i][j]];
            suma += copy_matrix[i][matches[i][j]];
            if(j == 3) printf("La distancia promedio que recorre el equipo %s es: %0.2f \n", copy_name[i], (distance_average)/4);
        }
        distance_average = 0;
    }

    printf("\nLa distancia promedio que recorre el torneo es: %0.2f \n", suma/(N*4));

    output = fopen("partidos.txt", "w");

    for(int i = 0; i < N; i++){
        fprintf(output, "%s,", copy_name[i]);
    	for(int j = 0; j < 4; j++){
            if(j == 3) fprintf(output, "%s", copy_name[matches[i][j]]);
    	    else fprintf(output, "%s,", copy_name[matches[i][j]]);
    	}
    	fprintf(output, "\n");
    }
    fclose(output);

    printf("Archivo creado con exito! \n");
	return 0;
}