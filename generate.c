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
    printf("这是第 %d 个子任务\n",i);
    printf("其资源占有分别是 %d,%d,%d \n",node.resource[0],node.resource[1],node.resource[2]);
    printf("开始时间为 %d, 持续时间为 %d\n", node.startTime,node.duration);
}

/*打印整个任务*/
void printVList(struct vList list){
    int i = 0;
    printf("-------------------------------------------------------------------\n");
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
//        printVNode(*cur,0);
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

/*创建任务的列表，每一个任务是一条子任务链*/
struct vList* initVListList(int taskNum){
    struct vList* totalList = (struct vList*) malloc(sizeof(struct vList) * taskNum);
    for(int i = 0; i < taskNum; i++) totalList[i] = initVList();
    return totalList;
}



/*释放任务列表*/
void freeTaskList(int taskNum, struct vList* list){
    for(int i = 0; i < taskNum; i++){
        freeVList(list[i]);
    }
    free(list);
}

/*生成一个物理机节点*/
struct pNode* initPNode(){
    struct pNode* temp = (struct pNode*)malloc(sizeof(struct pNode));
    if(temp == NULL) {
        perror("out of memory");
        return NULL;
    }
    temp->totalResource[CPU] = generateRand(PN_RES_MAX,PN_RES_MIN);
    temp->totalResource[MEMORY] = generateRand(PN_RES_MAX,PN_RES_MIN);
    temp->totalResource[DISK] = generateRand(PN_RES_MAX,PN_RES_MIN);
    temp->load[CPU] = 0;
    temp->load[MEMORY] = 0;
    temp->load[DISK] = 0;
    return temp;
}

/*打印一个物理机*/
void printPNode(struct pNode node, int i){

    printf("这是第 %d 个物理机\n",i);
    printf("其资源总量分别是 %d,%d,%d \n",node.totalResource[0],node.totalResource[1],node.totalResource[2]);
    printf("其资源被用量分别是 %d,%d,%d \n",node.load[0],node.load[1],node.load[2]);
}

/*释放一个物理机节点*/
void freePNode(struct pNode* node){
    if(node)
        free(node);
}


/*创建一个物理机列表*/
struct pNode** initPNodeList(int pNodeNum){
    struct pNode** pNodeList = (struct pNode**) malloc(sizeof(struct pNode*) * pNodeNum);
    for(int i = 0; i < pNodeNum; i++) pNodeList[i] = initPNode();
    return pNodeList;
}

/*打印一个物理机列表*/
void printPNodeList(struct pNode** list, int pNodeNum){
    for(int i = 0; i < pNodeNum; i++){
        printPNode(*list[i],i);
    }
}

/*释放所有物理机，即物理机列表*/
void freePNodeList(struct pNode** list, int pNodeNum){
    for(int i = 0; i < pNodeNum; i++){
        freePNode(list[i]);
    }
    free(list);
}

/*初始化所有物理机之间的距离*/
void initDis(int pNodeNum , int dis[][pNodeNum]){
    for(int i = 0; i < pNodeNum; i++)
        for(int j = 0; j < pNodeNum; j++)
            dis[i][j] = generateRand(DISTANCE_MAX,DISTANCE_MIN);
}