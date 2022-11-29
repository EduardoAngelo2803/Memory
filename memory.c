#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 1024

char* takeInput[SIZE];
char* vetorMemory[SIZE];
char* auxTake[SIZE];
char* auxRelase [10];
int countTake = 0;
int countRequest = 0;
int countProcess = 0;
int tamTotal;
int flagCountProcess;
int countFirst = 0;

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

    int auxCount = 0;

      for (int i = 0; i < tamTotal; i++) {

            if(allocation[i].num == 9999 && auxCount < list[countRequest].memory) {
                //countFirst = verProcessNum(i);
                allocation[i].num = countFirst + 1;
                strcpy(allocation[i].name, list[countRequest].name);
                //Flag to compact, add 1 without reset
                countFirst++;
                auxCount++;
            }              
        }       
    for(int i = 0; i < tamTotal; i++) {

        //printf("%s = %d\n", allocation[i].name, allocation[i].num);

    } 
}

void bestFit () {

    int auxBestFit = 0;
    int auxContador;
    int auxCount = 0;
    int flag = 0;
    int menor = 9999;
    int auxMenor;
    auxMenor = menor;

    for (int i = 0; i < tamTotal; i++) {

        if (allocation[i].num != 9999) {

            flag = 1;
        }
    }

    if(flag == 0) {

        firstFit();

    }else {

        for (int i = 0; i < tamTotal; i++)
        {

            if(allocation[i].num == 9999) {
                //Lock mutex
                auxBestFit = i;
                while (allocation[i].num == 9999)
                {
                    auxCount++;
                    i++;
                }

                if(auxCount < menor) {
                    auxMenor = auxBestFit;
                    menor = auxCount;
                }
            }
        }
        
        for (int i = auxMenor; i < list[countRequest].memory+auxMenor; i++)
        {

            if (allocation[i].num == 9999) {
                // countFirst = verProcessNum(i);
                allocation[i].num = countFirst + 1;
                strcpy(allocation[i].name, list[countRequest].name);
                // Flag to compact, add 1 without reset
                countFirst++;
                auxCount++;
            }else {

                printf("Fail\n");
            }
        }
    }
}

void worstFit () {
    /*
    int auxBestFit = 0;
    int auxContador;
    int auxCount = 0;
    int flag = 0;
    int maior = 9999;
    int auxMaior;
    auxMaior = maior;
    for (int i = 0; i < tamTotal; i++)
    {

        if (allocation[i].num != 9999)
        {

            flag = 1;
        }
    }

    if (flag == 0)
    {

        firstFit();
    }
    else
    {

        for (int i = 0; i < tamTotal; i++)
        {

            if (allocation[i].num == 9999)
            {
                // Lock mutex
                auxBestFit = i;
                while (allocation[i].num == 9999)
                {
                    auxCount++;
                    i++;
                }

                if (auxCount > maior)
                {
                    auxMaior = auxBestFit;
                    maior = auxCount;
                }
            }
        }
    
        for (int i = auxMaior; i < list[countRequest].memory + auxMaior; i++)
        {

            if (allocation[i].num == 9999)
            {
                // countFirst = verProcessNum(i);
                allocation[i].num = countFirst + 1;
                strcpy(allocation[i].name, list[countRequest].name);
                // Flag to compact, add 1 without reset
                countFirst++;
                auxCount++;
            }
            else
            {

                printf("Fail\n");
            }
        }
    }*/
}

void request () {
    
    char aux[2];    
    int auxFlag = 0;

    sscanf(vetorMemory[countTake], "%s", aux);

   

    for(int i = 0; i < countProcess; i++) {

       if(strcmp(aux, list[i].name) == 0) {

            auxFlag = 1;

       }

    }
    memset(aux, 0, sizeof(char) * 2);

    if(auxFlag != 1) {

        sscanf(vetorMemory[countTake], "%s%s%d%s", aux, list[countRequest].name, &list[countRequest].memory, list[countRequest].strategy);
    }
    memset(aux, 0, sizeof(char) * 2);

    if(strcmp(list[countRequest].strategy, "F") == 0) {
        
        if(list[countRequest].memory < tamTotal) {

            fprintf(f, "Allocate %d to %s with First fit\n", list[countRequest].memory, list[countRequest].name);
            firstFit();
        }else {

            fprintf(f, "The request of %s fail\n", list[countRequest].name);
            list[countRequest].name[0] = '\0';
            list[countRequest].memory = 0;
            list[countRequest].strategy[0] = '\0';
            flagCountProcess = 1;

        }
    }
    else if (strcmp(list[countRequest].strategy, "B") == 0)
    {

       if(list[countRequest].memory < tamTotal) {

            fprintf(f, "Allocate %d to %s with Best fit\n", list[countRequest].memory, list[countRequest].name);
            bestFit();
        }else {

            fprintf(f, "The request of %s fail\n", list[countRequest].name);
            list[countRequest].name[0] = '\0';
            list[countRequest].memory = 0;
            list[countRequest].strategy[0] = '\0';
            flagCountProcess  = 1;

        }
    }
    else if (strcmp(list[countRequest].strategy, "W") == 0)
    {

        if(list[countRequest].memory < tamTotal) {

            fprintf(f, "Allocate %d to %s with Worst fit\n", list[countRequest].memory, list[countRequest].name);
            worstFit();
        }else {

            fprintf(f, "The request of %s fail\n", list[countRequest].name);
            list[countRequest].name[0] = '\0';
            list[countRequest].memory = 0;
            list[countRequest].strategy[0] = '\0';
            flagCountProcess = 1;

        }
    }

    countRequest++;
}

