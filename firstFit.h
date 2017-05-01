#ifndef _TEST_H_
#define _TEST_H_

#define LOCALERROR -1
#define TIME_STEP 1
#include "generate.h"

//void PerformTest(int taskNum, struct vList* list, int dis[][PN_MAX]);
void sortByArriveTime(struct vList*  list, int taskNum);
int * UsePNodeInOrder(int taskNum, int pNodeNum, struct vList* list, int dis[][PN_MAX], struct pNode** pNodeList,FILE * fp);
void reset(struct vList* list,int taskNum,struct pNode** pNodeList);

#endif // !_TEST_H_