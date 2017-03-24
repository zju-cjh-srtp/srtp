//
// Created by Wu on 2017/3/24.
//

#include <stdlib.h>
#include <stdio.h>
#include "generate.h"

/*生成一个范围在[min，max]的随机数*/
int generateRand(int max, int min){
    return rand()%(max-min+1) + min;
}

/*生成一个虚拟节点，即一个任务的其中一个子任务*/
struct vNode* initVNode(){
    struct vNode* temp = (struct vNode*)malloc(sizeof(struct vNode));
    if(temp == NULL) {
        perror("out of memory");
        return NULL;
    }
    temp->startTime = 0;
    temp->duration = generateRand(RUN_MAX,RUN_MIN);
    temp->resource[CPU] = generateRand(SF_RES_MAX,SF_RES_MIN);
    temp->resource[MEMORY] = generateRand(SF_RES_MAX,SF_RES_MIN);
    temp->resource[DISK] = generateRand(SF_RES_MAX,SF_RES_MIN);
    temp->next = NULL;
    return temp;
}

/*生成一个vList*/
struct vList initVList(){
    int length = generateRand(SF_MAX,SF_MIN);
    struct vList* list = (struct vList*)malloc(sizeof(struct vList));
    list->arriveTime = generateRand(ARRIVE_MAX,ARRIVE_MIN);
    list->deadline = list->arriveTime + generateRand(DEADLINE_MAX,DEADLINE_MIN);
    list->head = initVNode();
    struct vNode* now = list->head;
    for(int i = 1; i < length; i++){
        now->next = initVNode();
        now = now->next;
    }
    return *list;
}

/*打印一个子任务*/
void printVNode(struct vNode node, int i){
    node.resource;
    node.duration;
    node.startTime;
    printf("这是第 %d 个子任务\n",i);
    printf("其资源占有分别是 %d,%d,%d \n",node.resource[0],node.resource[1],node.resource[2]);
    printf("开始时间为 %d, 持续时间为 %d\n", node.startTime,node.duration);
}

/*打印整个任务*/
void printVList(struct vList list){
    int i = 0;
    printf("-------------------------------------------------------------------");
    printf("这个任务的到达时间是 %d, 截止时间为 %d\n",list.arriveTime,list.deadline);
    struct vNode* now = list.head;
    while(now != NULL){
        printVNode(*now,++i);
        now = now->next;
    }
}

/*释放一个vList*/
void freeVList(struct vList list){
    struct vNode* cur = list.head;
    while(cur != NULL){
        printVNode(*cur,0);
        struct vNode* temp = cur;
        cur = cur->next;
        freeVNode(temp);
    }
}

/*释放一个vNode*/
void freeVNode(struct vNode* node){
    if(node)
        free(node);
}

struct vList* initVListList(){
    int length = generateRand(SFC_MAX,SFC_MIN);
    struct vList* totalList = (struct vList*) malloc(sizeof(struct vList) * length);
    for(int i = 0; i < length; i++) totalList[i] = initVList();
    return totalList;
}



/*释放任务列表*/
int freeTaskList(){

}

/*生成一个物理机节点*/
struct pNode initPNode(){

}

