#include <stdio.h>
#include <stdlib.h>

#define MAX 100

typedef struct Node {
    int data;
    struct Node* left;
    struct Node* right;
} Node;

typedef struct Queue {
    int items[MAX];
    int front, rear;
} Queue;

Node* createNode(int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = value;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

Node* insert(Node* root, int value) {
    if (root == NULL) {
        return createNode(value);
    }
    if (value < root->data) {
        root->left = insert(root->left, value);
    } else {
        root->right = insert(root->right, value);
    }
    return root;
}

void preOrder(Node* root) {
    if (root != NULL) {
        printf("%d ", root->data);
        preOrder(root->left);
        preOrder(root->right);
    }
}

void inOrder(Node* root) {
    if (root != NULL) {
        inOrder(root->left);
        printf("%d ", root->data);
        inOrder(root->right);
    }
}

void postOrder(Node* root) {
    if (root != NULL) {
        postOrder(root->left);
        postOrder(root->right);
        printf("%d ", root->data);
    }
}

void initializeGraph(int adjacencyList[MAX][MAX], int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            adjacencyList[i][j] = 0;
        }
    }
}

void addEdge(int adjacencyList[MAX][MAX], int u, int v) {
    adjacencyList[u][v] = 1;
    adjacencyList[v][u] = 1;
}

void convertTreeToGraph(Node* root, int adjacencyList[MAX][MAX]) {
    if (root == NULL) {
        return;
    }
    if (root->left != NULL) {
        addEdge(adjacencyList, root->data, root->left->data);
        convertTreeToGraph(root->left, adjacencyList);
    }
    if (root->right != NULL) {
        addEdge(adjacencyList, root->data, root->right->data);
        convertTreeToGraph(root->right, adjacencyList);
    }
}

void DFS(int start, int visited[], int adjacencyList[MAX][MAX], int size) {
    printf("%d ", start);
    visited[start] = 1;
    for (int i = 0; i < size; i++) {
        if (adjacencyList[start][i] == 1 && !visited[i]) {
            DFS(i, visited, adjacencyList, size);
        }
    }
}

void enqueue(Queue* q, int value) {
    if (q->rear == MAX - 1) return;
    if (q->front == -1) q->front = 0;
    q->rear++;
    q->items[q->rear] = value;
}

int dequeue(Queue* q) {
    if (q->front == -1) return -1;
    int item = q->items[q->front];
    q->front++;
    if (q->front > q->rear) q->front = q->rear = -1;
    return item;
}

int isEmpty(Queue* q) {
    return q->front == -1;
}

void BFS(int start, int visited[], int adjacencyList[MAX][MAX], int size) {
    Queue q;
    q.front = q.rear = -1;

    enqueue(&q, start);
    visited[start] = 1;

    while (!isEmpty(&q)) {
        int current = dequeue(&q);
        printf("%d ", current);
        for (int i = 0; i < size; i++) {
            if (adjacencyList[current][i] == 1 && !visited[i]) {
                enqueue(&q, i);
                visited[i] = 1;
            }
        }
    }
}

int main() {
    Node* root = NULL;
    int n, value;

    printf("Nhap so luong nut: ");
    scanf("%d", &n);

    printf("Nhap gia tri cac nut: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &value);
        root = insert(root, value);
    }

    printf("Duyet Pre-Order: ");
    preOrder(root);
    printf("\n");

    printf("Duyet In-Order: ");
    inOrder(root);
    printf("\n");

    printf("Duyet Post-Order: ");
    postOrder(root);
    printf("\n");

    int adjacencyList[MAX][MAX];
    initializeGraph(adjacencyList, MAX);
    convertTreeToGraph(root, adjacencyList);

    int visited[MAX] = {0};
    printf("Duyet DFS: ");
    DFS(root->data, visited, adjacencyList, MAX);
    printf("\n");

    for (int i = 0; i < MAX; i++) visited[i] = 0;

    printf("Duyet BFS: ");
    BFS(root->data, visited, adjacencyList, MAX);
    printf("\n");

    return 0;
}
