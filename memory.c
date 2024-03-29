#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 10240

char *takeInput[SIZE];
char *vetorMemory[SIZE];
char *auxTake[SIZE];
char *auxRelase[10];
int countTake = 0;
int countRequest = 0;
int countProcess = 0;
int tamTotal;
int flagCountProcess;
int countFirst = 0;
int flagMemory;
int countSpaces = 0;
int auxFirst = 0;
int flagFirst = 0, flagBest = 0, flagWorst = 0;
int auxCountMemory = 0;
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

void firstFit() {

    int auxCount = 0;
    int i = 0;
    int flag = 0;
    int auxI = 0;

    while(i < tamTotal) {

        if(allocation[i].num == 99999) {
            int auxAllocF = i;
            auxI = i;
            while (allocation[i].num == 99999) {

                i++;
                auxFirst++;
            } 
            
            if(list[countRequest].memory <= auxFirst) {
                
                while(auxCount < list[countRequest].memory) {
                    
                    allocation[auxI].num = auxAllocF + 1;
                    strcpy(allocation[auxI].name, list[countRequest].name);
                    countFirst++;
                    auxCount++;  
                    auxI++;
                    auxAllocF++;
                }
                flag = 1 ;

            }
            if(flag == 1) {
                break;
            }
        }
        i++;
    }
    if(flag == 0) {

        flagFirst = 1;
               
    }
    auxFirst = 0;
}

void bestFit() {

    int auxBestFit = 0;
    int auxContador;
    int auxCount = 0;
    int flag = 0;
    int menor = 99999;
    int flagBestFit = 0;
    int auxMenor;
    auxMenor = menor;
    int i = 0;

    for (int i = 0; i < tamTotal; i++) {

        if (allocation[i].num != 99999) {

            flag = 1;
        }
    }
   
    if (flag == 0) {

        firstFit();

    } else {

        while(i < tamTotal) {
            
            if (allocation[i].num == 99999) {
                // Lock mutex
                auxBestFit = i;

                while (allocation[i].num == 99999) {
                    auxCount++;
                    i++;
                }
            
                if (auxCount < menor && list[countRequest].memory <= auxCount) {

                    auxMenor = auxBestFit;
                    menor = auxCount;
                    flagBestFit = 1;
                }

            }else {

                i++;
            }
            auxCount = 0;
        }
        if(flagBestFit == 0) {

            flagBest = 1;

        }else {
            int auxAllocB = auxMenor;
            for (int i = auxMenor; i < list[countRequest].memory + auxMenor; i++) {

                if (allocation[i].num == 99999) {
                    
                    allocation[i].num = auxAllocB + 1;
                    strcpy(allocation[i].name, list[countRequest].name);
                    // Flag to compact, add 1 without reset
                    countFirst++;
                    auxCount++;
                    auxAllocB++;
                }          
            }
        }
    }
     
}

void worstFit() {

    int auxWorstFit = 0;
    int auxContador;
    int auxCount = 0;
    int flag = 0;
    int maior = 0;
    int flagWorstFit = 0;
    int auxMaior;
    auxMaior = maior;
    int i = 0;

    for (int i = 0; i < tamTotal; i++) {

        if (allocation[i].num != 99999) {

            flag = 1;
        }
    }
   
    if (flag == 0) {

        firstFit();

    } else {

        while(i < tamTotal) {
            
            if (allocation[i].num == 99999) {
                // Lock mutex
                auxWorstFit = i;

                while (allocation[i].num == 99999) {
                    auxCount++;
                    i++;
                }
            
                if (auxCount > maior && list[countRequest].memory <= auxCount) {

                    auxMaior = auxWorstFit;
                    maior = auxCount;
                    flagWorstFit = 1;
                }

            }else {

                i++;
            }
            auxCount = 0;
        }
        if(flagWorstFit == 0) {

            flagWorst = 1;

        }else {
            int auxAllocW = auxMaior;
            for (int i = auxMaior; i < list[countRequest].memory + auxMaior; i++) {

                if (allocation[i].num == 99999) {
                    
                    allocation[i].num = auxAllocW + 1;
                    strcpy(allocation[i].name, list[countRequest].name);
                    // Flag to compact, add 1 without reset
                    countFirst++;
                    auxCount++;
                    auxAllocW++;
                }          
            }
        }
    }
}

