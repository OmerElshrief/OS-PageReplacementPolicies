
#include "Clock.c"
#include "fifo.c"
#include "LRU.C"
#include <stdio.h>
#include <string.h>

typedef struct
{
    int data;
    struct Page *next;
} Page;

void append(Page **head_ref, int new_data);

void print(int *arr, int size);

void printList(Page *n);

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