//
// Created by Wu on 2017/3/24.
//
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#ifndef SRTP_GENERATE_H
#define SRTP_GENERATE_H

/*PN资源参数*/
#define PN_RES_MAX 50
#define PN_RES_MIN 25

/*PN数量参数*/
#define PN_MAX 30
#define PN_MIN 30

/*PN距离参数*/
#define DISTANCE_MAX 20
#define DISTANCE_MIN 1

/*SFC数量参数*/
#define SFC_MAX 1500
#define SFC_MIN 1500

/*SFC中SF数量参数*/
#define SF_MAX 10
#define SF_MIN 5

/*SFC到达时间参数*/
#define ARRIVE_MAX 1000
#define ARRIVE_MIN 0

/*SFC截止时间参数*/
#define DEADLINE_MAX 1000
#define DEADLINE_MIN 0

/*SF运行时间参数*/
#define RUN_MAX 30
#define RUN_MIN 15

/*SF资源参数*/
#define SF_RES_MAX 10
#define SF_RES_MIN 7

/*资源种类*/
#define CPU 0
#define MEMORY 1
#define DISK 2


/*虚拟机，任务链中的子任务*/
struct vNode{
    int resource[3];//三种类型资源
    int startTime;//开始时间
    int duration;//持续时间
    struct vNode* next;//下一个子任务
};

struct vList{
    int arriveTime;
    int deadline;
    struct vNode head;
};




/*物理机*/
struct pNode{
    int totalResource[3];//三种类型资源共有多少
    int load[3];//三种类型资源已经被占用了多少
//    struct vNode* next;//下一个子任务

};

int generateRand(int max, int min);

struct vNode* initVNode();
struct vList initVList();
void printVNode(struct vNode node, int i);
void printVList(struct vList list);


#endif //SRTP_GENERATE_H