void request() {

    char aux[20];
    sscanf(vetorMemory[countTake], "%s%s%d%s", aux, list[countRequest].name, &list[countRequest].memory, list[countRequest].strategy);
    
    memset(aux, 0, sizeof(char) * 2);
   
    if(list[countRequest].memory > tamTotal) {
        
        fprintf(f, "The request of %s fail\n", list[countRequest].name);
        list[countRequest].name[0] = '\0';
        list[countRequest].memory = 0;
        list[countRequest].strategy[0] = '\0';
        flagCountProcess = 1;
        

    } else {

        if (strcmp(list[countRequest].strategy, "F") == 0) {

            firstFit();

            if (list[countRequest].memory < tamTotal && flagFirst != 1) {

                fprintf(f, "Allocate %d to %s with First Fit\n", list[countRequest].memory, list[countRequest].name);       
                countProcess++;
                auxCountMemory += list[countRequest].memory;
           
                
            }else {
                
                fprintf(f, "The request of %s fail\n", list[countRequest].name);
                list[countRequest].name[0] = '\0';
                list[countRequest].memory = 0;
                list[countRequest].strategy[0] = '\0';
                flagCountProcess = 1;
            }

        }else if (strcmp(list[countRequest].strategy, "B") == 0) {

            bestFit();

            if (list[countRequest].memory < tamTotal && flagBest != 1) {

                fprintf(f, "Allocate %d to %s with Best Fit\n", list[countRequest].memory, list[countRequest].name);
                countProcess++;
                auxCountMemory += list[countRequest].memory;

            } else {

                fprintf(f, "The request of %s fail\n", list[countRequest].name);
                list[countRequest].name[0] = '\0';
                list[countRequest].memory = 0;
                list[countRequest].strategy[0] = '\0';
                flagCountProcess = 1;
            }

        } else if (strcmp(list[countRequest].strategy, "W") == 0) {

            worstFit();
           
            if (list[countRequest].memory < tamTotal && flagWorst != 1) {

                fprintf(f, "Allocate %d to %s with Worst Fit\n", list[countRequest].memory, list[countRequest].name);
                countProcess++;
                auxCountMemory += list[countRequest].memory;

            } else {

                fprintf(f, "The request of %s fail\n", list[countRequest].name);
                list[countRequest].name[0] = '\0';
                list[countRequest].memory = 0;
                list[countRequest].strategy[0] = '\0';
                flagCountProcess = 1;
            }
        }
    }
    countSpaces = 0;
    countRequest++;
}

void release() {

    int flagNoExist = 0;

    for (int i = 0; i < countProcess; i++) {

        // Contando se o processo solicitado para release existe, na lista de processos, caso sim, acrescenta na flag, para depois verificar se existe algum ou não
        if (strcmp(list[i].name, auxRelase[countTake]) != 0) {

            flagNoExist++;
        }
    }

    if (flagNoExist >= countProcess) {

        fprintf(f, "Fail to release %s\n", auxRelase[countTake]);

    } else {
       
        fprintf(f, "Release %s\n", auxRelase[countTake]);
        auxCountMemory -= list[countTake].memory;
    }

    for (int i = 0; i < tamTotal; i++) {

        if (allocation[i].num != 99999) {

            if (strcmp(allocation[i].name, auxRelase[countTake]) == 0) {

                strcpy(allocation[i].name, "Unused");
                allocation[i].num = 99999;
            }
        }
    }

    for (int i = 0; i < countProcess; i++) {

        // Limpando o processo que sofreu release da lista de processos
        if (strcmp(list[i].name, auxRelase[countTake]) == 0) {
            list[i].name[0] = '\0';
            list[i].strategy[0] = '\0';
            list[i].memory = 0;
        }
    }
}

int verProcessName(int i) {

    for (int j = 0; j < countProcess; j++) {

        if (strcmp(allocation[i].name, list[j].name) == 0) {

            return j;
        }
    }
}

int verProcessNum(int i)
{

    for (int j = 0; j < countProcess; j++)
    {

        if (allocation[j].num == allocation[i].num)
        {

            return j;
        }
    }
}

void verSpaces() {

    for (int i = 0; i < tamTotal; i++) {

        if(allocation[i].num == 99999) {

            countSpaces++;
        }
    }    
}

