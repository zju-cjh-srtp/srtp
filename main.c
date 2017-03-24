#include <stdlib.h>
#include <sys/time.h>
#include <printf.h>
#include "generate.h"

int main() {
    srand(time(NULL));
    struct vList list = initVList();
    printVList(list);
    printf("--------------\n");
    freeVList(list);
}