//
// Created by IsaccLee on 4/21/17.
//

#include <stdio.h>




void unAllocate(struct vNode* from, struct vNode* to, struct pNode** pNodeList)  //取消分配，即当发现一个任务分配失败后，取消已经分配的子节点占用的资源（从from指向的节点到to指向的节点，to指向的节点表示最后一个分配到物理机的子任务节点的下一个节点）。
{
    while (from != to)
    {
        pNodeList[from->hostPNodeID]->load[CPU] -= from->resource[CPU];
        pNodeList[from->hostPNodeID]->load[MEMORY] -= from->resource[MEMORY];
        pNodeList[from->hostPNodeID]->load[DISK] -= from->resource[DISK];
        from = from->next;
    }
}

int hasWaiting(struct vList*  list, int taskNum, int tmp_time, struct pNode** pNodeList) //判断是否有待分配任务，并完成任务状态转换
{
    for (int i = 0;i < taskNum;i++) {
        if (tmp_time >= list[i].deadline) {
            if (list[i].taskState == SUCCEED) {
                list[i].taskState = FINISHED;
                unAllocate(list[i].head, NULL, pNodeList);
            }
            else if (list[i].taskState == FAILED || list[i].taskState == WAITING) {
                list[i].taskState = REJECTED;
            }
        }
        else if (list[i].taskState == FAILED) {
            list[i].taskState = WAITING;
        }
    }
    for (int i = 0;i < taskNum;i++) {
        if (list[i].taskState == WAITING)
            return 1;
    }
    return 0;
}

void sortByArriveTime(struct vList*  list, int taskNum)
{
    struct vList tmp;
    for (int i = 0;i < taskNum - 1;i++) {
        for (int j = i+1;j < taskNum;j++) {
            if (list[i].arriveTime > list[j].arriveTime) {
                tmp = list[i];
                list[i] = list[j];
                list[j] = tmp;
            }
        }
    }
}

int delay_time(int distance) //根据上个子任务所在物理机和当前子任务所在物理机距离计算延迟时间
{
    return distance / 5;
}

int putTaskIntoPnode(struct pNode* PC, int *need)  //子任务放入物理机。如果能成功放入返回1并放入，否则返回0
{
    if ((PC->totalResource[CPU] - PC->load[CPU] >= need[CPU]) && (PC->totalResource[MEMORY] - PC->load[MEMORY] >= need[MEMORY]) && (PC->totalResource[DISK] - PC->load[DISK] >= need[DISK]))
    {
        PC->load[CPU] += need[CPU];
        PC->load[MEMORY] += need[MEMORY];
        PC->load[DISK] += need[DISK];
        return 1;
    }
    else
    {
        return 0;
    }
}

int findPnode(struct pNode** pNodeList, int *need,int lastId,int pNodeNum,int dis[][PN_MAX]){
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


int* UsePNodeInGreedy(int taskNum, int pNodeNum, struct vList* list, int dis[][PN_MAX], struct pNode** pNodeList)  //对每一个子任务，按物理机编号顺序找到第一个装得下的物理机，并放入。返回每个任务的完成时间
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
                    if(id >= 0) {
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