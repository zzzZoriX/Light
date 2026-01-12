#include <stdlib.h>

int main() {
int* test_ptr = (int*)malloc(sizeof(int));
free(test_ptr);

    return 0;
}