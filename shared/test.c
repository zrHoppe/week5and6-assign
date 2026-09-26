#include "vector.h"
#include <assert.h>
#include <stdio.h>

int main(void) {
    printf("Starting Vector library tests...\n");

    Vector v = vectorNew(2);
    assert(v != NULL);
    assert(vectorLen(v) == 0);

    vectorPush(&v, 10);
    vectorPush(&v, 20);
    assert(vectorLen(v) == 2);
    assert(vectorGet(v, 0) == 10);
    assert(vectorGet(v, 1) == 20);

    vectorPush(&v, 30);
    assert(vectorLen(v) == 3);
    assert(vectorGet(v, 2) == 30);

    vectorStatus(v);

    assert(vectorSet(v, 1, 99) == 1);
    assert(vectorGet(v, 1) == 99);
    assert(vectorSet(v, 5, 100) == 0);

    assert(vectorPop(v) == 30);
    assert(vectorLen(v) == 2);
    assert(vectorPop(v) == 99);
    assert(vectorPop(v) == 10);
    assert(vectorPop(v) == 0);

    vectorDelete(v);

    printf("All tests passed successfully.\n");
    return 0;
}