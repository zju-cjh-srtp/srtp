//
// Created by IsaccLee on 5/3/17.
//
#include <stdlib.h>
#include <stdio.h>
#include "generate.h"
void PrintPCState(struct vList *list, struct pNode** pNodeList, FILE *fp,int Time,int pNum,int tNum){//输出物理机状态
//    fprintf(fp,"TIME,PcNumber,CPU,MEMORY,DISK\n");
    int * resource = (int *)calloc(Time*pNum*3, sizeof(int));//3列的数组->一维存储
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

    for(int i = 0 ; i <Time;i++){//每次输出当前秒数下,五个机子的状态
//        printf("%d",Time);
        int t = i * pNum*3;
        fprintf(fp,"%d,%d,%d,%d,%d\n",resource[t+CPU],resource[t+3+CPU],resource[t+6+CPU],resource[t+9+CPU],resource[t+12+CPU]);
        fprintf(fp,"%d,%d,%d,%d,%d\n",resource[t+MEMORY],resource[t+3+MEMORY],resource[t+6+MEMORY],resource[t+9+MEMORY],resource[t+12+MEMORY]);
        fprintf(fp,"%d,%d,%d,%d,%d\n",resource[t+DISK],resource[t+3+DISK],resource[t+6+DISK],resource[t+9+DISK],resource[t+12+DISK]);
    }
}


int* AnalystResult(int* result,struct vList* list,struct pNode** pNodeList,int pNodeNum,int taskNum){
    int successNum = 0,pcNum = 0,usedTime = 0;
    int* pUsed = calloc(pNodeNum,sizeof(int));
    for(int i = 0; i <taskNum;i++){
        if(list[i].taskState != REJECTED){ //every success task
            successNum ++;//  succss num plus 1
            struct vNode* task = list[i].head;
            for(int j = 0; j < list[i].length ; j++){// each small task
                if(pUsed[task->hostPNodeID] == 0){ //the pcNum
                    pUsed[task->hostPNodeID] = 1;
                    pcNum++;
                }
                if(j == list[i].length - 1){ //final small task, to check the finished time
                    int t = task->startTime+task->duration;
                    if(usedTime < t) usedTime = t;
                }
                task= task->next;
            }
        }
    }
    result[0] = successNum;
    result[1] = pcNum;
    result[2] = usedTime;

    return result;

}