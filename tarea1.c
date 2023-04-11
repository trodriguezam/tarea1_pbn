#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

float distance(float x1, float x2, float y1, float y2){
    return sqrt(pow((x2 - x1), 2) + pow((y2 - y1), 2));
}

void bubble_sort(float values[], char **names, int n){
    int sorted = 1;

    for(int curr = 0; curr < n - 1; curr++){
        if(values[curr] > values[curr + 1]){
            char naux[25];

            float vaux = values[curr];
            strcpy(naux, names[curr]);
            

            values[curr] = values[curr + 1];
            strcpy(names[curr], names[curr + 1]);

            values[curr + 1] = vaux;
            strcpy(names[curr + 1], naux);
            
            sorted = 0;
        }
    }

    if(sorted == 0) bubble_sort(values, names, n);
}

int main(){
    char line[100];
    char *team_names[500];
    float teams[20][2], matrix[20][20], daverage[20];
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
    bubble_sort(daverage, team_names, n);
    
    printf("\n");
    for(int i = 0; i < 20; i++) printf("%i) %s: \n%f\n\n", i+1, team_names[i], daverage[i]);

	return 0;
}
