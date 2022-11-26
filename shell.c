#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 1024

char* takeInput[SIZE];
char* vetorMemory[SIZE];
char* auxTake[SIZE];
int countTake = 0;
int countRequest = 0;

typedef struct
{

    char name[10];
    int memory;
    char strategy[2];

} Process;

Process list[SIZE];

void request () {
 
    char aux[2];
    sscanf(vetorMemory[countRequest], "%s%s%d%s", aux, list[countRequest].name, &list[countRequest].memory, list[countRequest].strategy);
    printf("%s %d %s\n", list[countRequest].name, list[countRequest].memory, list[countRequest].strategy);
    countRequest++;
    memset(aux, 0, sizeof(char) * 2);
}

void release () {

}

void stat () {


}

void compact () {


} 

void end () {


}

void runMemory () {

    char *ptr;
    int shouldrun = 1;

    while (shouldrun == 1) {

        if(strcmp(takeInput[countTake], "X") == 0) {
            printf("exiting...\n");
            exit(EXIT_SUCCESS);
        }

        ptr = strtok(takeInput[countTake], " ");
        auxTake[countTake] = ptr;      

        if(strcmp(auxTake[countTake], "RQ") == 0) {
           
            request();
        } else if (strcmp(auxTake[countTake], "RL") == 0) {
           
            release();
        } else if (strcmp(auxTake[countTake], "STAT") == 0) {
            
            stat();
        } else if (strcmp(auxTake[countTake], "C") == 0) {
            
            compact();
        }

        countTake++;
    }
}

int main (int argc, char* argv[]) {

    FILE *file;
    int r = 0;
    int tamTotal;

    if (argc <= 1)
    {
        printf("No takeInput entered! Exiting...\n");
        exit(0);
        file = fopen(argv[1], "r");
    }
    else if (argc == 2)
    {

        printf("Problems with opening file!\n");
        exit(0);
    }
    else if (argc >= 3)
    {
        tamTotal = atoi(argv[1]);
    
        file = fopen(argv[2], "r");

        if(file == NULL) {
            printf("File no exist! Exiting...\n");
            exit(0);
        }
        while (!feof(file) && !ferror(file)) {

            takeInput[r] = malloc(sizeof *takeInput[r] * 1024);        
            fgets(takeInput[r], 1024, file);
            takeInput[r][strlen(takeInput[r]) - 1] = '\0';
            r++;
        }
    }
    for (int i = 0; i < r - 1; i++) {

        vetorMemory[i] =  strdup(takeInput[i]);
        
    }
        fclose(file);
 
    runMemory();
   

    return 0;
}