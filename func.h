#ifndef FUNC_H
#define FUNC_H

typedef struct {
    int* elements;
    int size;
    int capacity;
} Set;

Set createSet();
void addToSet(Set* set, int element);
int isInSet(Set set, int element);
Set unionSelectedSets(Set sets[], int indices[], int count);
void printSet(Set set);
void saveToFile(Set sets[], int count, Set result, const char* filename);
void freeSet(Set* set);

#endif
