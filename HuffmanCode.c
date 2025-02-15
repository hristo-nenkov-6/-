#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    char data;
    int freq;
    struct Node *left, *right;
} Node;

typedef struct Tree {
    int capacity;
    int size;
    Node** array;
} Tree;

void printArr(int arr[], int n);

Node* createNode(char data, int freq) {
    Node* newNode = (Node*)malloc(sizeof(Node));

    newNode->data = data;
    newNode->freq = freq;
    newNode->left = NULL;
    newNode->right = NULL;

    return newNode;
}

Tree* createTree(int capacity) {
    Tree* newTree = (Tree*)malloc(sizeof(Tree));

    newTree->capacity = capacity;
    newTree->array = (Node**)malloc(sizeof(Node) * capacity);
    newTree->size = 0;

    return newTree;
}

void fillTree(Tree* tree, char chars[], int freqs[], int size) {

    for(int i = 0; i < size; i++) {
        Node* newNode = createNode(chars[i], freqs[i]);
        tree->array[i] = newNode;
    }

    tree->size = size;
}

void insertionSort(Tree* tree) {
    for(int curr = 1; curr < tree->size; curr++) {
        Node* key = tree->array[curr];
        int j = curr - 1;

        while(j >= 0 && key->freq > tree->array[j]->freq) {
            tree->array[j+1] = tree->array[j];
            --j;
        }

        tree->array[j+1] = key;
    }
}

unsigned checkIfOne(Tree* tree) {
    if(tree->size == 1) {
        return true;
    }

    return false;
}

Node* getSmallest(Tree* tree) {
    return tree->array[--tree->size];
}

Node* createCombinedNode(Node* left, Node* right) {
    Node* combinedNode = createNode("", left->freq + right->freq);
    combinedNode->left = left;
    combinedNode->right = right;

    return combinedNode;
}

void insertCombinedNodeIntoTree(Node* node, Tree* tree) {
    tree->array[++tree->size - 1] = node;
}

Node* buildHuffmanTree(char chars[], int freqs[], int capcaity, int size) {
    Tree* tree = createTree(capcaity);
    fillTree(tree, chars, freqs, size);
    insertionSort(tree);

    while (!checkIfOne(tree)) {
        Node* left = getSmallest(tree);

        Node* right = getSmallest(tree);

        Node* combinedNode = createCombinedNode(left, right);
        insertCombinedNodeIntoTree(combinedNode, tree);

        insertionSort(tree);
    }

    return  tree->array[0];
}

unsigned isLeaf(Node* node) {
    if(node->left == NULL && node->right == NULL) {
        return true;
    }

    return false;
}

void printArr(int arr[], int n)
{
    int i;
    for (i = 0; i < n; ++i)
        printf("%d", arr[i]);

    printf("\n");
}

void printHoffmanTree(Node* rootNode, int arr[], int top) {
    if(rootNode->left) {
        arr[top] = 0;
        printHoffmanTree(rootNode->left, arr, top + 1);
    }

    if(rootNode->right) {
        arr[top] = 1;
        printArr(arr, top);
        printHoffmanTree(rootNode->right, arr, top + 1);
    }

    if(isLeaf(rootNode)) {
        printf("%c = ", rootNode->data);
        printf("\n");
    }
}

int main() {
    const char chars[] = {'a', 'b', 'c', 'd', 'e', 'f'};
    const int freqs[] = {5, 9, 12, 13, 16, 45};
    const int capacity = 6;

    int size = sizeof(chars) / sizeof(chars[0]);

    Node* hoffmanNode = buildHuffmanTree(chars, freqs, capacity, size);
    printHoffmanTree(hoffmanNode, freqs, 0);
}

