#include <stdio.h>
#include <stdlib.h>
#include "fifo.h"


//Globel memory
Memory_Queue *memory_Queue;

void initialize_FIFO(int numberofPages)
{
    memory_Queue = (Memory_Queue *)malloc(sizeof(Memory_Queue));
    memory_Queue->capacity = numberofPages;
    memory_Queue->size = 0;
    memory_Queue->front =0;
    memory_Queue->rear = numberofPages - 1;
    memory_Queue->array = (int *)malloc(numberofPages * sizeof(int));
}


int getPage_FIFO(int pageNumber)
{
  //printf("\n  call Page %d \n",pageNumber);
    if (isEmpty_FIFO(memory_Queue))
    {   
        enmemory(memory_Queue, pageNumber);
        return PAGE_SUCCESS;
    }
    // Case if the Page reference already exists in the memory
    if (contains_FIFO(pageNumber, memory_Queue))
        return PAGE_SUCCESS;

    // IF the memory pages are all full
    if (!isFull_FIFO(memory_Queue))
    { // We first Dequeu
        enmemory(memory_Queue, pageNumber);
        return PAGE_SUCCESS;
    }

    // Enmemory the new page number and return page Fault;
    dememory(memory_Queue);
    enmemory(memory_Queue, pageNumber);
    return PAGE_FAULT;
}


int *gerFrames_FIFO()
{
    return memory_Queue->array;
}
// memory is full when size becomes equal to the capacity
int isFull_FIFO(Memory_Queue *memory)
{
    return (memory->size == memory->capacity);
}

// memory is empty when size is 0
int isEmpty_FIFO(Memory_Queue *memory)
{
    return (memory->size == 0);
}

void enmemory(Memory_Queue *memory, int item)
{
    if (isFull_FIFO(memory))
    { //printf("EnMemory is full");
        return;
    }
    memory->rear = (memory->rear + 1) % memory->capacity;
    memory->array[memory->rear] = item;
    memory->size = memory->size + 1;
    //printf("\n%d enmemoryd to memory\n", item);
}



int dememory(Memory_Queue *memory)
{
   
    if (isEmpty_FIFO(memory))
        return -1;
  //  printf("\n  call dememory %d \n");
    int item = memory->array[memory->front];
    memory->front = (memory->front + 1) % memory->capacity;
    memory->size = memory->size - 1;
    return item;
}


int contains_FIFO(int element, Memory_Queue *memory)
{
    if (isEmpty_FIFO(memory))
    {
        return 0;
    }
    int size = memory->size;

    for (int i = 0; i < size; i++)
    {
        if (memory->array[i] == element)
            return 1; //element Found
    }
    return 0; //Element not found
}

int* getMemory_FIFO(){
    return memory_Queue->array;

}

int getSize_FIFO(){
    return memory_Queue->size;
}



