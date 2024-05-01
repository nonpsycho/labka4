#include "task2.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct ParkingLot {
    int totalSpots;
    int freeSpots;
    char** carNumbers;
    struct ParkingLot* next;
} ParkingLot;

typedef struct {
    ParkingLot* front;
    ParkingLot* rear;
} Queue;

Queue* CreateQueue() {
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    if (queue == NULL)
    {
        printf("Error.Failed to allocate memory\n");
        exit(EXIT_FAILURE);
    }
    queue->front = NULL;
    queue->rear = NULL;
    return queue;
}

int isQueueEmpty(Queue* queue) {
    return (queue->front == NULL);
}

void Enqueue(Queue* queue, ParkingLot* parkingLot) {
    parkingLot->next = NULL;

    if (isQueueEmpty(queue)) {
        queue->front = parkingLot;
        queue->rear = parkingLot;
    }
    else {
        queue->rear->next = parkingLot;
        queue->rear = parkingLot;
    }
}

ParkingLot* Dequeue(Queue* queue) 
{
    if (isQueueEmpty(queue)) 
    {
        return NULL;
    }

    ParkingLot* temp = queue->front;
    queue->front = queue->front->next;

    if (queue->front == NULL) 
    {
        queue->rear = NULL;
    }

    return temp;
}

void SecondTask() 
{
    Queue* queue = CreateQueue();
    //COMMING SOON
}