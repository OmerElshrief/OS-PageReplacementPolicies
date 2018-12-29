

#include <stdio.h>
#include <stdlib.h>
#include "memory.h"

int contain_LRU(Memory *memory_LRU, int pageReference);
int initialize_LRU(int numberOfPages);
int getPage_LRU(int pageReference);
int isFull_LRU(Memory *memory_LRU);
int getLeastRecentlyUsed_LRU(Memory *memory_LRU);
int contain_LRU(Memory *memory_LRU, int pageReference);
int *getmemory_LRU();
int getSize_LRU();


Memory *memory_LRU;
int counter =0;

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
        memory_LRU->lru[lruIndex]= ++counter;
        
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

    int index=0,minimum = memory_LRU->lru[0];

    // If no non-marked reference, then UnMark all references
    for (int i =0; i < memory_LRU->capacity; i++)
    {
        if (memory_LRU->lru[i] < minimum)
        {
            minimum = memory_LRU->lru[i];
            index =i; // LRU_index points to next page
               
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

int getSize_LRU(){
    return memory_LRU->size;
}


