#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include "greedy.h"
#include "output.h"

int main() {

//    int n;
//    scanf("%d",&n);
//    while(n >=0){
        //初始化
        srand(time(NULL));//随机数种子

        //open file
        FILE *frf,*frg,*ftask,*fpf,*fpg,*fchart;
        //fr 任务分配到哪些机子上 f - firstfit  g - greedy
        if((frf = fopen("frf.csv","w+"))==NULL ) {
            printf("fail to create frf");
            exit(1);
        };
        if((frg = fopen("frg.csv","w+"))==NULL ) {
            printf("fail to create frg");
            exit(1);
        };

        //fp 物理机每秒的状态
        if((fpf = fopen("fpf.csv","w+"))==NULL ) {
            printf("fail to create fpf");
            exit(1);
        };
        if((fpg = fopen("fpg.csv","w+"))==NULL ) {
            printf("fail to create fpg");
            exit(1);
        };
        //ftask 任务详情,
        if((ftask = fopen("ftask.csv","w+")) == NULL){
            printf("fail to create task");
            exit(1);
        }
        //fchart, 为了展示画图所有计算的数据
        if((fchart = fopen("fchart.csv","a")) == NULL){
            printf("fail to create fchart");
            exit(1);
        }

        /*一个任务，即一条子任务链的小测试*/
//    struct vList list = initVList();
//    printVList(list);
//    printf("--------------\n");
//    freeVList(list);

        /*任务列表，即子任务链的列表的小测试*/
        int taskNum = generateRand(SFC_MAX,SFC_MIN);
        struct vList* list = initVListList(taskNum);

        sortByArriveTime(list, taskNum);   //新增：让任务安到达时间排序

        //任务状态输出
        fprintf(ftask,"TaskID,Length,ListID,CPU,MEMORY,DISK,StartTime,Duration\n");
        for (int i = 0; i < taskNum; i++) {
            struct vNode* now = list[i].head;
            for(int j = 0; j < list[i].length;j++){
                fprintf(ftask,"%d,%d,%d,%d,%d,%d,%d,%d\n",i+1,list[i].length,j+1,now->resource[0],now->resource[1],now->resource[2],now->startTime,now->duration);//第i个任务的j个子任务,三个资源占有率,开始时间和持续时间
                now = now->next;
            }
            printVList(list[i]);
        }
//    for (int i = 0; i < taskNum; i++) {
//        printf("这是第%d个任务\n", i);
//        printVList(list[i]);
//    }



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

        /*限定时间*/
        int totaltime = TOTAL_TIME;
        fprintf(fpf,"PCCount,TotalTime,TaskCount\n");
        fprintf(fpg,"PCCount,TotalTime,TaskCount\n");
        fprintf(fpf,"%d,%d,%d\n",pNodeNum,totaltime,taskNum);
        fprintf(fpg,"%d,%d,%d\n",pNodeNum,totaltime,taskNum);




        //主要功能区

        //FirstFit
        clock_t timeBeginFirstfit = clock();

        int *finish_time = UsePNodeInOrder(taskNum, pNodeNum, list, dis, pNodeList,frf);
        for (int i = 0;i < taskNum;i++) {
            if (list[i].taskState == REJECTED) {
                printf("任务%d分配失败\n", i);
            }
            else {
                printf("任务%d分配成功，完成时间为%d\n", i, finish_time[i]);
            }
        }
//        PrintPCState(list,pNodeList,fpf,totaltime,pNodeNum,taskNum);//输出物理资源使用情况
        clock_t timeEndFirstfit = clock();


        int *result = malloc(sizeof(int)*3);// 用到物理机的数量,时间开销,分配成功率
        result = AnalystResult(result,list,pNodeList,pNodeNum,taskNum);

        //重置状态
        reset(list,taskNum,pNodeList);


        // Greedy
        clock_t timeBeginGreedyfit = clock();
        int *finish_time2 = UsePNodeInGreedy(taskNum, pNodeNum, list, dis, pNodeList,frg);
        for (int i = 0;i < taskNum;i++) {
            if (list[i].taskState == REJECTED) {
                printf("任务%d分配失败\n", i);
            }
            else {
                printf("任务%d分配成功，完成时间为%d\n", i, finish_time2[i]);
            }
        }
        //PerformTest(taskNum, list, dis);
//        PrintPCState(list,pNodeList,fpg,totaltime,pNodeNum,taskNum);//输出资源
        clock_t timeEndGreedyfit = clock();

        int *result2 = malloc(sizeof(int)*3);// 分配成功率,用到物理机的数量,时间开销,
        result2 = AnalystResult(result2,list,pNodeList,pNodeNum,taskNum);

//    printf("%d,%d",timeBeginFirstfit,timeEndFirstfit);
//    输出整体统计记录
        fprintf(fchart,"%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d\n",pNodeNum,totaltime,taskNum,timeEndFirstfit-timeBeginFirstfit,timeEndGreedyfit-timeBeginGreedyfit,result[0],result2[0],result[1],result2[1],result[2],result2[2]);

        //free
        freeTaskList(taskNum, list);
        freePNodeList(pNodeList, pNodeNum);
        fclose(fpf);
        fclose(fpg);
        fclose(frf);
        fclose(frg);
        fclose(ftask);
//    system("pause"); //for win only

//        n--;
//    }
    return 0;
}