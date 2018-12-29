#ifndef _fifoHeader
#define _fifoHeader
#define PAGE_FAULT 1
#define PAGE_SUCCESS 0
#define PAGE_FOUND 1
#define PAGE_NOT_FOUND 0

typedef struct
{
    int front, rear, size;
    unsigned capacity;
    int *array;
} Memory_Queue;

/*
    Function to Intialize the FIFO Algorithm wi th the number of pages

*/
void initialize_FIFO(int numberofPages);

/*
    Function to get a Page from memory
    Input: pageNumber
    Return: 1 when Page fault
            0 When no Page fault
*/
int getPage_FIFO(int pageNumber);


/*
    Function to get memory frames
    Returns: Array of frames
*/

int *gerFrames_FIFO();

/*
 Function to add an item to the memory.
 It changes rear and size
*/
void enmemory(Memory_Queue *memoy, int item);

/*   
 Function to remove an item from memory.
 It changes front and size
*/
int dememory(Memory_Queue *memory);

/*
    Function to check if the Memory contains the Specific Element
*/
int contains_FIFO(int element, Memory_Queue *memory);

int isEmpty_FIFO(Memory_Queue *memory);

// memory is full when size becomes equal to the capacity
int isFull_FIFO(Memory_Queue *memory);

/*
    Function to get the Content of memory
*/
int *getMemory_FIFO();

#endif