#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
    int data;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

typedef struct Stack {
    TreeNode* data;
    struct Stack* next;
} Stack;

void push(Stack** top, TreeNode* node) {
    Stack* newNode = (Stack*)malloc(sizeof(Stack));
    newNode->data = node;
    newNode->next = *top;
    *top = newNode;
    printf("Push: %d\n", node->data);
}

TreeNode* pop(Stack** top) {
    if (*top == NULL) return NULL;
    Stack* temp = *top;
    TreeNode* node = temp->data;
    *top = (*top)->next;
    printf("Pop: %d\n", node->data);
    free(temp);
    return node;
}

void PlaceNode(TreeNode* node, int direction, int data) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;

    if (direction == 0) { 
        node->left = newNode;
    }
    else if (direction == 1) {
        node->right = newNode;
    }
}

void GenerateLinkTree(TreeNode* root) {
    PlaceNode(root, 0, 2); 
    PlaceNode(root, 1, 3); 
    PlaceNode(root->left, 0, 4); 
    PlaceNode(root->left, 1, 5);  
    PlaceNode(root->right, 0, 6); 
    PlaceNode(root->right, 1, 7);  
}

void LinkPreOrder(TreeNode* root) {
    if (root == NULL) return;

    Stack* stack = NULL;
    push(&stack, root);

    while (stack != NULL) {
        TreeNode* node = pop(&stack);
        printf("visit(%d)\n", node->data);

        if (node->right) push(&stack, node->right);
        if (node->left) push(&stack, node->left);
    }
}

void LinkInOrder(TreeNode* root) {
    Stack* stack = NULL;
    TreeNode* current = root;

    while (stack != NULL || current != NULL) {
        while (current != NULL) {
            push(&stack, current);
            current = current->left;
        }
        current = pop(&stack);
        printf("visit(%d)\n", current->data);
        current = current->right;
    }
}

void LinkPostOrder(TreeNode* root) {
    if (root == NULL) return;

    Stack* stack1 = NULL;
    Stack* stack2 = NULL;
    push(&stack1, root);

    while (stack1 != NULL) {
        TreeNode* node = pop(&stack1);
        push(&stack2, node);

        if (node->left) push(&stack1, node->left);
        if (node->right) push(&stack1, node->right);
    }

    while (stack2 != NULL) {
        TreeNode* node = pop(&stack2);
        printf("visit(%d)\n", node->data);
    }
}

void LinkOrders(TreeNode* root) {
    printf("PreOrder Traversal:\n");
    LinkPreOrder(root);
    printf("\n");

    printf("InOrder Traversal:\n");
    LinkInOrder(root);
    printf("\n");

    printf("PostOrder Traversal:\n");
    LinkPostOrder(root);
    printf("\n");
}

int main() {
    TreeNode* root = (TreeNode*)malloc(sizeof(TreeNode));
    root->data = 1;
    root->left = NULL;
    root->right = NULL;

    GenerateLinkTree(root);

    LinkOrders(root);

    return 0;
}
