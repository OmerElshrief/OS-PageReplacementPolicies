#ifndef _Pages
#define _Pages


#include <stdio.h>
#include <stdlib.h>
#include "memory.h"
#include "Clock.h"




Memory *memory;

int initialize_Clock(int numberOfPages){

    memory = (Memory *)malloc(sizeof(Memory));
    memory->pages = (int *)malloc(sizeof(int) * numberOfPages);
    memory->lru = (int *)malloc(sizeof(int) * numberOfPages);
    memory->capacity = numberOfPages;
    memory->size=0;
    memory->lru_index = 0;
    
}

int getPage_Clock(int pageReference)
{
    
    // First check3 if the memory already contains the Page reference;
    int index = contain(memory,pageReference);
    
    if (index !=-1) //The Pagereference is Found
    {
       // //printf("Page Reference found index is: %d\n", index);
        memory->lru[index]=1; // Increse the Frequency of the Page reference
        return PAGE_SUCCESS; // Return Page success
    }

    // If the memory is NotFull then insert the new pages and return PageFault
    if (!isFull(memory)){
        
        memory->pages[memory->size] = pageReference;    
        memory->lru[memory->size++]  = 1;  //This for the Least Recently used Mark
        
        return PAGE_SUCCESS;
    } else
    { // If the Memory is full, we then get the least recently used Page reference and replace it.
       
        int lruIndex = getLeastRecentlyUsed(memory); // Fetch the Least recently used Page.
        //printf("memry is full, replacing index: %d\n", memory->lru_index);
        memory->pages[lruIndex] = pageReference;
        
       // printf("LRU_index is now poiting at %d \n", memory->lru_index);

        return PAGE_FAULT;  // Return PageFault
    }


}





int isFull(Memory *memory){
    return memory->size==memory->capacity;
}



int getLeastRecentlyUsed(Memory *memory){

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
    for (i = memory->lru_index ; i < memory->capacity; i = (i + 1) % memory->capacity)
    {
        if(memory->lru[i] ==0)
            {
                memory->lru[i] = 1;
                memory->lru_index = (i + 1) % memory->capacity; // LRU_index points to next page
                return i;
            }
        memory->lru[i]=0;
    }
    return -1;
}



int contain(Memory *memory , int pageReference){

    for(int i=0;i<memory->size;i++)
    {
        if(memory->pages[i] == pageReference)
            return i;
    }

    return -1;

}



int* getmemory()
{
    return memory->pages;
}


int getSize(){
return memory->size;
}
#endif