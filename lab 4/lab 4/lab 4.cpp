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

/* ============================================================
   БАЗОВАЯ ФУНКЦИЯ СОЗДАНИЯ ДЕРЕВА (из методички)
   ============================================================ */
struct Node* CreateTree(struct Node* root, struct Node* r, int data) {
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
        CreateTree(r, r->left, data);
    else
        CreateTree(r, r->right, data);
    return root;
}

/* ============================================================
   ЗАДАНИЕ 3: создание дерева БЕЗ дубликатов
   ============================================================ */
struct Node* CreateTreeUnique(struct Node* root, struct Node* r, int data) {
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
        CreateTreeUnique(r, r->left, data);
    else
        CreateTreeUnique(r, r->right, data);
    return root;
}

/* ============================================================
   ВЫВОД ДЕРЕВА (из методички)
   ============================================================ */
void print_tree(struct Node* r, int l) {
    if (r == NULL) return;
    print_tree(r->right, l + 1);
    for (int i = 0; i < l; i++)
        printf(" ");
    printf("%d\n", r->data);
    print_tree(r->left, l + 1);
}

/* ============================================================
   ЗАДАНИЕ 1: поиск значения в дереве
   ============================================================ */
struct Node* find_node(struct Node* r, int value) {
    if (r == NULL) return NULL;
    if (r->data == value) return r;
    if (value > r->data)
        return find_node(r->left, value);
    else
        return find_node(r->right, value);
}

/* ============================================================
   ЗАДАНИЕ 2: подсчёт числа вхождений
   ============================================================ */
int count_occurrences(struct Node* r, int value) {
    if (r == NULL) return 0;
    int count = 0;
    if (r->data == value) count = 1;
    return count + count_occurrences(r->left, value)
        + count_occurrences(r->right, value);
}

/* ============================================================
   ЗАДАНИЕ 4: поиск с подсчётом шагов (для оценки сложности)
   ============================================================ */
int find_with_steps(struct Node* r, int value, int* steps) {
    (*steps)++;
    if (r == NULL) return 0;
    if (r->data == value) return 1;
    if (value > r->data)
        return find_with_steps(r->left, value, steps);
    else
        return find_with_steps(r->right, value, steps);
}

/* Приблизительный log2 для оценки сложности */
int log2_approx(int n) {
    int k = 0;
    while (n > 1) { n /= 2; k++; }
    return k;
}

/* ============================================================
   ГЛАВНОЕ МЕНЮ
   ============================================================ */
int main() {
    setlocale(LC_ALL, "Russian");
    int choice;
    int D;
    int useUnique = 0;  /* 0 — с дубликатами, 1 — без */

    do {
        printf("\n=== Бинарное дерево поиска ===\n");
        printf("1 - построить дерево\n");
        printf("2 - вывести дерево\n");
        printf("3 - поиск значения (задание 1)\n");
        printf("4 - подсчёт вхождений (задание 2)\n");
        printf("5 - включить/выключить режим без дубликатов (задание 3)\n");
        printf("6 - оценка сложности поиска (задание 4)\n");
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

            while (1) {
                printf("Введите число: ");
                (void)scanf("%d", &D);
                if (D == -1) break;
                if (useUnique)
                    root = CreateTreeUnique(root, root, D);
                else
                    root = CreateTree(root, root, D);
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
            struct Node* found = find_node(root, value);
            if (found != NULL)
                printf("Элемент %d найден\n", value);
            else
                printf("Элемент %d не найден\n", value);
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
            int value, total = 0;
            printf("Введите значение для поиска: ");
            (void)scanf("%d", &value);

            int steps = 0;
            int found = find_with_steps(root, value, &steps);
            if (found)
                printf("Элемент %d найден за %d шагов\n", value, steps);
            else
                printf("Элемент %d не найден (сделано %d шагов)\n", value, steps);

            /* Считаем, сколько всего элементов в дереве */
            int countTotal(struct Node*);
            /* (оценка ниже — для наглядности) */
            printf("\nТеоретическая оценка:\n");
            printf("  - Сбалансированное дерево: O(log n)\n");
            printf("  - Вырожденное дерево:      O(n)\n");
            printf("  - Ваш результат:           %d шагов\n", steps);
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