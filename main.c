#include <stdio.h>
#include <stdlib.h>

#define MAX_PRIORITY 5

// Estructura para un nodo en la cola
typedef struct Node {
    int data;
    struct Node* next;
} Node;

// Estructura para la cola
typedef struct Queue {
    Node* front;
    Node* rear;
} Queue;

// Estructura para la cola con prioridad
typedef struct PriorityQueue {
    Queue queues[MAX_PRIORITY];
} PriorityQueue;

void initializePriorityQueue(PriorityQueue* pq) {
    for (int i = 0; i < MAX_PRIORITY; i++) {
        pq->queues[i].front = NULL;
        pq->queues[i].rear = NULL;
    }
}

void enqueue(PriorityQueue* pq, int data, int priority) {
    if (priority < 1 || priority > MAX_PRIORITY) {
        printf("Prioridad inválida\n");
        return;
    }
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;

    int index = priority - 1;
    if (pq->queues[index].rear == NULL) {
        pq->queues[index].front = newNode;
        pq->queues[index].rear = newNode;
    } else {
        pq->queues[index].rear->next = newNode;
        pq->queues[index].rear = newNode;
    }
    printf("Elemento %d encolado con prioridad %d\n", data, priority);
}

void dequeue(PriorityQueue* pq) {
    for (int i = 0; i < MAX_PRIORITY; i++) {
        if (pq->queues[i].front != NULL) {
            Node* temp = pq->queues[i].front;
            pq->queues[i].front = pq->queues[i].front->next;
            if (pq->queues[i].front == NULL) {
                pq->queues[i].rear = NULL;
            }
            printf("Elemento %d desencolado con prioridad %d\n", temp->data, i + 1);
            free(temp);
            return;
        }
    }
    printf("La cola con prioridad está vacía\n");
}

void display(PriorityQueue* pq) {
    for (int i = 0; i < MAX_PRIORITY; i++) {
        Node* temp = pq->queues[i].front;
        printf("Prioridad %d: ", i + 1);
        while (temp != NULL) {
            printf("%d -> ", temp->data);
            temp = temp->next;
        }
        printf("NULL\n");
    }
}

void menu() {
    PriorityQueue pq;
    initializePriorityQueue(&pq);

    int choice, data, priority;

    while (1) {
        printf("\nMenú:\n");
        printf("1. Insertar elemento\n");
        printf("2. Eliminar elemento\n");
        printf("3. Mostrar elementos\n");
        printf("4. Salir\n");
        printf("Ingrese su elección: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Ingrese el valor y la prioridad (1-5): ");
                scanf("%d %d", &data, &priority);
                enqueue(&pq, data, priority);
                break;
            case 2:
                dequeue(&pq);
                break;
            case 3:
                display(&pq);
                break;
            case 4:
                exit(0);
            default:
                printf("Elección inválida\n");
        }
    }
}

int main() {
    menu();
    return 0;
}