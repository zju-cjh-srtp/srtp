//
// Created by Wu on 2017/3/24.
//
#ifndef SRTP_GENERATE_H
#define SRTP_GENERATE_H


/*总计用时*/
#define TOTAL_TIME 99999

/*PN距离参数*/
#define DISTANCE_MAX 20
#define DISTANCE_MIN 1

/*PN资源参数*/
#define PN_RES_MAX 70
#define PN_RES_MIN 50

/*PN数量参数*/
#define PN_MAX 1400
#define PN_MIN 1400

/*SFC数量参数*/
#define SFC_MAX 1500
#define SFC_MIN 1500

/*SFC中SF数量参数*/
#define SF_MAX 20
#define SF_MIN 5

/*SFC到达时间参数*/
#define ARRIVE_MAX 700
#define ARRIVE_MIN 0

/*SFC截止时间参数*/
#define DEADLINE_MAX 500
#define DEADLINE_MIN 0

/*SF运行时间参数*/
#define RUN_MAX 10
#define RUN_MIN 4

/*SF资源参数*/
#define SF_RES_MAX 7
#define SF_RES_MIN 2

/*资源种类*/
#define CPU 0
#define MEMORY 1
#define DISK 2

/*未绑定物理机时虚拟机缺省的宿主机号*/
#define DEFAULT_HOST -1

/*任务链分配状态*/
#define WAITING 0
#define SUCCEED 1
#define FAILED 2
#define REJECTED 3
#define WORKING 4
#define FINISHED 5

/*虚拟机，任务链中的子任务*/
struct vNode{
    int resource[3];//三种类型资源
    int startTime;//开始时间
    int duration;//持续时间
    int hostPNodeID; //分配到的物理机的ID
    struct vNode* next;//下一个子任务
};

struct vList{
    int arriveTime;
    int deadline;
    int taskState;  //任务链状态
    int length;
    struct vNode* head;
};


/*物理机*/
struct pNode{
    int totalResource[3];//三种类型资源共有多少
    int load[3];//三种类型资源已经被占用了多少
};

/*生成一个范围在[min，max]的随机数*/
int generateRand(int max, int min);

/*生成一个虚拟节点，即一个任务的其中一个子任务*/
struct vNode* initVNode();

/*生成一个vList*/
struct vList initVList();

/*打印一个子任务*/
void printVNode(struct vNode node, int i);

/*打印整个任务*/
void printVList(struct vList list);

/*释放一个vList*/
void freeVList(struct vList list);

/*释放一个vNode*/
void freeVNode(struct vNode* node);

/*创建任务的列表，每一个任务是一条子任务链*/
struct vList* initVListList(int taskNum);

/*释放任务列表*/
void freeTaskList(int taskNum, struct vList* list);

/*生成一个物理机节点*/
struct pNode* initPNode();

/*打印一个物理机*/
void printPNode(struct pNode node, int i);

/*释放一个物理机节点*/
void freePNode(struct pNode* node);

/*创建一个物理机列表*/
struct pNode** initPNodeList(int pNodeNum);

/*打印一个物理机列表*/
void printPNodeList(struct pNode** list, int pNodeNum);

/*释放所有物理机，即物理机列表*/
void freePNodeList(struct pNode** list, int pNodeNum);

/*初始化所有物理机之间的距离*/
void initDis(int pNodeNum,int dis[][PN_MAX]);

#endif //SRTP_GENERATE_H
