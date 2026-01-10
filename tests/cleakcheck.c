#include <stdlib.h>

int main() {
    int* test_ptr = (int*)malloc(sizeof(int));
    if(!test_ptr)
        return 1;

    return 0;
}