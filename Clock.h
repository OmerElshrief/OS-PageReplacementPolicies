#ifndef _ClockHeader
#define _ClockHeader
#include "memory.h"

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
void reset(Memory *memory);
#endif