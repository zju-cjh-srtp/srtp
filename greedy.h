//
// Created by IsaccLee on 4/21/17.
//

#ifndef SRTP_GREEDY_H
#define SRTP_GREEDY_H

#define LOCALERROR -1
#define TIME_STEP 1
#include "generate.h"

//void PerformTest(int taskNum, struct vList* list, int dis[][PN_MAX]);
void sortByArriveTime(struct vList*  list, int taskNum);
int * UsePNodeInGreedy(int taskNum, int pNodeNum, struct vList* list, int dis[][PN_MAX], struct pNode** pNodeList);


#endif //SRTP_GREEDY_H
