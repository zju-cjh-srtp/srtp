#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include "greedy.h"
int main() {
    srand(time(NULL));

    /*一个任务，即一条子任务链的小测试*/
//    struct vList list = initVList();
//    printVList(list);
//    printf("--------------\n");
//    freeVList(list);

    /*任务列表，即子任务链的列表的小测试*/
    int taskNum = generateRand(SFC_MAX,SFC_MIN);
    struct vList* list = initVListList(taskNum);

    sortByArriveTime(list, taskNum);   //新增：让任务安到达时间排序

    for (int i = 0; i < taskNum; i++) {
        printf("这是第%d个任务\n", i);
        printVList(list[i]);
    }



    /*物理机节点的小测试*/
//    struct pNode* node1 = initPNode();
//    struct pNode* node2 = initPNode();
//    printPNode(*node1,1);
//    printPNode(*node2,1);
//    freePNode(node1);
//    freePNode(node2);

    /*物理机列表的小测试*/
    int pNodeNum = generateRand(PN_MAX,PN_MIN);
    struct pNode** pNodeList = initPNodeList(pNodeNum);
    // printPNodeList(pNodeList,pNodeNum);


    /*初始化物理机距离数组*/
    int dis[PN_MAX][PN_MAX];
    initDis(pNodeNum,dis);
    //for (int i = 0; i < pNodeNum; i++)
    //  for (int j = 0; j < pNodeNum; j++);
    //    printf("物理机节点 %d 和 %d 之间的距离是 %d\n", i,j,dis[i][j]);


    int *finish_time = UsePNodeInOrder(taskNum, pNodeNum, list, dis, pNodeList);
    for (int i = 0;i < taskNum;i++) {
        if (list[i].taskState == REJECTED) {
            printf("任务%d分配失败\n", i);
        }
        else {
            printf("任务%d分配成功，完成时间为%d\n", i, finish_time[i]);
        }
    }
    reset(list,taskNum,pNodeList);
    int *finish_time2 = UsePNodeInGreedy(taskNum, pNodeNum, list, dis, pNodeList);
    for (int i = 0;i < taskNum;i++) {
        if (list[i].taskState == REJECTED) {
            printf("任务%d分配失败\n", i);
        }
        else {
            printf("任务%d分配成功，完成时间为%d\n", i, finish_time2[i]);
        }
    }
    //PerformTest(taskNum, list, dis);

    freeTaskList(taskNum, list);
    freePNodeList(pNodeList, pNodeNum);

//    system("pause"); //for win only
}