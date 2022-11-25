#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 1024

char* takeInput[SIZE];
int countTake = 0;

typedef struct
{

    char name[10];
    int memory;
    char strategy[2];

} Process;

Process list[SIZE];

void request () {

    

}

void release () {

}

void stat () {


}

void compact () {


} 

void exit () {


}

void runMemory () {


}



int main (int argc, char* argv[]) {

    FILE *file;
    int r = 0;
    int tamTotal;

    if (argc <= 1)
    {
        printf("No arguments entered! Exiting...\n");
        exit(1);
        file = fopen(argv[1], "r");
    }
    else if (argc == 2)
    {

        printf("Problems with opening file!\n");
        exit(1);
    }
    else if (argc >= 3)
    {
        tamTotal = atoi(argv[1]);
    
        file = fopen(argv[2], "r");

        if(file == NULL) {
            printf("File no exist! Exiting...\n");
            exit(1);
        }
        while (!feof(file) && !ferror(file)) {

            takeInput[r] = malloc(sizeof *takeInput[r] * 1024);
            fgets(takeInput[r], 1024, file);
           // takeInput[r][strlen(takeInput[r]) - 1] = '\0';
            r++;
        }
    }
    printf("%d\n", tamTotal);
    printf("%s", takeInput[7]);
    return 0;
}