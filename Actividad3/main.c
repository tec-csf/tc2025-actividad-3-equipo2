//  Actividad 3 Administración de un SO
//  main.c
//  AvanzadaCubells
//
//  Created by Naji M A Saadat A01025599 on 1/09/20.
//  Copyright B) 2020 Naji M A Saadat A01025599. All rights reserved.
//
//

#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int id;
    int parent;
    int clock;
}
Subprocess;

typedef struct Node
{
    Subprocess * s;
    struct Node * next;
}
Node_t;

int counter = 0;
Node_t *head = NULL;

void enqueueRR(int id, int parent, int clock)
{
    Node_t *current = head;

    if (counter == 0)
    {
        Subprocess *subprocess = (Subprocess*) malloc(sizeof(Subprocess));
        subprocess->id = id;
        subprocess->clock = clock;
        subprocess->parent = parent;
        head->s = subprocess;
    }
    else
    {
        while (current->next != NULL)
        {
            current = current->next;
        }
        current->next = malloc(sizeof(Node_t));
        Subprocess *subprocess = (Subprocess*) malloc(sizeof(Subprocess));
        subprocess->id = id;
        subprocess->parent = parent;
        subprocess->clock = clock;
        current->next->s = subprocess;
        current->next->next = NULL;
    }
    ++counter;
}

Subprocess* DequeueRR()
{
    Subprocess * returnValue;
    if (counter == 1)
    {
        returnValue = head->s;
    }
    else
    {
        Node_t *nextProcess = head->next;
        returnValue = head->s;
        free(head->s);
        free(head);
        head = nextProcess;
    }
    --counter;
    return returnValue;
}

int main(int argc, char *argv[])
{
    head = malloc(sizeof(Node_t));
    head->next = NULL;
    int numProcess = 0;
    int numSubProcess = 0;
    int finalSubProcess = 0;
    int countSubProcess = 0;
    int cpus = 0;
    int idle = 0;

    printf("CPUs Number: ");
    scanf("%d", &cpus);
    printf("\n");
    printf(" # Process Number: ");
    scanf("%d", &numProcess);
    printf("\n");
    int *array = malloc(sizeof(int) *numProcess);
    int *final = array + numProcess;
    int *i = array;
    int j = 1;

    while ((i < final) && (j <= numProcess))
    {
        printf(" # Subprocess in %d NoProcess: ", j);
        scanf("%d", &numSubProcess);
        printf("\n");
        finalSubProcess += numSubProcess;
        *i = finalSubProcess;
        ++i;
        ++j;
    }
    int a = 0;
    int k = 0;
    i = array;
    j = 1;

    while (a < finalSubProcess)
    {
        if (k == *i)
        {
            countSubProcess = 1;
            ++i;
            ++j;
            ++k;
        }
        else
        { ++countSubProcess;
            ++k;
        }
        printf("Time of execution of subprocess %d-%d: ", j, countSubProcess);
        scanf("%d", &idle);

        printf("Queuing to Round Robin \n");
        printf("\n");
        enqueueRR(countSubProcess, j, idle);
        ++a;
    }
    free(array);
    return 0;
}
