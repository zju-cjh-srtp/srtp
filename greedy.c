//
// Created by IsaccLee on 4/21/17.
//

#include <stdio.h>
#include "firstFit.h"
int findPnode(struct pNode** pNodeList, int *need,int lastId,int pNodeNum,int dis[][PN_MAX]){//寻找能成功放入的最近的节点,如果上一个为空,则是第一个放的进的节点,-1表示没有放的下的
    int preId = -1,minDis=DISTANCE_MAX;
    for(int i = 0; i < pNodeNum ; i++){
        if((pNodeList[i]->totalResource[CPU] - pNodeList[i]->load[CPU] >= need[CPU]) && (pNodeList[i]->totalResource[MEMORY] - pNodeList[i]->load[MEMORY] >= need[MEMORY]) && (pNodeList[i]->totalResource[DISK] - pNodeList[i]->load[DISK] >= need[DISK])){
            if(lastId == -1) return i;
            else if(preId == -1) {
                preId = i;
                minDis= dis[lastId][i];
            }else{
                if(dis[lastId][i] < minDis){
                    preId = i;
                    minDis = dis[lastId][i];
                }
            }
        }
    }
    return preId;
}


int* UsePNodeInGreedy(int taskNum, int pNodeNum, struct vList* list, int dis[][PN_MAX], struct pNode** pNodeList,FILE *fp)  //对每一个子任务，调用寻找函数,输出结果
{
    int tmp_time = 0;
    int* finish_time = (int *)malloc(sizeof(int) * taskNum);
    while (hasWaiting(list, taskNum, tmp_time, pNodeList) == 1) {//如果还有待分配任务
        for (int i = 0; i < taskNum;i++)
        {
            if (list[i].taskState == WAITING) {
                struct vNode* tmp_subTask = list[i].head;
                struct vNode* prev_subTask = NULL;
                while (NULL != tmp_subTask) {

                    int id;
                    if(prev_subTask)id = findPnode(pNodeList, tmp_subTask->resource,prev_subTask->hostPNodeID,pNodeNum,dis);
                    else id = findPnode(pNodeList, tmp_subTask->resource,-1,pNodeNum,dis);
                    if(id >= 0) {//放的下就输出
                        putTaskIntoPnode(pNodeList[id], tmp_subTask->resource);

                        tmp_subTask->hostPNodeID = id;

                        if (NULL == prev_subTask) {
                            tmp_subTask->startTime = list[i].arriveTime;
                        }
                        else {
                            tmp_subTask->startTime = prev_subTask->startTime + prev_subTask->duration + delay_time(
                                    dis[tmp_subTask->hostPNodeID][prev_subTask->hostPNodeID]);
                        }
                    }

                    else if (id < 0 || tmp_subTask->startTime + tmp_subTask->duration > list[i].deadline) {  //放不下或者超时
                        list[i].taskState = FAILED;
                        finish_time[i] = LOCALERROR;
                        unAllocate(list[i].head, tmp_subTask, pNodeList);
                        break;
                    }
                    prev_subTask = tmp_subTask;
                    tmp_subTask = tmp_subTask->next;
                }
                if (FAILED != list[i].taskState) {
                    list[i].taskState = SUCCEED;
                    finish_time[i] = prev_subTask->startTime + prev_subTask->duration;
                }
            }
        }
        tmp_time += TIME_STEP;
    }
    return finish_time;
}