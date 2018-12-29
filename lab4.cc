

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define PAGE_FAULT 1
#define PAGE_SUCCESS 0
#define PAGE_FOUND 1
#define PAGE_NOT_FOUND  0

typedef struct
{
    int front, rear, size;
    unsigned capacity;
    int *array;
} Memory_Queue;


typedef struct
{
    int *pages;
    int *lru;
    unsigned int capacity;
    int size;
    int lru_index;
} Memory;


typedef struct page
{
    int data;
    struct page *next;
} Page;

void append(Page **head_ref, int new_data);

void print(int *arr, int size);

void printList(Page *n);

/*
    Function to add new Page
    Return 1 for PageFault
            0 For Success
*/
int contain(Memory *memory, int pageReference);

/*
    Initialization fucntion for the Clocck Policy
*/
int initialize_Clock(int numberOfPages);

/*
    Function to fetch a Page from memory
*/
int getPage(int pageReference);

/*
    Function to Check if the memory is full of pages
    Returns 1 if Full
            0 if notFull
*/
int isFull(Memory *memory);

/*
    Function to get teh index of the Least recently used page reference in memory
*/
int getLeastRecentlyUsed(Memory *memory);

/*
    Function to check wether the Page reference already exist in memory or not;
    Return  the index of the PageReference if exists
            -1 if not; 
*/
int contain(Memory *memory, int pageReference);

/*
    Function that returns the Elements in the memory
*/



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

int contain_LRU(Memory *memory_LRU, int pageReference);
int initialize_LRU(int numberOfPages);
int getPage_LRU(int pageReference);
int isFull_LRU(Memory *memory_LRU);
int getLeastRecentlyUsed_LRU(Memory *memory_LRU);
int contain_LRU(Memory *memory_LRU, int pageReference);
int *getmemory_LRU();
int getSize_LRU();
int  getSize();
int getPage_Clock(int pageReference);
int getSize_FIFO();
int *getmemory();

    Memory *memory_LRU;
Memory *memory;
Memory_Queue *memory_Queue;
int counter = 0;

int main()
{

    int input, numberOfPages=0, index = 0, faults = 0;
    int result;
    char type[5];
    int qPage, LRUPages;
    Page *page_References = NULL;

    scanf("%d", &numberOfPages);
    LRUPages = qPage = numberOfPages;
    scanf(" %s", type);
    getchar();

    //
    scanf("%d", &input);

    while (input != -1)
    {

        append(&page_References, input);

        scanf("%d", &input);
    }

    printf("Replacement Policy = %s\n-------------------------------------\nPage   Content of Frames\n----   -----------------\n", &type);

    if (strcmp("FIFO", type) == 0)
    {
       

        initialize_FIFO(numberOfPages);

        while (page_References != NULL)
        {
            int page = page_References->data;
            page_References = page_References->next;
            result = getPage_FIFO(page);
            int *memory = getMemory_FIFO();

            if (result == PAGE_FAULT)
            {
                printf("%02d F   ", page);
                faults++;
            }
            else
                printf("%02d     ", page);
            for (int i = 0; i < getSize_FIFO(); i++)
            {
                printf("%02d ", memory[i]);
            }
            printf("\n");
        }
    }
    else if (strcmp("CLOCK", type) == 0)
    {
        

        
        initialize_Clock(qPage);
        int page;
        while (page_References != NULL)
        {
            page = page_References->data;
            page_References = page_References->next;
            result = getPage_Clock(page);
            int *memory = getmemory();
            
            if (result == PAGE_FAULT)
            {
                printf("%02d F   ", page);
                faults++;
            }
            else
                printf("%02d     ", page);
            for (int i = 0; i < getSize(); i++)
            {
                printf("%02d ", memory[i]);
            }
            printf("\n");
        }
    }
    
    else if (strcmp("LRU", type) == 0)
    {
       
        initialize_LRU(qPage);
       
        int page;
        while (page_References != NULL)
        {
            page = page_References->data;
            page_References = page_References->next;
            result = getPage_LRU(page);
            int *memory = getmemory_LRU();

            if (result == PAGE_FAULT)
            {
                printf("%02d F   ", page);
                faults++;
            }
            else
                printf("%02d     ", page);
            for (int i = 0; i < getSize_LRU(); i++)
            {
                printf("%02d ", memory[i]);
            }
            printf("\n");
        }
    }
    printf("-------------------------------------\nNumber of page faults = %d\n", faults);
    faults = 0;

    return 0;
}