void release () {
    
    int flagNoExist = 0;

    for(int i = 0; i < countProcess; i++) {      
        //Contando se o processo solicitado para release existe, na lista de processos, caso sim, acrescenta na flag, para depois verificar se existe algum ou não
        if(strcmp(list[i].name, auxRelase[countTake]) != 0) {

            flagNoExist++;
        }
    }

    if(flagNoExist >= countProcess) {
       
        fprintf(f, "Fail to release %s\n", auxRelase[countTake]);

    }else {
       // printf("%d", flagNoExist);
        fprintf(f, "Release %s\n", auxRelase[countTake]);
        //countProcess--;
    }


    for (int i = 0; i < tamTotal; i++) {

        if(allocation[i].num != 9999) {

            if (strcmp(allocation[i].name, auxRelase[countTake]) == 0) {
               
                strcpy(allocation[i].name, "Unused");
                allocation[i].num = 9999;
            }
        }
    }     

    for(int i = 0; i < countProcess; i++) {

         //Limpando o processo que sofreu release da lista de processos
        if(strcmp(list[i].name, auxRelase[countTake]) == 0) {

            list[i].name[0] = '\0';
            list[i].strategy[0] = '\0';
            list[i].memory = 0;
        }
    }
}

int verProcessName (int i) {
   
    for(int j = 0; j < countProcess; j++) {

        if(strcmp(allocation[i].name, list[j].name) == 0) {
            
            return j;
        }
    }
}

int verProcessNum (int i) {

    for(int j = 0; j < countProcess; j++) {

        if(allocation[j].num == allocation[i].num) {
            
            return j;
        }
    }

}

void stat () {
   
    int aux = 0;
    int auxUnused = 0;
    int flag = 0;
    int i = 0;
    int j = 0;
    int auxi = 0;
    int auxProcessName;

    while (i < tamTotal) {

        if(allocation[i].num != 9999) {
            //Lock 'Mutex'
            auxProcessName = verProcessName(i);
            
            while (strcmp(allocation[i].name, list[auxProcessName].name) == 0) {
                
                i++;
                auxi = i - 1;
               
            }

            fprintf(f, "Addresses [%d:%d] %s\n", aux, auxi, allocation[auxi].name);
            aux = i;
            
  
        } else {

            auxUnused = i;
            while (allocation[i].num == 9999) {
                auxUnused++;
                i++;
                auxi = i - 1;
            }
            fprintf(f, "Addresses [%d:%d] Unused\n", aux, auxUnused - 1);
            aux = i;           
        }
        flag++;
    }
 }

void compact () {

    int aux;
    int flag = 0;
    int aux2;


    int i, j, auxNum, auxDur, auxWait, auxexComp, auxlostDead, auxKilled, auxFlagKill;
    char auxName[SIZE];

    for (i = 1; i < tamTotal; i++) {

        auxNum = allocation[i].num;
        
        strcpy(auxName, allocation[i].name);

        for (j = i - 1; j >= 0 && auxNum < allocation[j].num; j--)
        {

            allocation[j + 1].num = allocation[j].num;
            strcpy(allocation[j + 1].name, allocation[j].name);
        }

        allocation[j+1].num = auxNum;
        strcpy(allocation[j + 1].name, auxName);
       
    }



    /*
    for (int i = 0; i < tamTotal; i++) {   

        if(flag == 1 && allocation[i].num != -1) {

            for (int j = aux; j < i; j++) {

                allocation[j].num = j;
                strcpy(allocation[j].name, allocation[i].name);
            }
        }

        if (allocation[i].num == -1) {

            aux = i;
            while (allocation[i].num == -1) {

                i++;
            }
        }
    }*/
    fprintf(f, "Compact Memory\n");
}

void end () {


}

void runMemory () {

    char *ptr;
    int shouldrun = 1;

    while (shouldrun == 1) {

        if(strcmp(takeInput[countTake], "X") == 0) {
            
            fprintf(f, "Exit");
            exit(EXIT_SUCCESS);
        }

        ptr = strtok(takeInput[countTake], " ");
        auxTake[countTake] = ptr;      

        if(strcmp(auxTake[countTake], "RQ") == 0) {
            //Modificar
            
            countProcess++;            
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

    for (int i = 0; i < tamTotal; i++)
    {

        allocation[i].num = 9999;
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
            printf("%d\n", strlen(takeInput[r]));   
        
            takeInput[r][strlen(takeInput[r]) - 1] = '\0';
            r++;
        }
    }
    for (int i = 0; i < r - 1; i++) {

        
        vetorMemory[i] =  strdup(takeInput[i]);
        
    }

        fclose(file);

    fprintf(f, "Total Memory %d\n", tamTotal);
    initVetor();
    runMemory();
    

    return 0;
}