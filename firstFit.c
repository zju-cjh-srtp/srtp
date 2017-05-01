#include <stdio.h>
#include <stdlib.h>
#include "firstFit.h"


//void PerformTest(int taskNum, struct vList* list, int dis[][PN_MAX])
//{
//	for (int i = 0;i < taskNum;i++)
//	{
//		if (FAILED == list[i].taskState) {
//			printf("task %d scheduled failed\n", i);
//		}
//		else if (SUCCEED == list[i].taskState)
//		{
//
//		}
//	}
//}
void unAllocate(struct vNode* from, struct vNode* to, struct pNode** pNodeList)  //ȡ�����䣬��������һ���������ʧ�ܺ�ȡ���Ѿ�������ӽڵ�ռ�õ���Դ����fromָ��Ľڵ㵽toָ��Ľڵ㣬toָ��Ľڵ��ʾ���һ�����䵽�������������ڵ����һ���ڵ㣩��
{
	while (from != to)
	{
		pNodeList[from->hostPNodeID]->load[CPU] -= from->resource[CPU];
		pNodeList[from->hostPNodeID]->load[MEMORY] -= from->resource[MEMORY];
		pNodeList[from->hostPNodeID]->load[DISK] -= from->resource[DISK];
		from = from->next;
	}
}
void reset(struct vList* list,int taskNum,struct pNode** pNodeList){
	for (int i = 0;i < taskNum;i++) {
		if(list[i].taskState == SUCCEED){unAllocate(list[i].head, NULL, pNodeList);}
		list[i].taskState = WAITING;
	}
}
int hasWaiting(struct vList*  list, int taskNum, int tmp_time, struct pNode** pNodeList) //�ж��Ƿ��д��������񣬲��������״̬ת��
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

int delay_time(int distance) //�����ϸ�����������������͵�ǰ�����������������������ӳ�ʱ��
{
	return distance / 5;
}

int putTaskIntoPnode(struct pNode* PC, int *need)  //��������������������ܳɹ����뷵��1�����룬���򷵻�0
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




int* UsePNodeInOrder(int taskNum, int pNodeNum, struct vList* list, int dis[][PN_MAX], struct pNode** pNodeList,FILE *fp)  //��ÿһ�������񣬰���������˳���ҵ���һ��װ���µ�������������롣����ÿ����������ʱ��
{
	int tmp_time = 0;
	int* finish_time = (int *)malloc(sizeof(int) * taskNum);
	while (hasWaiting(list, taskNum, tmp_time, pNodeList) == 1) {//������д���������
		for (int i = 0; i < taskNum;i++)
		{
			if (list[i].taskState == WAITING) {
				struct vNode* tmp_subTask = list[i].head;
				struct vNode* prev_subTask = NULL;
				while (NULL != tmp_subTask) {
					int j;
					for (j = 0;j < pNodeNum;j++) {
						if (1 == putTaskIntoPnode(pNodeList[j], tmp_subTask->resource)) {
							tmp_subTask->hostPNodeID = j;
							if (NULL == prev_subTask) {
								tmp_subTask->startTime = list[i].arriveTime;
							}
							else {
								tmp_subTask->startTime = prev_subTask->startTime + prev_subTask->duration + delay_time(dis[tmp_subTask->hostPNodeID][prev_subTask->hostPNodeID]);
							}
							break;
						}
					}
					if (j == pNodeNum || tmp_subTask->startTime + tmp_subTask->duration > list[i].deadline) {  //�Ų��»��߳�ʱ
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

