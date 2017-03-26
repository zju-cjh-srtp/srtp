#include <stdlib.h>
#include <sys/time.h>
#include "generate.h"
#include <stdio.h>
int main() {
    srand(time(NULL));

    /*一个任务，即一条子任务链的小测试*/
//    struct vList list = initVList();
//    printVList(list);
//    printf("--------------\n");
//    freeVList(list);

    /*任务列表，即子任务链的列表的小测试*/
//    int taskNum = generateRand(SFC_MAX,SFC_MIN);
//    struct vList* list = initVListList(taskNum);
//    for(int i = 0; i < SFC_MIN; i++)
//        printVList(list[i]);
//    freeTaskList(taskNum , list);

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
    printPNodeList(pNodeList,pNodeNum);
    freePNodeList(pNodeList,pNodeNum);

    /*初始化物理机距离数组*/
    int dis[pNodeNum][pNodeNum];
    initDis(pNodeNum,dis);
    for(int i = 0; i < pNodeNum; i++)
        for(int j = 0; j < pNodeNum; j++)
            printf("物理机节点 %d 和 %d 之间的距离是 %d\n", i,j,dis[i][j]);
}