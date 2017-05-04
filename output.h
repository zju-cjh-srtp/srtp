//
// Created by IsaccLee on 5/3/17.
//

#ifndef SRTP_STATE_H
#define SRTP_STATE_H

void PrintPCState(struct vList* list,struct pNode** pNodeList,FILE *fp,int Time,int pNum,int tNum);//向fp中输出pnode在当前vlist下的资源占有量
int* AnalystResult(int* result,struct vList* list,struct pNode** pNodeList,int pNodeNum,int taskNum);
#endif //SRTP_STATE_H
