//
// Created by Wu on 2017/3/24.
//




#include "generate.h"

/*生成一个范围在[min，max]的随机数*/
int generateRand(int max, int min){
    return rand()%(max-min+1) + min;
}

/*生成一个虚拟节点，即一个任务的其中一个子任务*/
struct vNode* initVNode(){
    struct vNode* temp = (struct vNode*)malloc(sizeof(struct vNode));
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
    list->deadline = generateRand(DEADLINE_MAX,DEADLINE_MIN);
    list->head = *initVNode();
    struct vNode* now = &list->head;
    for(int i = 1; i < length; i++){
        now->next = initVNode();
        now = now->next;
    }
    return *list;
}

void printVNode(struct vNode node, int i){
    node.resource;
    node.duration;
    node.startTime;
    printf("这是第 %d 个子任务\n",i);
    printf("其资源占有分别是 %d,%d,%d \n",node.resource[0],node.resource[1],node.resource[2]);
    printf("开始时间为 %d, 持续时间为 %d\n", node.startTime,node.duration);
}

void printVList(struct vList list){
    int i = 0;
    printf("这个任务的到达时间是 %d, 截止时间为 %d\n",list.arriveTime,list.deadline);
    struct vNode* now = &list.head;
    while(now != NULL){
        printVNode(*now,++i);
        now = now->next;
    }
}

/*释放一个vList*/
int freeVList(){

}

/*生成任务列表*/
struct vList* initTaskList(){

}

/*释放任务列表*/
int freeTaskList(){

}

/*生成一个物理机节点*/
struct pNode initPNode(){

}

