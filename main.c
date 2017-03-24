#include <stdlib.h>
#include <sys/time.h>
#include "generate.h"

int main() {
    srand(time(NULL));
//    struct vList list = initVList();
//    printVList(list);
//    printf("--------------\n");
//    freeVList(list);
    struct vList* list = initVListList();
    for(int i = 0; i < SFC_MIN; i++)
        printVList(list[i]);
}