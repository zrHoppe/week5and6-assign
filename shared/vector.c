#include "vector.h"

Vector vectorNew(int size) {
    if (size < 0) {
        size = 0;
    }

    Vector v = (Vector)malloc(sizeof(struct vector));
    if (v == NULL) {
        return NULL;
    }

    v->allocated = size;
    v->used = 0;

    if (size > 0) {
        v->data = (int *)malloc(size * sizeof(int));
        if (v->data == NULL) {
            free(v);
            return NULL;
        }
    } else {
        v->data = NULL;
    }

    return v;
}

void vectorDelete(Vector vector) {
    if (vector == NULL) {
        return;
    }
    if (vector->data != NULL) {
        free(vector->data);
        vector->data = NULL;
    }
    free(vector);
}

int *vectorResize(Vector *vector, int addSize) {
    if (vector == NULL || *vector == NULL || addSize <= 0) {
        return (vector && *vector) ? (*vector)->data : NULL;
    }

    Vector v = *vector;
    int newAllocated = v->allocated + addSize;

    int *newData = (int *)malloc(newAllocated * sizeof(int));
    if (newData == NULL) {
        return NULL;
    }

    for (int i = 0; i < v->used; i++) {
        newData[i] = v->data[i];
    }

    if (v->data != NULL) {
        free(v->data);
    }

    v->data = newData;
    v->allocated = newAllocated;

    return v->data;
}

void vectorPush(Vector *vector, int value) {
    if (vector == NULL || *vector == NULL) {
        return;
    }

    Vector v = *vector;

    if (v->used >= v->allocated) {
        int addSize = (v->allocated > 0) ? v->allocated : 4;
        if (vectorResize(vector, addSize) == NULL) {
            fprintf(stderr, "Error: vectorResize failed to allocate memory.\n");
            return;
        }
        v = *vector;
    }

    v->data[v->used] = value;
    v->used++;
}

int vectorPop(Vector vector) {
    if (vector == NULL || vector->used <= 0) {
        return 0;
    }
    vector->used--;
    return vector->data[vector->used];
}

int vectorGet(Vector vector, int index) {
    if (vector == NULL || index < 0 || index >= vector->used) {
        return 0;
    }
    return vector->data[index];
}

int vectorSet(Vector vector, int index, int value) {
    if (vector == NULL || index < 0 || index >= vector->used) {
        return 0;
    }
    vector->data[index] = value;
    return 1;
}

int vectorLen(Vector vector) {
    if (vector == NULL) {
        return 0;
    }
    return vector->used;
}

void vectorStatus(Vector vector) {
    if (vector == NULL) {
        printf("Vector is NULL\n");
        return;
    }

    printf("=== Vector Status ===\n");
    printf("Struct Address : %p\n", (void *)vector);
    printf("Data Address   : %p\n", (void *)vector->data);
    printf("Allocated Size : %d\n", vector->allocated);
    printf("Elements Used  : %d\n", vector->used);
    printf("Contents       : [");
    for (int i = 0; i < vector->used; i++) {
        printf("%d%s", vector->data[i], (i == vector->used - 1) ? "" : ", ");
    }
    printf("]\n");
    printf("=====================\n");
}