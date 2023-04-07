#include <stdio.h>
#include <string.h>
#include <math.h>

int distance(int x1, int x2, int y1, int y2){
    return sqrt(pow((x2 - x1), 2) + pow((y2 - y1), 2));
}

int main(){
	char line[100];
    float teams[20][2];
    int k = 0;
	FILE* input;
    FILE* output;
	
	/* input = fopen("entrada.txt", "r");
	salida = fopen("salida.txt", "w");
	fgets(linea, 199, input);
    fprintf(salida, "%s", linea); */
    // printf("test1 ");
    input = fopen("equipos_corto.txt", "r");
    output = fopen("partidos.txt", "w");
    // printf("test2 ");
    
    while(fgets(line, 99, input)){
        // printf("test3 ");
        char* value = strtok(line, ",");
        char* teamx;
        float x;
        float y;
        for(int i = 0; i<3; i++){
            // printf("test4 ");
            // printf("%s", value);
            if (i == 0){
                // printf("test5 ");
                // printf("%s\n", value);
                teamx = value;
                printf("%s\n", teamx);
            }
            else if(i == 1){
                // printf("test6 ");
                x = atof(value);
                printf("%f\n", x);
            }
            else if(i == 2){
                // printf("test6 ");
                y = atof(value);
                printf("%f\n", y);
            }
            value = strtok(NULL, ",");
        }
        teams[k][0] = x;
        teams[k][1] = y;
        // teams[k] = teamx[k];
        k++;
    }
    fclose(input);
    fclose(output);
    for(int j = 0; j<20; j++){
        for(int i = 0; i<2; i++){
            printf("%f, ", teams[j][i]);
        }
        printf("\n");
    }
	return 0;
}