void append(Page **head_ref, int new_data)
{

    /* 1. allocate node */
    Page *new_node = (Page *)malloc(sizeof(Page));

    Page *last = *head_ref; /* used in step 5*/

    /* 2. put in the data  */
    new_node->data = new_data;

    /* 3. This new node is going to be the last node, so make next  
          of it as NULL*/
    new_node->next = NULL;

    /* 4. If the Linked List is empty, then make the new node as head */
    if (*head_ref == NULL)
    {
        *head_ref = new_node;
        return;
    }

    /* 5. Else traverse till the last node */
    while (last->next != NULL)
        last = last->next;

    /* 6. Change the next of last node */
    last->next = new_node;
    return;
}

void printList(Page *n)
{
    while (n != NULL)
    {
        printf(" %d ", n->data);
        n = n->next;
    }
}

int initialize_Clock(int numberOfPages)
{

    memory = (Memory *)malloc(sizeof(Memory));
    memory->pages = (int *)malloc(sizeof(int) * numberOfPages);
    memory->lru = (int *)malloc(sizeof(int) * numberOfPages);
    memory->capacity = numberOfPages;
    memory->size = 0;
    memory->lru_index = 0;
}

int getPage_Clock(int pageReference)
{

    // First check3 if the memory already contains the Page reference;
    int index = contain(memory, pageReference);

    if (index != -1) //The Pagereference is Found
    {
        // //printf("Page Reference found index is: %d\n", index);
        memory->lru[index] = 1; // Increse the Frequency of the Page reference
        return PAGE_SUCCESS;    // Return Page success
    }

    // If the memory is NotFull then insert the new pages and return PageFault
    if (!isFull(memory))
    {

        memory->pages[memory->size] = pageReference;
        memory->lru[memory->size++] = 1; //This for the Least Recently used Mark

        return PAGE_SUCCESS;
    }
    else
    { // If the Memory is full, we then get the least recently used Page reference and replace it.

        int lruIndex = getLeastRecentlyUsed(memory); // Fetch the Least recently used Page.
        //printf("memry is full, replacing index: %d\n", memory->lru_index);
        memory->pages[lruIndex] = pageReference;

        // printf("LRU_index is now poiting at %d \n", memory->lru_index);

        return PAGE_FAULT; // Return PageFault
    }
}

int isFull(Memory *memory)
{
    return memory->size == memory->capacity;
}

int getLeastRecentlyUsed(Memory *memory)
{

    int i;

    // First we iterate through the array to find a non marked Page reference
    // for (i = memory->lru_index; i < memory->capacity + memory->lru_index ; i++)
    // {
    //     if (memory->lru[i % memory->capacity] == 0)
    //     {
    //         memory->lru[i % memory->capacity] = 1;
    //         memory->lru_index = (i + 1) % memory->capacity; // LRU_index points to next page
    //         return i;
    //     }

    // }

    // If no non-marked reference, then UnMark all references
    for (i = memory->lru_index; i < memory->capacity; i = (i + 1) % memory->capacity)
    {
        if (memory->lru[i] == 0)
        {
            memory->lru[i] = 1;
            memory->lru_index = (i + 1) % memory->capacity; // LRU_index points to next page
            return i;
        }
        memory->lru[i] = 0;
    }
    return -1;
}

