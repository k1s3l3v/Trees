#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#define COUNT 5

struct node {
    int key;
    struct node *left, *right;
};

struct node* root = NULL;

void print(struct node *node, int space)
{
    if (node == NULL)
        return;

    space += COUNT;

    print(node->right, space);

    printf("\n");
    for (int i = COUNT; i < space; i++)
        printf(" ");
    printf("%d\n", node->key);

    print(node->left, space);
}

void printTree(struct node *node)
{
    print(node, 0);
}

struct node* newNode(int item)
{
    struct node* temp = (struct node*)malloc(sizeof(struct node));
    temp->key = item;
    temp->left = temp->right = NULL;
    return temp;
}

struct node* add(struct node* node, int key)
{
    if (node == NULL)
        return newNode(key);

    if (key < node->key)
        node->left = add(node->left, key);
    else
        node->right = add(node->right, key);

    return node;
}

struct node* minNode(struct node* node)
{
    struct node* current = node;

    while (current && current->left != NULL)
        current = current->left;

    return current;
}

struct node* delete(struct node* node, int key)
{
    if (node == NULL)
        return node;
    if (key < node->key)
        node->left = delete(node->left, key);
    else if (key > node->key)
        node->right = delete(node->right, key);
    else {
        if (node->left == NULL) {
            struct node* temp = node->right;
            free(node);
            return temp;
        }
        else if (node->right == NULL) {
            struct node* temp = node->left;
            free(node);
            node = NULL;
            return temp;
        }
        struct node* temp = minNode(node->right);
        node->key = temp->key;
        node->right = delete(node->right, temp->key);
    }
    return node;
}

void printInorder(struct node* node)
{
    if (node == NULL)
        return;

    printInorder(node->left);
    printf("%d ", node->key);
    printInorder(node->right);
}

void printPostorder(struct node* node)
{
    if (node == NULL)
        return;

    printPostorder(node->left);
    printPostorder(node->right);
    printf("%d ", node->key);
}

void printPreorder(struct node* node)
{
    if (node == NULL)
        return;

    printf("%d ", node->key);
    printPreorder(node->left);
    printPreorder(node->right);
}

void deleteTree(struct node *node){
    if (node == NULL)
        return;

    deleteTree(node->left);
    deleteTree(node->right);
    free(node);
    root = NULL;
}

int main()
{
    int i = 0;
    while (i != 8) {
        puts("\nEnter the number of command\n\n  1. Add node\n  2. Delete node\n  3. Inorder traversal\n  "
             "4. Preorder traversal\n  5. Postorder traversal\n  6. Print the tree\n  7. Delete the tree\n  8. Exit");
        int k;
        if (scanf("%d", &i) != 1) {
            puts("You entered an invalid value");
            return 0;
        } else {
            switch (i) {
                case 1:
                    puts("Enter the key of node to insert");
                    if (scanf("%d", &k) != 1) {
                        puts("You entered an invalid value");
                        return 0;
                    }
                    root = add(root, k);
                    break;

                case 2:
                    puts("Enter the key of node to delete");
                    if (scanf("%d", &k) != 1) {
                        puts("You entered an invalid value");
                        return 0;
                    }
                    root = delete(root, k);
                    break;

                case 3:
                    printf("Inorder traversal:\n");
                    printInorder(root);
                    break;

                case 4:
                    printf("Preorder traversal:\n");
                    printPreorder(root);
                    break;

                case 5:
                    printf("Postorder traversal:\n");
                    printPostorder(root);
                    break;

                case 6:
                    printf("Tree:\n");
                    printTree(root);
                    break;

                case 7:
                    deleteTree(root);
                    printf("Tree is deleted\n");
                    break;

                case 8:
                    break;

                default:
                    puts("You entered an invalid value");
            }
        }
    }

    return 0;
}

