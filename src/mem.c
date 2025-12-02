#include "../header/mem.h"

// local variables for mem.c/h only
static void** memMap;
static size_t blockLength;
static size_t blockPad;
static size_t count;
static size_t padding;
static bool init = false;
static size_t allocated;
static size_t blocks;

void initMem()
{
    debugmalloc_max_block_size(50 * 1024 * 1024);
    int initialSize = 500;
    memMap = malloc(initialSize * sizeof(*memMap));
    if (memMap == NULL)
    {
        fprintf(stderr, "SAFEMEM: Failed to allocate memory, sorry this is just my silly little gc acting up. exiting...\n");
        exit(ERROR_MEMORY);
    }

    blockLength = initialSize;
    blockPad = 500;
    padding = 100;
    count = 0;
    allocated = 0;
    blocks = 0;
    init = true;
}

void* safeMalloc(size_t size)
{
    if (!init)
    {
        fprintf(stderr, "Can't call safeMalloc() without first calling initMem(). exiting...\n");
        exit(ERROR_MEMORY);
    }

    else if (memMap == NULL)
    {
        fprintf(stderr, "Can't call safeMalloc() after freeAll(), if you want to use it call initMem() again. exiting...\n");
        exit(ERROR_MEMORY);
    }

    void* ptr = malloc(size);

    if (ptr == NULL)
    {
        fprintf(stderr, "Failed to allocate memory. exiting...\n");
        freeAll();
        memReport();
        exit(ERROR_MEMORY);
    }

    if (blockLength <= count)
    {
        grow();
    }

    memMap[count] = ptr;
    count++;
    allocated += size;
    blocks++;

    return ptr;
}

void grow()
{
    void** tmp; 
    tmp = realloc(memMap, (blockLength + blockPad) * sizeof((*tmp)));
    if (tmp == NULL)
    {
        fprintf(stderr, "SAFEMALLOC: Failed to increase the size of the block, sorry this is just my silly little gc acting up. exiting...\n");
        freeAll();
        memReport();
        exit(ERROR_MEMORY);
    }

    memMap = tmp;
    blockLength += blockPad;
}

void shrink()
{
    void** tmp;
    tmp = realloc(memMap, (blockLength - blockPad) * sizeof(*tmp));
    if (tmp == NULL)
    {
        fprintf(stderr, "SAFEFREE: Failed to decrease the size of the block, sorry this is just my silly little gc acting up. exiting...\n");
        freeAll();
        memReport();
        exit(ERROR_MEMORY);
    }

    memMap = tmp;
    blockLength -= blockPad;
}

void safeFree(void* ptr)
{
    if (ptr == NULL)
    {
        return;
    }

    else if (!init)
    {
        fprintf(stderr, "Can't call safeFree() without first calling initMem(). exiting...\n");
        exit(ERROR_MEMORY);
    }

    else if (memMap == NULL)
    {
        fprintf(stderr, "Can't call safeFree() after freeAll(), if you want to use it call initMem() again. exiting...\n");
        exit(ERROR_MEMORY);
    }

    for (size_t i = 0; i < count; i++)
    {
        if (memMap[i] == ptr)
        {
            free(ptr);
            count--;
            memMap[i] = memMap[count];

            if ((count + padding + blockPad) <= blockLength)
            {
                shrink();
            }

            return;
        }
    }

    fprintf(stderr, "The program tried to free a pointer not managed by gc, might be double free, or did you used plain free. exiting...\n");
    freeAll();
    memReport();
    exit(ERROR_MEMORY);
}

void freeAll()
{
    if (!init)
    {
        fprintf(stderr, "Can't call freeAll() without first calling initMem(). exiting...\n");
        exit(ERROR_MEMORY);
    }

    else if (memMap == NULL)
    {
        fprintf(stderr, "Can't call freeAll() more than once without a new initMem() before the call. exiting...\n");
        exit(ERROR_MEMORY);
    }

    for (size_t i = 0; i < count; i++)
    {
        free(memMap[i]);
    }

    free(memMap);

    memMap = NULL;
}

void memReport()
{
    if (memMap == NULL)
    {
        printf("**************************************************************\n");
        printf("* The debug malloc we have at home :3\n");
        printf("* No GC-managed memory leak detected\n");
        printf("* Total GC allocated %zu block, %zu byte.\n", blocks, allocated);
        printf("**************************************************************\n");
    }

    else
    {
        printf("**************************************************************\n");
        printf("* The debug malloc we have at home :3\n");
        printf("* Leaky memory detected\n");
        printf("* The number of unfreed memory block are: %zu \n", count);
        printf("* You really should call freeAll() at the end of your program\n");
        printf("**************************************************************\n");
    }
}