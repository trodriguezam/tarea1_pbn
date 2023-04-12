#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int main(){
    char line[100];
    FILE* input;
    FILE* output;

    input = fopen("equipos_corto.txt", "r");
    output = fopen("partidos.txt", "w");

    while(fgets(line, 99, input)){
        char* elements = strtok(line, ",");

        if(elements != NULL){
            while(elements != NULL){
                fprintf(output, "%s\n", elements);
                elements = strtok(NULL, ",");
            }
        }
    }
    
    return 0;
}