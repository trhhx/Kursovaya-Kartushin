#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "func.h"
#include <locale.h>

#define MAX_SETS 10

void clearInput() {
    while (getchar() != '\n');
}

void displayMenu() {
    printf("\n=== ОБЪЕДИНЕНИЕ МНОЖЕСТВ ===\n");
    printf("1. Создать случайное множество\n");
    printf("2. Ввести множество вручную\n");
    printf("3. Показать все множества\n");
    printf("4. Найти объединение \n");
    printf("5. Сохранить в файл\n");
    printf("6. Выход\n");
    printf("Выбор: ");
}

int main() {
    setlocale(LC_ALL, "Russian");
    printf("-----------------------------------------------------------------------------------\n\n");
    printf("          Курсовая работа по дисциплине\n");
    printf("   \"Логика и основы алгоритмизации и инженерия задач\"\n");
    printf("на тему: \"Реализация операции нахождения объединения двух и более множеств\"\n\n");
    printf("Выполнил студент группы 24ВВB1: Картушин Р.А\n");
    printf("Приняла: Юрова О.В.\n");
    printf("-----------------------------------------------------------------------------------\n\n");

    Set sets[MAX_SETS];
    Set result;
    int count = 0;
    int choice;

    for (int i = 0; i < MAX_SETS; i++) {
        sets[i] = createSet();
    }
    result = createSet();

    do {
        displayMenu();
        if (scanf("%d", &choice) != 1) {
            printf("Неверный ввод!\n");
            clearInput();
            continue;
        }
        clearInput();

        switch (choice) {
        case 1: {
            if (count >= MAX_SETS) {
                printf("Максимум %d множеств!\n", MAX_SETS);
                break;
            }

            printf("\n--- Создание случайного множества %d ---\n", count + 1);

            int min, max, elements;

            printf("Минимальное число: ");
            scanf("%d", &min);
            clearInput();

            printf("Максимальное число: ");
            scanf("%d", &max);
            clearInput();

            printf("Сколько элементов? ");
            scanf("%d", &elements);
            clearInput();

            freeSet(&sets[count]);
            sets[count] = createSet();

            srand((unsigned int)time(NULL));
            for (int i = 0; i < elements; i++) {
                int num = min + rand() % (max - min + 1);
                addToSet(&sets[count], num);
            }

            printf("Создано множество %d!\n", count + 1);
            count++;
            break;
        }

        case 2: {
            if (count >= MAX_SETS) {
                printf("Максимум %d множеств!\n", MAX_SETS);
                break;
            }

            printf("\n--- Ввод множества %d ---\n", count + 1);

            freeSet(&sets[count]);
            sets[count] = createSet();

            printf("Сколько элементов? ");
            int n;
            scanf("%d", &n);
            clearInput();

            printf("Введите %d элементов (через пробел):\n", n);
            for (int i = 0; i < n; i++) {
                int num;
                if (scanf("%d", &num) == 1) {
                    addToSet(&sets[count], num);
                }
            }
            clearInput();

            printf("Множество %d сохранено!\n", count + 1);
            count++;
            break;
        }

        case 3: {
            if (count == 0) {
                printf("Нет созданных множеств!\n");
                break;
            }

            printf("\n--- Все множества (%d шт.) ---\n", count);
            for (int i = 0; i < count; i++) {
                printf("%d. Множество %d (элементов: %d): ",
                    i + 1, i + 1, sets[i].size);
                printSet(sets[i]);
            }
            break;
        }

        case 4: {
            if (count < 2) {
                printf("Нужно минимум 2 множества! Сейчас %d.\n", count);
                break;
            }

            printf("\nДоступные множества (всего %d):\n", count);
            for (int i = 0; i < count; i++) {
                printf("%d. ", i + 1);
                printSet(sets[i]);
            }

            printf("Какие множества объединить? (номера через пробел): ");

            int indices[MAX_SETS];
            int selected = 0;
            char input[100];

            fgets(input, sizeof(input), stdin);
            char* token = strtok(input, " \t\n");

            while (token != NULL && selected < MAX_SETS) {
                int idx = atoi(token) - 1;
                if (idx >= 0 && idx < count) {
                    indices[selected++] = idx;
                }
                token = strtok(NULL, " \t\n");
            }

            if (selected < 2) {
                printf("Нужно выбрать минимум 2 множества!\n");
                break;
            }

            printf("\n--- Объединение выбранных множеств ---\n");
            for (int i = 0; i < selected; i++) {
                int idx = indices[i];
                printf("Множество %d: ", idx + 1);
                printSet(sets[idx]);
            }

            freeSet(&result);
            result = unionSelectedSets(sets, indices, selected);

            printf("\nРезультат объединения: ");
            printSet(result);
            printf("Всего элементов: %d\n", result.size);
            break;
        }

        case 5: {
            if (count == 0) {
                printf("Нет множеств для сохранения!\n");
                break;
            }

            if (result.size == 0) {
                printf("Сначала найдите объединение!\n");
                break;
            }

            char filename[100];
            printf("Имя файла: ");
            scanf("%99s", filename);
            clearInput();

            saveToFile(sets, count, result, filename);
            break;
        }

        case 6: {
            printf("Выход...\n");
            break;
        }

        default: {
            printf("Неверный выбор! (1-6)\n");
            break;
        }
        }
    } while (choice != 6);

    
    for (int i = 0; i < MAX_SETS; i++) {
        freeSet(&sets[i]);
    }
    freeSet(&result);

    return 0;
}
