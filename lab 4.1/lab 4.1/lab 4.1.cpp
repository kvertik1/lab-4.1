#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

struct Node* root = NULL;
int maxLevel = 100;  

struct Node* CreateTree(struct Node* root, struct Node* r, int data,
    int level, int maxLevel) {          
    if (level > maxLevel) {                                 
        printf("Достигнут максимальный уровень (%d), элемент %d не добавлен\n",
            maxLevel, data);
        return root;
    }
    if (r == NULL) {
        r = (struct Node*)malloc(sizeof(struct Node));
        if (r == NULL) {
            printf("Ошибка выделения памяти\n");
            exit(0);
        }
        r->left = NULL;
        r->right = NULL;
        r->data = data;
        if (root == NULL) return r;
        if (data > root->data) root->left = r;
        else root->right = r;
        return r;
    }
    if (data > r->data)
        CreateTree(r, r->left, data, level + 1, maxLevel);  // НОВОЕ: level + 1
    else
        CreateTree(r, r->right, data, level + 1, maxLevel); // НОВОЕ: level + 1
    return root;
}

struct Node* CreateTreeUnique(struct Node* root, struct Node* r, int data,
    int level, int maxLevel) {    
    if (level > maxLevel) {                                 
        printf("Достигнут максимальный уровень (%d), элемент %d не добавлен\n",
            maxLevel, data);
        return root;
    }
    if (r == NULL) {
        r = (struct Node*)malloc(sizeof(struct Node));
        if (r == NULL) {
            printf("Ошибка выделения памяти\n");
            exit(0);
        }
        r->left = NULL;
        r->right = NULL;
        r->data = data;
        if (root == NULL) return r;
        if (data > root->data) root->left = r;
        else root->right = r;
        return r;
    }
    if (data == r->data) {
        printf("Элемент %d уже есть в дереве, пропущен\n", data);
        return root;
    }
    if (data > r->data)
        CreateTreeUnique(r, r->left, data, level + 1, maxLevel);   // НОВОЕ
    else
        CreateTreeUnique(r, r->right, data, level + 1, maxLevel);  // НОВОЕ
    return root;
}

void print_tree(struct Node* r, int l) {
    if (r == NULL) return;
    print_tree(r->right, l + 1);
    for (int i = 0; i < l; i++)
        printf("    ");                                     
    printf("%d (уровень %d)\n", r->data, l);                
    print_tree(r->left, l + 1);
}

int find_all_levels(struct Node* r, int value, int level) { // НОВ
    if (r == NULL) return 0;
    int found = 0;
    if (r->data == value) {
        printf("Элемент %d найден на уровне %d\n", value, level);
        found = 1;
    }
    found += find_all_levels(r->left, value, level + 1);
    found += find_all_levels(r->right, value, level + 1);
    return found;
}

struct Node* find_node(struct Node* r, int value) {
    if (r == NULL) return NULL;
    if (r->data == value) return r;
    if (value > r->data)
        return find_node(r->left, value);
    else
        return find_node(r->right, value);
}

int count_occurrences(struct Node* r, int value) {
    if (r == NULL) return 0;
    int count = 0;
    if (r->data == value) count = 1;
    return count + count_occurrences(r->left, value)
        + count_occurrences(r->right, value);
}

int find_with_steps(struct Node* r, int value, int* steps) {
    (*steps)++;
    if (r == NULL) return 0;
    if (r->data == value) return 1;
    if (value > r->data)
        return find_with_steps(r->left, value, steps);
    else
        return find_with_steps(r->right, value, steps);
}

int main() {
    setlocale(LC_ALL, "Russian");
    int choice;
    int D;
    int useUnique = 0;

    do {
        printf("\n=== Бинарное дерево поиска ===\n");
        printf("1 - построить дерево\n");
        printf("2 - вывести дерево\n");
        printf("3 - поиск значения (задание 1)\n");
        printf("4 - подсчёт вхождений (задание 2)\n");
        printf("5 - включить/выключить режим без дубликатов (задание 3)\n");
        printf("6 - оценка сложности поиска (задание 4)\n");
        printf("7 - задать ограничение по уровню\n");        // НОВОЕ
        printf("8 - показать текущее ограничение\n");         // НОВОЕ
        printf("0 - выход\n");
        printf("Ваш выбор: ");
        (void)scanf("%d", &choice);

        switch (choice) {
        case 1: {
            printf("-1 - окончание построения дерева\n");
            if (useUnique)
                printf("Режим: без дубликатов\n");
            else
                printf("Режим: с дубликатами\n");
            printf("Ограничение уровня: %d\n", maxLevel);    // НОВОЕ

            while (1) {
                printf("Введите число: ");
                (void)scanf("%d", &D);
                if (D == -1) break;
                if (useUnique)
                    root = CreateTreeUnique(root, root, D, 0, maxLevel); // НОВОЕ
                else
                    root = CreateTree(root, root, D, 0, maxLevel);       // НОВОЕ
            }
            break;
        }
        case 2: {
            if (root == NULL) {
                printf("Дерево пусто\n");
                break;
            }
            printf("\nДерево (повёрнуто на 90°):\n");
            print_tree(root, 0);
            break;
        }
        case 3: {
            if (root == NULL) {
                printf("Дерево пусто\n");
                break;
            }
            int value;
            printf("Введите значение для поиска: ");
            (void)scanf("%d", &value);
            int found = find_all_levels(root, value, 0);     // НОВОЕ
            if (found == 0)
                printf("Элемент %d не найден\n", value);
            else
                printf("Всего найдено вхождений: %d\n", found);
            break;
        }
        case 4: {
            if (root == NULL) {
                printf("Дерево пусто\n");
                break;
            }
            int value;
            printf("Введите значение для подсчёта вхождений: ");
            (void)scanf("%d", &value);
            int cnt = count_occurrences(root, value);
            printf("Элемент %d встречается %d раз\n", value, cnt);
            break;
        }
        case 5: {
            useUnique = !useUnique;
            if (useUnique)
                printf("Режим БЕЗ дубликатов включён\n");
            else
                printf("Режим С дубликатами включён\n");
            break;
        }
        case 6: {
            if (root == NULL) {
                printf("Дерево пусто\n");
                break;
            }
            int value;
            printf("Введите значение для поиска: ");
            (void)scanf("%d", &value);
            int steps = 0;
            int found = find_with_steps(root, value, &steps);
            if (found)
                printf("Элемент %d найден за %d шагов\n", value, steps);
            else
                printf("Элемент %d не найден (сделано %d шагов)\n", value, steps);
            printf("\nТеоретическая оценка:\n");
            printf("  - Сбалансированное дерево: O(log n)\n");
            printf("  - Вырожденное дерево:      O(n)\n");
            printf("  - Ваш результат:           %d шагов\n", steps);
            break;
        }
        case 7: {                                            // НОВОЕ
            printf("Текущее ограничение: %d\n", maxLevel);
            printf("Введите максимальный уровень (0 — только корень): ");
            (void)scanf("%d", &maxLevel);
            printf("Новое ограничение: %d\n", maxLevel);
            break;
        }
        case 8: {                                            // НОВОЕ
            printf("Текущее ограничение уровня: %d\n", maxLevel);
            break;
        }
        case 0:
            printf("Выход из программы.\n");
            break;
        default:
            printf("Неверный выбор\n");
        }
    } while (choice != 0);

    return 0;
}