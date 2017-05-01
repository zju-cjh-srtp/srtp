//
// Created by IsaccLee on 4/21/17.
//

#ifndef SRTP_GREEDY_H
#define SRTP_GREEDY_H

#define LOCALERROR -1
#define TIME_STEP 1
#include "firstFit.h"

int* UsePNodeInGreedy(int taskNum, int pNodeNum, struct vList* list, int dis[][PN_MAX], struct pNode** pNodeList,FILE * fp);


#endif //SRTP_GREEDY_H
