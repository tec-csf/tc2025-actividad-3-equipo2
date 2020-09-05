//
//  main.c
//  Actividad 3 OS
//
//  Created by MacBook Pro on 04/09/20.
//  Copyright © 2020 Naji M A Saadat A01025599. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

typedef struct Process
{
    int id;
    int time;
    struct Process * next;
} Process;

typedef struct node
{
    int num;
    int id;
    Process * FirstProc;
    struct node * next;
} node;
void executeProcess(Process * p);
void enqueuenode(node * toAdd);
void enqueueProcess(Process * toAdd, node * g);
void PrintProcess(Process * FirstProc);
Process * dequeueProcess(node * g);
Process * createProcess(int time, int id);
node * CreateGroup(int id, int num, Process * FirstProc);
node * first;
node * dequeuenode(void);
int quantum;

int main(int argc, const char * argv[])
{
    int processCounter = 0, numProcesos = 0, tiempoProceso = 0, processnode = 0, CPUs = 0, NodeNum = 0, i = 0, j = 0;
    // User input information for Algorithm
    printf("Number of Processes : \n ");
    scanf("%d", &numProcesos);
    printf("Number of Quantum : \n ");
    scanf("%d", &quantum);
    printf("Number of CPU: \n");
    scanf("%d", &CPUs);
    printf("Number of Groups : \n");
    scanf("%d", &NodeNum);
    
    // Create node
    for(;i<NodeNum; i++)
    {
        printf("Number of processes per Group %d \n", i);
        scanf("%d", &processnode);
        while(processnode>numProcesos){
            printf("Something is wrong: Number of processes per group is more than available: %d, Input minor number of pocesses \n", numProcesos);
            scanf("%d", &processnode);
        }
        while(processCounter+processnode > numProcesos){
            printf("Something is wrong: Cannot assing this quantity to the group %d processes, input minor number of processes \n", numProcesos-(processCounter));
            scanf("%d", &processnode);
        }
        Process * FirstProc = NULL;
        node * newnode = CreateGroup(i, processnode, FirstProc);
        for(j=0; j<processnode; j++)
        {
            printf("Time of process %d \n", processCounter);
            scanf("%d", &tiempoProceso);
            Process *temp = createProcess(tiempoProceso, processCounter);
            enqueueProcess(temp, newnode);
            processCounter++;
        }
        enqueuenode(newnode);
        printf("----> node created \n");
        PrintProcess(newnode->FirstProc);
    }
    if(numProcesos>processCounter+1)
    {
        printf("Something is wrong: %d process does not have a node, try again\n", numProcesos-(processCounter+1));
        return 0;
        
    }
    node * in_execution;
    while( NodeNum > 0)
    {
        // Get 1st Queue into node
        in_execution = dequeuenode();
        int num_process_node = in_execution->num;
        printf(" ---> Executing Group ##  %d \n", in_execution->id);
        for(i=0; i<CPUs; i++)
        {
            if(num_process_node != 0)
            {
                Process * temp = dequeueProcess(in_execution);
                printf(" CPU %d: \t Executing Process ##  %d Execution Time %d  \n", i, temp->id, temp->time);
                executeProcess(temp);
                if(temp->time > 0)
                {
                    enqueueProcess(temp, in_execution);
                    printf(" Forming up: Process not finished  %d in the quantum, Remaining time; %d seconds \n\n", temp->id, temp->time);
                }else{
                    in_execution->num--;
                    free(temp);
                }
                num_process_node--;
            }
        }
        if(in_execution->FirstProc != NULL)
        {
            enqueuenode(in_execution);
            printf("*** node not finished! *** \n");
        }else
        {
            free(in_execution);
            printf("*** Process finished! *** \n");
            NodeNum--;
        }
        printf("\n");
    }
    return 0;
}
void executeProcess(Process * p)
{
    p->time -= quantum;
    sleep(quantum);
}
void enqueuenode(node * toAdd)
{
    if(first==NULL)
    {
        first=toAdd;
    }else
    {
        node * temp = first;
        while(temp->next!=NULL)
        {
            temp = temp ->next;
        }
        temp ->next = toAdd;
    }
}
void enqueueProcess(Process * toAdd, node * g){
    if(g->FirstProc == NULL)
    {
        g->FirstProc = toAdd;
    }else
    {
        Process * temp = g->FirstProc;
        while(temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = toAdd;
    }
}
node * CreateGroup(int id, int num, Process * FirstProc)
{
    node * new = (node *)malloc(sizeof(node));
    new->FirstProc = FirstProc;
    new->num = num;
    new->id = id;
    new->next = NULL;
    return new;
}
Process * createProcess(int time, int id)
{
    Process * new = (Process *)malloc(sizeof(Process));
    new->time = time;
    new->id = id;
    new->next = NULL;
    return new;
}
Process * dequeueProcess(node * g)
{
    Process *toReturn = g->FirstProc;
    g->FirstProc = g->FirstProc->next;
    toReturn->next = NULL;
    return toReturn;
}
node * dequeuenode()
{
    node *toReturn = first;
    first=first->next;
    toReturn->next=NULL;
    return toReturn;
}
void PrintProcess(Process * FirstProc)
{
    Process *temp = FirstProc;
    while(temp!=NULL){
        printf("id proceso: %d, Time needed for execution: %d \n",temp->id, temp->time);
        temp=temp->next;
    }
    printf("\n");
}
