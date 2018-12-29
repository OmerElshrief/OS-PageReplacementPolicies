#ifndef _MEMORY
#define _MEMORY
#define PAGE_FAULT 1
#define PAGE_SUCCESS 0
#define PAGE_FOUND 1
#define PAGE_NOT_FOUND  0

typedef struct
{
    int *pages;
    int *lru;
    unsigned int capacity;
    int size;
    int lru_index;
} Memory;

#endif