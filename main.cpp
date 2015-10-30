/* 
 * File:   main.cpp
 * Author: mlameyer <mlameyer@mgex.com>
 *
 * Created on October 30, 2015, 10:34 AM
 */

#include <cstdlib>
#include <stdio.h>

unsigned char *mySpace;
int MINIMUM_ALLOC = 4;
int NUM_ALLOCS = 32000;
int MEMORYALLOCATED;


using namespace std;

/*
 * 
 */
void hexDump (char *desc, void *addr, int len) ;


unsigned char *myMalloc(int size)
{
/* your code goes here */
 return NULL;  /* replace this */
}


void myFree(unsigned char *buffer)
{
/* your code goes here */
}

/* space is a pointer to space you have allocated 

Example to allocate an array of space, assuming size is how big your buffers are and count is how many buffers:

int size = 1;
int count = 32000;
unsigned char space[size * count];
*/

void init(unsigned char *space, int size, int count)
{
    printf("%p \n", space);
    printf("%p \n", mySpace);
    mySpace = &space[size * count];
    printf("%p \n", space);
    printf("%p \n", mySpace);
/* your code goes here */
}
 
/* this should return how much space is allocated, in bytes not blocks */
int totalAllocated() 
{
  /* your code goes here */
    printf("Initializing %u memory \n", mySpace);
}

/* this should return how much space is free, in bytes not blocks */
int  totalFree() 
{
 /* your code goes here */
 return 0;  /* replace this */
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

    hexDump ("my buf",mySpace, 0x20 );
  
    ptr = myMalloc(3);

    hexDump ("my buf",mySpace, 0x20 );

    ptr2 = myMalloc(1);

    hexDump ("my buf",mySpace, 0x20 );

    ptr3= myMalloc(4);

    hexDump ("my buf",mySpace, 0x20 );

    printf("Total allocated %d \n", totalAllocated() * MINIMUM_ALLOC);

    printf("Total free %d \n", totalFree() *MINIMUM_ALLOC);

    myFree(ptr);

    myFree(ptr2);

    myFree(ptr3);

    hexDump ("my buf",mySpace, 0x20 );

    printf("Total allocated %d \n", totalAllocated() * MINIMUM_ALLOC);

    printf("Total free %d \n", totalFree() *MINIMUM_ALLOC);

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

