#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 1024

char* takeInput[SIZE];
char* vetorMemory[SIZE];
char* auxTake[SIZE];
int countTake = 0;
int countRequest = 0;
int countProcess = 0;
int tamTotal;

FILE *f;

typedef struct {

    char name[10];
    int num;

} AlocMemory;


typedef struct {

    char name[10];
    int memory;
    char strategy[2];

} Process;

Process list[SIZE];
AlocMemory allocation[SIZE];

void firstFit () {

    int countFirst = 0;

    for (int i = 0; i < tamTotal; i++) {

        allocation[i].num = -1;
    }

        for (int j = 0; j < countProcess; j++)
        {

            for (int i = 0; i < list[j].memory; i++)
            {

                allocation[countFirst].num = countFirst + 1;
                strcpy(allocation[countFirst].name, list[j].name);
                countFirst++;
               
            }
        }

        for (int i = 0; i < tamTotal; i++)
        {
           
            if (allocation[i].num == -1)
            {

                strcpy(allocation[i].name, "Unused");
            }
        }        
}

void bestFit () {




}

void worstFit () {


}

void request () {

    
    char aux[2];
    sscanf(vetorMemory[countRequest], "%s%s%d%s", aux, list[countRequest].name, &list[countRequest].memory, list[countRequest].strategy);
    printf("%s %d %s\n", list[countRequest].name, list[countRequest].memory, list[countRequest].strategy);
    
    memset(aux, 0, sizeof(char) * 2);

    if(strcmp(list[countRequest].strategy, "F") == 0) {

        fprintf(f, "Allocate %d to %s with First fit\n", list[countRequest].memory, list[countRequest].name);

    }else if (strcmp(list[countRequest].strategy, "B") == 0) {

        fprintf(f, "Allocate %d to %s with Best fit\n", list[countRequest].memory, list[countRequest].name);

    }else if (strcmp(list[countRequest].strategy, "W") == 0){

        fprintf(f, "Allocate %d to %s with Worst fit\n", list[countRequest].memory, list[countRequest].name);
    }

    countRequest++;
}

void release () {

}

void stat () {

    int aux = 0;
    int auxUnused = 0;
    int flag = 0;
  /*  for (int j = 0; j < countProcess; j++)
    {

        for (int i = aux; i < tamTotal; i++) {
           
            if(allocation[i].num != -1 && flag == 0) {

                printf("Addresses [%d:%d] %s\n",  aux, aux+list[j].memory -1, list[j].name);
                aux += list[j].memory;
                flag = 1;
                
            }else if(flag == 0) {

                while(allocation[i].num == -1) {
                    auxUnused++;
                }
                printf("Adresses [%d:%d] Unused\n", aux, auxUnused);
            }
        }
        flag = 0;
    }*/
    int i = 0;
    int j = 0;
    while (i < tamTotal)
    {

        if(allocation[i].num != -1) {

            //Lock 'Mutex'
            while (strcmp(allocation[i].name, list[j].name) == 0) {
                i++;

            }
            fprintf(f, "Addresses [%d:%d] %s\n", aux, i-1, list[j].name);
            aux = i;
            
            j++;
        }
        else
        {
            auxUnused = i;
            while (allocation[i].num == -1)
            {
                auxUnused++;
                i++;
            }
            fprintf(f, "Addresses [%d:%d] Unused\n", aux, auxUnused-1);
            aux += i;
        }
        flag++;
    }
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
            fprintf(f, "Exit\n");
            exit(EXIT_SUCCESS);
        }

        ptr = strtok(takeInput[countTake], " ");
        auxTake[countTake] = ptr;      

        if(strcmp(auxTake[countTake], "RQ") == 0) {
            countProcess++;
            
            request();
        } else if (strcmp(auxTake[countTake], "RL") == 0) {
           
            release();
        } else if (strcmp(auxTake[countTake], "STAT") == 0) {
            firstFit();
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
    f = fopen("memory_leam.out", "w");

    if (argc <= 1)
    {
        printf("No Arguments entered! Exiting...\n");
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

    fprintf(f, "Total Memory %d\n", tamTotal);
    runMemory();

    return 0;
}