#include <stdio.h>
#include <stdlib.h>

#define MAX 100

typedef struct Node {
    int vertex;
    struct Node* next;
} Node;

typedef struct Graph {
    int numVertices;
    Node* adjLists[MAX];
} Graph;

typedef struct Queue {
    int items[MAX];
    int front, rear;
} Queue;

Graph* createGraph(int vertices) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->numVertices = vertices;
    for (int i = 0; i < vertices; i++) {
        graph->adjLists[i] = NULL;
    }
    return graph;
}

Node* createNode(int vertex) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->vertex = vertex;
    newNode->next = NULL;
    return newNode;
}

void addEdge(Graph* graph, int src, int dest) {
    Node* newNode = createNode(dest);
    newNode->next = graph->adjLists[src];
    graph->adjLists[src] = newNode;

    newNode = createNode(src);
    newNode->next = graph->adjLists[dest];
    graph->adjLists[dest] = newNode;
}

void DFS(Graph* graph, int vertex, int visited[]) {
    visited[vertex] = 1;
    printf("%d ", vertex);
    Node* temp = graph->adjLists[vertex];
    while (temp) {
        int connectedVertex = temp->vertex;
        if (!visited[connectedVertex]) {
            DFS(graph, connectedVertex, visited);
        }
        temp = temp->next;
    }
}

Queue* createQueue() {
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    queue->front = -1;
    queue->rear = -1;
    return queue;
}

int isEmpty(Queue* queue) {
    return queue->front == -1;
}

void enqueue(Queue* queue, int value) {
    if (queue->rear == MAX - 1) return;
    if (queue->front == -1) queue->front = 0;
    queue->items[++queue->rear] = value;
}

int dequeue(Queue* queue) {
    if (isEmpty(queue)) return -1;
    int item = queue->items[queue->front];
    if (queue->front >= queue->rear) {
        queue->front = queue->rear = -1;
    } else {
        queue->front++;
    }
    return item;
}

void BFS(Graph* graph, int startVertex, int visited[]) {
    Queue* queue = createQueue();
    visited[startVertex] = 1;
    enqueue(queue, startVertex);
    while (!isEmpty(queue)) {
        int currentVertex = dequeue(queue);
        printf("%d ", currentVertex);
        Node* temp = graph->adjLists[currentVertex];
        while (temp) {
            int connectedVertex = temp->vertex;
            if (!visited[connectedVertex]) {
                visited[connectedVertex] = 1;
                enqueue(queue, connectedVertex);
            }
            temp = temp->next;
        }
    }
}

int main() {
    int vertices, edges, src, dest, startVertex;
    printf("Nhap so dinh: ");
    scanf("%d", &vertices);
    printf("Nhap so canh: ");
    scanf("%d", &edges);

    Graph* graph = createGraph(vertices);
    for (int i = 0; i < edges; i++) {
        printf("Nhap canh (dinh1 dinh2): ");
        scanf("%d %d", &src, &dest);
        addEdge(graph, src, dest);
    }

    printf("Nhap dinh bat dau: ");
    scanf("%d", &startVertex);

    int visited[MAX] = {0};
    printf("DFS: ");
    DFS(graph, startVertex, visited);

    for (int i = 0; i < vertices; i++) visited[i] = 0;
    printf("\nBFS: ");
    BFS(graph, startVertex, visited);

    return 0;
}
