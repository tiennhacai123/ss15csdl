#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node {
    int vertex;
    struct Node* next;
} Node;

typedef struct Graph {
    int numVertices;
    Node** adjLists;
    bool* visited;
} Graph;

Node* createNode(int v) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->vertex = v;
    newNode->next = NULL;
    return newNode;
}

Graph* createGraph(int vertices) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->numVertices = vertices;
    graph->adjLists = (Node**)malloc(vertices * sizeof(Node*));
    graph->visited = (bool*)malloc(vertices * sizeof(bool));

    for (int i = 0; i < vertices; i++) {
        graph->adjLists[i] = NULL;
        graph->visited[i] = false;
    }
    return graph;
}

void addEdge(Graph* graph, int src, int dest) {
    Node* newNode = createNode(dest);
    newNode->next = graph->adjLists[src];
    graph->adjLists[src] = newNode;

    newNode = createNode(src);
    newNode->next = graph->adjLists[dest];
    graph->adjLists[dest] = newNode;
}

void BFS(Graph* graph, int startVertex, int targetVertex) {
    int* prev = (int*)malloc(graph->numVertices * sizeof(int));
    for (int i = 0; i < graph->numVertices; i++) {
        prev[i] = -1;
    }

    int queue[graph->numVertices];
    int front = 0, rear = 0;

    graph->visited[startVertex] = true;
    queue[rear++] = startVertex;

    while (front < rear) {
        int currentVertex = queue[front++];
        Node* temp = graph->adjLists[currentVertex];

        while (temp) {
            int adjVertex = temp->vertex;
            if (!graph->visited[adjVertex]) {
                graph->visited[adjVertex] = true;
                prev[adjVertex] = currentVertex;
                queue[rear++] = adjVertex;

                if (adjVertex == targetVertex) {
                    front = rear; 
                    break;
                }
            }
            temp = temp->next;
        }
    }

    if (prev[targetVertex] != -1) {
        printf("Duong di ngan nhat tu %d den %d la: ", startVertex, targetVertex);
        int path[graph->numVertices];
        int count = 0;
        for (int at = targetVertex; at != -1; at = prev[at]) {
            path[count++] = at;
        }
        for (int i = count - 1; i >= 0; i--) {
            printf("%d ", path[i]);
        }
        printf("\n");
    } else {
        printf("Khong co duong di tu %d den %d.\n", startVertex, targetVertex);
    }

    free(prev);
}

int main() {
    int vertices, edges;
    printf("Nhap so dinh: ");
    scanf("%d", &vertices);
    printf("Nhap so canh: ");
    scanf("%d", &edges);

    Graph* graph = createGraph(vertices);

    printf("Nhap cac canh (u, v):\n");
    for (int i = 0; i < edges; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        addEdge(graph, u, v);
    }

    int startVertex, targetVertex;
    printf("Nhap dinh bat dau: ");
    scanf("%d", &startVertex);
    printf("Nhap dinh dich: ");
    scanf("%d", &targetVertex);

    BFS(graph, startVertex, targetVertex);

    return 0;
}
