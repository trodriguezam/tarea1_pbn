#include <stdio.h>
#include <string.h>

int main(){
	char line[100];
    int teams[10], k = 0;
	FILE* input;
	
	/* input = fopen("entrada.txt", "r");
	salida = fopen("salida.txt", "w");
	fgets(linea, 199, input);
    fprintf(salida, "%s", linea); */

    input = fopen("equipos.txt", "r");
    
    while(fgets(line, 99, input)){
        char* value = strtok(line, ", ");
        int teamx[3];
        for(int i = 0; i<3; i++){
            // printf("%s", value);
            if (i == (int)0){
                teamx[i] = value[i];
                printf("%s", teamx[i]);
            }
            else{
                teamx[i] = value[i];
                printf("%d", (int)teamx[i]);
            }
            value = strtok(NULL, ", ");
        }
        teams[k] = teamx[k];
        k++;
    }

	printf("%d", &teams[0]);
	printf("\n");
	return 0;
}