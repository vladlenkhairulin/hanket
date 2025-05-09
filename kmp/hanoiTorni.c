#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "hanoi.h"

Stack* initStack(int cap) {
    Stack* s = (Stack*)malloc(sizeof(Stack));
    if (!s) {
        printf("Memmory for stack not allocated!\n");
        return NULL;
    }
    s->top = NULL;
    s->capacity = cap;
    s->disks = (Node**)malloc(cap * sizeof(Node*));
    if (!s->disks) {
        printf("Memory not alloc'ed for array of Nodes");
        free(s);
        return NULL;
    }
    for (int i = 0; i < cap; i++) {
        s->disks[i] = (Node*)malloc(sizeof(Node));
        if (!s->disks[i]) {
            printf("Memory not alloc'ed for a Node");
            for (int j = 0; j < i; j++) free(s->disks[j]);
            free(s->disks);
            free(s);
            return NULL;
        }
        s->disks[i]->next = NULL;
    }
    s->top_index = -1;
    return s;
}

int push(Stack* s, int el) {
    if (s->top && s->top->value < el) {
        printf("Don't try to put bigger ring atop a smaller one\n");
        return -1;
    }
    if (s->top_index + 1 == s->capacity) {
        printf("Stack ist uberdrussiG! OVF\n");
        return -1;
    }
    Node* node = s->disks[++s->top_index];
    node->value = el;
    node->next = s->top;
    s->top = node;
    return 0;
}

int top(Stack* s) {
    if (!s->top) {
        printf("Stack is empty!");
        return -1;
    }
    return s->top->value;
}

int pop(Stack* s) {
    if (!s->top) {
        printf("Stack is empty!");
        return -1;
    }
    int val = s->top->value;
    s->top = s->top->next;
    s->top_index--;
    return val;
}

void move(Stack* from, Stack* to, char from_name, char to_name) {
    if (!from->top) return;
    
    int disk = from->top->value;
    if (to->top && to->top->value <= disk) {
        printf("Don't try to put bigger ring atop a smaller one\n");
        return;
    }
    
    int val = pop(from);
    if (val == -1) return;
    
    if (push(to, val) == -1) {
        push(from, val); // Возвращаем обратно при ошибке
        return;
    }
    
    printf("Moving disk %d from tower %c to tower %c.\n", val, from_name, to_name);
}

void hanoi(int n, Stack* A, Stack* B, Stack* C, char source_name, char storage_name, char d_name, int* count) {
    if (n == 0) return;
    hanoi(n-1, A, C, B, source_name, d_name, storage_name, count);
    move(A, C, source_name, d_name); 
    (*count)++;
    hanoi(n-1, B, A, C, storage_name, source_name, d_name, count);
}

void freeStack(Stack* s) {
    for (int i = 0; i < s->capacity; i++) {
        free(s->disks[i]);
    }
    free(s->disks);
    free(s);
}

int main() {
    int n;
    printf("Input number of disks: \n");
    scanf("%d", &n);
    int count = 0;
    
    Stack* source = initStack(n);
    Stack* storage = initStack(n-1);
    Stack* dest = initStack(n);
    
    for (int i = 0; i < n; i++) push(source, n-i);
    
    clock_t start = clock();
    hanoi(n, source, storage, dest, 'A', 'B', 'C', &count);
    clock_t end = clock();
    
    double time = (double)(end-start)/CLOCKS_PER_SEC;
    printf("Time executed: %.4f\n", time);
    printf("Moves needed: %d", count); 
    freeStack(source);
    freeStack(storage);
    freeStack(dest);
    
    return 0;
}