int contain(Memory *memory, int pageReference)
{

    for (int i = 0; i < memory->size; i++)
    {
        if (memory->pages[i] == pageReference)
            return i;
    }

    return -1;
}

int *getmemory()
{
    return memory->pages;
}

int getSize()
{
    return memory->size;
}

void initialize_FIFO(int numberofPages)
{
    memory_Queue = (Memory_Queue *)malloc(sizeof(Memory_Queue));
    memory_Queue->capacity = numberofPages;
    memory_Queue->size = 0;
    memory_Queue->front = 0;
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

int *getMemory_FIFO()
{
    return memory_Queue->array;
}

int getSize_FIFO()
{
    return memory_Queue->size;
}
int initialize_LRU(int numberOfPages)
{

    memory_LRU = (Memory *)malloc(sizeof(Memory));
    memory_LRU->pages = (int *)malloc(sizeof(int) * numberOfPages);
    memory_LRU->lru = (int *)malloc(sizeof(int) * numberOfPages);
    memory_LRU->capacity = numberOfPages;
    memory_LRU->size = 0;
    memory_LRU->lru_index = 0;
}

/*
    Function to add new Page
    Return 1 for PageFault
            0 For Success
*/
int getPage_LRU(int pageReference)
{

    // First check3 if the memory_LRU already contains the Page reference;
    int index = contain_LRU(memory_LRU, pageReference);
    //printf("\ncontain Index : %d \n",index);
    if (index != -1) //The Pagereference is Found
    {
        //  printf("Page Reference found index is: %d\n", index);
        memory_LRU->lru[index] = ++counter; // Increse the Frequency of the Page reference

        return PAGE_SUCCESS; // Return Page success
    }

    // If the memory_LRU is N otFull then insert the new pages and return PageFault
    if (!isFull_LRU(memory_LRU))
    {
        // printf("Memory is not full, inserting: %d\n", index);
        memory_LRU->pages[memory_LRU->size] = pageReference;

        memory_LRU->lru[memory_LRU->size++] = ++counter; //This for the Least Recently used Mark

        return PAGE_SUCCESS;
    }
    else
    { // If the Memory is full, we then get the least recently used Page reference and replace it.

        int lruIndex = getLeastRecentlyUsed_LRU(memory_LRU); // Fetch the Least recently used Page.
                                                             //   printf("memry is full, replacing index: %d\n", lruIndex);
        memory_LRU->pages[lruIndex] = pageReference;
        memory_LRU->lru[lruIndex] = ++counter;

        // printf("LRU_index is now poiting at %d", memory_LRU->lru_index);

        return PAGE_FAULT; // Return PageFault
    }
}

/*
    Function to Check if the memory_LRU is full of pages
    Returns 1 if Full
            0 if notFull
*/
int isFull_LRU(Memory *memory_LRU)
{
    return memory_LRU->size == memory_LRU->capacity;
}

/*
    Function to get teh index of the Least recently used page reference in memory_LRU
*/
int getLeastRecentlyUsed_LRU(Memory *memory_LRU)
{

    int index = 0, minimum = memory_LRU->lru[0];

    // If no non-marked reference, then UnMark all references
    for (int i = 0; i < memory_LRU->capacity; i++)
    {
        if (memory_LRU->lru[i] < minimum)
        {
            minimum = memory_LRU->lru[i];
            index = i; // LRU_index points to next page
        }
    }
    return index;
}

/*
    Function to check wether the Page reference already exist in memory_LRU or not;
    Return  the index of the PageReference if exists
            -1 if not; 
*/
int contain_LRU(Memory *memory_LRU, int pageReference)
{

    for (int i = 0; i < memory_LRU->size; i++)
    {
        if (memory_LRU->pages[i] == pageReference)
            return i;
    }

    return -1;
}

/*
    Function that returns the Elements in the memory_LRU
*/
int *getmemory_LRU()
{
    return memory_LRU->pages;
}

int getSize_LRU()
{
    return memory_LRU->size;
}