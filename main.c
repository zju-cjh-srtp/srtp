#include "generate.h"

int main() {
    srand(time(NULL));
    struct vList list = initVList();
    printVList(list);
}