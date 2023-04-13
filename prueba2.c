#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


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

void copy(){}

int main(){
    char line[100];
    char *team_names[500];
    char *copy_name[500];
    float teams[20][2], matrix[20][20], daverage[20];
    int matches[20][4];
    int counters[20] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    int team_index[20] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19};
    int copy_index[20] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19};
    int k = 0;
    FILE *input;
    FILE *output;
	
    input = fopen("equipos_corto.txt", "r");
    output = fopen("partidos.txt", "w");

    while(fgets(line, 100, input)){
        char *value = strtok(line, ",");
        float x;
        float y;
        for(int i = 0; i<3; i++){
            if (i == 0) {
                team_names[k] = malloc(strlen(value) + 1);
                strcpy(team_names[k], value);
                }
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
    for(int row = 0; row < 20; row++){
        for(int col = 0; col < 20; col++){
                matrix[row][col] = distance(teams[row][0], teams[col][0], teams[row][1], teams[col][1]);
        }
    }
    printf("\n");
    
    // Avg distance from teamx to each team
    for(int i = 0; i < 20; i++){
        float sum = 0;
        for(int k = 0; k < 20; k++){
            sum += matrix[i][k];
        }
        daverage[i] = sum/19;
    }

    int n = sizeof(daverage) / sizeof(daverage[0]);

    for(int i = 0; i < n; i++) {
        copy_name[i] = team_names[i];
    }

    bubble_sort(daverage, team_names, team_index, n);  //Bubble sort, ordena las distancias promedio

    for(int i = 0; i < n; i++) {
        copy_index[i] = team_index[i];
        printf("%d ", copy_index[i]);
    }


    // for(int i = 0; i < 20; i++){
    //     printf("%d : %0.1f \n", team_index[i] + 1, daverage[i]);
    // }

    for(int i = 0; i < n; i++) {
        for(int a = 0; a < n; a++){
            team_index[a] = a;
        }
        bubble_sort(matrix[copy_index[19 - i]], team_names, team_index, n);   //copy_index[19] => 14
        for (int j = 0; j < 20; j++){
            // printf("%d /", counters[team_index[j]]);
            if (((counters[copy_index[19 - i]] < 4) && (counters[team_index[j + 1]] < 4))){
                matches[copy_index[19 - i]][counters[copy_index[19 - i]]] = team_index[j + 1];      //(int)copy_index[19 - 1] es un numero
                matches[team_index[j + 1]][counters[team_index[j + 1]]] = copy_index[19 - i];
                counters[copy_index[19 - i]]++;
                counters[team_index[j + 1]]++;
            }
        }
    }

    printf("\n");
    for(int i = 0; i < 20; i++) printf("%i) %s: %0.1f\n\n", team_index[i] + 1, team_names[i], daverage[i]);

    for(int i = 0; i < 20; i++){
        for(int j = 0; j < 4; j++){
            printf("%d  ", matches[i][j]);
        }
        printf("\n");
    }

    for(int i = 0; i < 20; i++){
    printf("%d \n", counters[i]);
    }

	return 0;
}