void stat() {

    int aux = 0;
    int auxUnused = 0;
    int flag = 0;
    int i = 0;
    int j = 0;
    int auxi = 0;
    int auxflagStat = 0;
    int auxProcessName;

    while (i < tamTotal && flag < 99) {

        if (allocation[i].num != 99999) {
            // Lock 'Mutex'
            auxProcessName = verProcessName(i);

            while (strcmp(allocation[i].name, list[auxProcessName].name) == 0) {

                i++;
                auxflagStat = 1;
            }
            auxi = i - 1;
            fprintf(f, "Addresses [%d:%d] %s\n", aux, auxi, allocation[auxi].name);
            aux = i;
            

        } else {

            auxUnused = i;
            while (allocation[i].num == 99999) {
                auxUnused++;
                i++;
                auxi = i - 1;
                auxflagStat = 1;
            }
            fprintf(f, "Addresses [%d:%d] Unused\n", aux, auxUnused - 1);
            aux = i;
            
        }
        flag++;
        if(auxflagStat != 1) {
            i++;
        }
        auxflagStat = 0;
    }
}

void compact() {

    int aux2;
    int i, j, auxNum;
    char auxName[SIZE];
    
    for (i = 1; i < tamTotal; i++) {

        auxNum = allocation[i].num;
        strcpy(auxName, allocation[i].name);

        for (j = i - 1; j >= 0 && auxNum < allocation[j].num; j--) {
            
            allocation[j + 1].num = allocation[j].num;
            strcpy(allocation[j + 1].name, allocation[j].name);
        }

        allocation[j + 1].num = auxNum;
        strcpy(allocation[j + 1].name, auxName);
    }

    fprintf(f, "Compact Memory\n");
}

void end()
{
}

void runMemory() {

    char *ptr;
    int shouldrun = 1;
  
    while (shouldrun == 1) {

        if (strcmp(takeInput[countTake], "X") == 0) {

            fprintf(f, "Exit");
            exit(EXIT_SUCCESS);
        }

        ptr = strtok(takeInput[countTake], " ");
        auxTake[countTake] = ptr;

        if (strcmp(auxTake[countTake], "RQ") == 0) {
            
            request();

        } else if (strcmp(auxTake[countTake], "RL") == 0) {

            while (ptr != NULL) {

                auxRelase[countTake] = ptr;
                ptr = strtok(NULL, " ");
            }

            release();

        } else if (strcmp(auxTake[countTake], "STAT") == 0) {

            stat();

        } else if (strcmp(auxTake[countTake], "C") == 0) {

            compact();
        }
        countTake++;
    }
}

void initVetor() {

    for (int i = 0; i < tamTotal; i++) {

        allocation[i].num = 99999;
    }
}

int main(int argc, char *argv[]) {

    FILE *file;
    char *auxCountLines[SIZE];
    int r = 0;
    char *ptr;
    char *str = {"X"};
    int countLines = 0;
    int t;
    f = fopen("memory_leam.out", "w");

    if (argc <= 1) {

        printf("No Arguments entered! Exiting...\n");
        exit(0);
        file = fopen(argv[1], "r");

    } else if (argc == 2) {

        if(sscanf(argv[1], "%d", &t) != 1) {

            printf("Input an Integer before ./memory!\n");

        }else {

            printf("Problems with opening file!\n");
        }
        
        exit(0);

    } else if  (argc > 3) {

        printf("Many arguments entered! Please input only 3!\n");
        exit(0);

    }else if (argc == 3) {

        if(sscanf(argv[1], "%d", &t) != 1) {

            printf("Please input an Integer before ./memory!\n");
            exit(0);

        }

        tamTotal = atoi(argv[1]);

        file = fopen(argv[2], "r");

        if (file == NULL) {

            printf("File no exist! Exiting...\n");
            exit(0);
        }

        while (!feof(file) && !ferror(file)) {

            auxCountLines[countLines] = malloc(sizeof *auxCountLines[countLines] * 1024);
            fgets(auxCountLines[countLines], 1024, file);
            countLines++;
        }
        
        fclose(file);

        file = fopen(argv[2], "r");

        while (!feof(file) && !ferror(file)) {

            takeInput[r] = malloc(sizeof *takeInput[r] * 1024);
            fgets(takeInput[r], 1024, file);

            if (r == (countLines - 1)) {
                
               if (strlen(takeInput[r]) > 1) {

                   takeInput[r] = strtok(takeInput[r], " ");
                  
                }
                r++;
                break;

            } else {

                takeInput[r][strlen(takeInput[r]) - 1] = '\0';
                r++;
            }           
        }       
    }

    for (int i = 0; i < r - 1; i++) {

        if(strcmp(takeInput[i], "\0") != 0) {

            vetorMemory[i] = strdup(takeInput[i]);
            
        }
    }

    fclose(file);
    
    fprintf(f, "Total Memory %d\n", tamTotal);
    initVetor();
    runMemory();

    return 0;
}