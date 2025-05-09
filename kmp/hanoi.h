#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
    int value;
    struct Node* next;
}Node;

typedef struct Stack{
    int capacity;
    Node* top;
    Node** disks;
    int top_index;    
}Stack;
