//
// Created by IsaccLee on 5/3/17.
//
#include <stdlib.h>
#include <stdio.h>
#include "generate.h"
void PrintPCState(struct vList *list, struct pNode** pNodeList, FILE *fp,int Time,int pNum,int tNum){
//    fprintf(fp,"TIME,PcNumber,CPU,MEMORY,DISK\n");
    int * resource = (int *)calloc(Time*pNum*3, sizeof(int));
    for(int i = 0; i < tNum; i++){// task

        if(list[i].taskState != REJECTED ){//only finished task will matter
            struct vNode* task = list[i].head;
            for(int j = 0; j < list[i].length ; j++){// each small task
                for(int k = 0; k < task->duration; k++){//duration adds
                    int temp = ((k+task->startTime)*pNum+task->hostPNodeID)*3;//the horizon coordinate
//                    printf("%d,%d,%d\n",task->resource[CPU],task->resource[MEMORY],task->resource[DISK]);
                    resource[temp + CPU] += task->resource[CPU];
                    resource[temp + MEMORY] += task->resource[MEMORY];
                    resource[temp + DISK] += task->resource[DISK];
//                    printf("%d,%d,%d\n",resource[temp+CPU],resource[temp+MEMORY],resource[temp+DISK]);

                }
                task= task->next;
            }
        }
    }

    for(int i = 0 ; i <Time;i++){
        printf("%d",Time);
        int t = i * pNum*3;
        fprintf(fp,"%d,%d,%d,%d,%d\n",resource[t+CPU],resource[t+3+CPU],resource[t+6+CPU],resource[t+9+CPU],resource[t+12+CPU]);
        fprintf(fp,"%d,%d,%d,%d,%d\n",resource[t+MEMORY],resource[t+3+MEMORY],resource[t+6+MEMORY],resource[t+9+MEMORY],resource[t+12+MEMORY]);
        fprintf(fp,"%d,%d,%d,%d,%d\n",resource[t+DISK],resource[t+3+DISK],resource[t+6+DISK],resource[t+9+DISK],resource[t+12+DISK]);
    }
}
