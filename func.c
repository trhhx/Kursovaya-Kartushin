#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "func.h"

Set createSet() {
    Set set;
    set.size = 0;
    set.capacity = 10;
    set.elements = malloc(set.capacity * sizeof(int));
    return set;
}

void addToSet(Set* set, int element) {
    for (int i = 0; i < set->size; i++) {
        if (set->elements[i] == element) return;
    }

    if (set->size >= set->capacity) {
        set->capacity *= 2;
        set->elements = realloc(set->elements, set->capacity * sizeof(int));
    }

    set->elements[set->size] = element;
    set->size++;
}

int isInSet(Set set, int element) {
    for (int i = 0; i < set.size; i++) {
        if (set.elements[i] == element) return 1;
    }
    return 0;
}

Set unionSelectedSets(Set sets[], int indices[], int count) {
    Set result = createSet();

    for (int i = 0; i < count; i++) {
        int idx = indices[i];
        for (int j = 0; j < sets[idx].size; j++) {
            int element = sets[idx].elements[j];
            if (!isInSet(result, element)) {
                addToSet(&result, element);
            }
        }
    }

    return result;
}

void printSet(Set set) {
    printf("{");
    for (int i = 0; i < set.size; i++) {
        printf("%d", set.elements[i]);
        if (i < set.size - 1) printf(", ");
    }
    printf("}\n");
}

void saveToFile(Set sets[], int count, Set result, const char* filename) {
    FILE* file = fopen(filename, "w");
    if (!file) {
        printf("Ошибка создания файла!\n");
        return;
    }

    fprintf(file, "Исходные множества:\n\n");
    for (int i = 0; i < count; i++) {
        fprintf(file, "Множество %d: {", i + 1);
        for (int j = 0; j < sets[i].size; j++) {
            fprintf(file, "%d", sets[i].elements[j]);
            if (j < sets[i].size - 1) fprintf(file, ", ");
        }
        fprintf(file, "}\n");
    }

    fprintf(file, "\nОбъединение: {");
    for (int i = 0; i < result.size; i++) {
        fprintf(file, "%d", result.elements[i]);
        if (i < result.size - 1) fprintf(file, ", ");
    }
    fprintf(file, "}\n");

    fclose(file);
    printf("Сохранено в файл '%s'\n", filename);
}

void freeSet(Set* set) {
    if (set->elements) {
        free(set->elements);
    }
    set->size = 0;
    set->capacity = 0;
}
