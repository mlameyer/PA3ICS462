/* 
 * File:   main.cpp
 * Author: mlameyer <hu2824uo@metrostate.com>
 *
 * Created on October 30, 2015, 10:34 AM
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MINIMUM_ALLOC 0x02
#define NUM_ALLOCS 0x07f

using namespace std;

/*
 * 
 */
unsigned char mySpace[MINIMUM_ALLOC * NUM_ALLOCS];

void hexDump (char *desc, void *addr, int len) ;

unsigned char *myMalloc(int size)
{
    //printf("value of size = %i\n", size);
    int continueWhile = 1;
    int i = 0;
    int block = size + MINIMUM_ALLOC;
    unsigned char value;
    unsigned char *ptr;
    
    ptr = &mySpace[i];
    
    while(continueWhile == 1)
    {
        value = mySpace[i];
        //printf("value of value = %i\n", value);
        if(value > '\x0f')
        {
           mySpace[i] = block;
           ptr = &mySpace[i];
           i = i + block;
           mySpace[i] = 255 - i;
           continueWhile = 0;
        }
        else
        {
            i = i + (int)value;
            //printf("value of i = %i\n", i);
        }
    }
    
    return ptr;
   
}


void myFree(unsigned char *buffer)
{
    //printf("Value of *buffer variable: %d\n", *buffer );
    unsigned char value;
    
    value = *buffer;
    //printf("Value of value variable: %i\n", value );
    *buffer = '\x80' + value;
}

/* space is a pointer to space you have allocated 

Example to allocate an array of space, assuming size is how big your buffers are and count is how many buffers:

int size = 1;
int count = 32000;
unsigned char space[size * count];
*/

void init(unsigned char *space, int size, int count)
{
    printf("Initializing %i memory\n", count);
    space[size * count];
    for (int i = 0; i < size * count; i++ ) 
    {
        if(i == 0)
        {
            space[i] = '\xff';
        }
        else
        {
           space[ i ] = '\xaa';
        } 
    }
/*    
    for (int j = 0; j < size * count; j++ ) 
    {
      printf("Element[%d] = %d\n", j, space[j] );
    }
*/
}
 
/* this should return how much space is allocated, in bytes not blocks */
int totalAllocated() 
{
    unsigned char value;
    int allocatedBytes = 0;
    
    for(int i = 0; i < MINIMUM_ALLOC * NUM_ALLOCS; i++)
    {
        value = mySpace[i];
        int k = value >> 4;
        //printf("Value of value: %x\n", k );
        if(k == '\x0')
        {
           allocatedBytes = allocatedBytes + value; 
        }
    }
    
    return allocatedBytes;
}

/* this should return how much space is free, in bytes not blocks */
int  totalFree() 
{
    unsigned char value;
    int freeBytes = 0;
    
    for(int i = 0; i < MINIMUM_ALLOC * NUM_ALLOCS; i++)
    {
        value = mySpace[i];
        int k = value >> 4;
        if(k == '\x0')
        {
           freeBytes = freeBytes + value; 
        }
    }
    
    return NUM_ALLOCS - freeBytes;
}

/* this routine should return the largest buffer available */
int largestAvailable() 
{
 /* your code goes here */
 return 0;  /* replace this */
}


/* this routine should return the size in bytes of the smallest buffer available */
int smallestAvailable() 
{
/* your code goes here */
 return 0;  /* replace this */
}


int main(int argc, char * argv[])
{
    unsigned char *ptr, *ptr2, *ptr3;
    
    printf("My main is working \n");
    
    printf("Init \n");

    init(mySpace, MINIMUM_ALLOC, NUM_ALLOCS);
    //printf("Address stored in mySpace variable: %x\n", mySpace );
    //printf("Value of *mySpace variable: %d\n", *mySpace );

    hexDump ("my buf",mySpace, 0x20 );
  
    ptr = myMalloc(3);

    hexDump ("my buf",mySpace, 0x20 );

    ptr2 = myMalloc(1);

    hexDump ("my buf",mySpace, 0x20 );

    ptr3= myMalloc(4);

    hexDump ("my buf",mySpace, 0x20 );

    printf("Total allocated %d \n", totalAllocated() * MINIMUM_ALLOC);

    printf("Total free %d \n", totalFree() * MINIMUM_ALLOC);

    myFree(ptr);

    myFree(ptr2);

    myFree(ptr3);

    hexDump ("my buf",mySpace, 0x20 );

    printf("Total allocated %d \n", totalAllocated() * MINIMUM_ALLOC);

    printf("Total free %d \n", totalFree() * MINIMUM_ALLOC);

    hexDump ("my buf",mySpace, 0x20 );
    
}



/* thank you stackoverflow */
/* http://stackoverflow.com/questions/7775991/how-to-get-hexdump-of-a-structure-data */

void hexDump (char *desc, void *addr, int len) 
{
    int i;
    unsigned char buff[17];
    unsigned char *pc = (unsigned char*)addr;

    // Output description if given.
    if (desc != NULL)
        printf ("%s:\n", desc);

    // Process every byte in the data.
    for (i = 0; i < len; i++) {
        // Multiple of 16 means new line (with line offset).

        if ((i % 16) == 0) {
            // Just don't print ASCII for the zeroth line.
            if (i != 0)
                printf ("  %s\n", buff);

            // Output the offset.
            printf ("  %04x ", i);
        }

        // Now the hex code for the specific character.
        printf (" %02x", pc[i]);

        // And store a printable ASCII character for later.
        if ((pc[i] < 0x20) || (pc[i] > 0x7e))
            buff[i % 16] = '.';
        else
            buff[i % 16] = pc[i];
        buff[(i % 16) + 1] = '\0';
    }

    // Pad out last line if not exactly 16 characters.
    while ((i % 16) != 0) {
        printf ("   ");
        i++;
    }

    // And print the final ASCII bit.
    printf ("  %s\n", buff);
}

