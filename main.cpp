/* 
 * File:   main.cpp
 * Author: mlameyer <hu2824uo@metrostate.com>
 *
 * Created on October 30, 2015, 10:34 AM
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MINIMUM_ALLOC 0x01 //minimum allocation of memory buffer
#define NUM_ALLOCS 0x07f // minimum number of buffers 

using namespace std;

/*
 * declared variable mySpace which is the memory buffer for allocating and 
 * freeing memory for myMalloc and myFree
 */
unsigned char mySpace[MINIMUM_ALLOC * NUM_ALLOCS];

//declaration of function hexDump to display results allocation and freeing memory
void hexDump (char *desc, void *addr, int len) ;

/*
 * declaration of function myMalloc to allocate memory from variable mySpace
 */
unsigned char *myMalloc(int size)
{
    printf("Allocating memory for size = %i\n", size);//print requested size to allocate
    int continueWhile = 1; //boolean to stop searching mySpace for available space
    int i = 0;//index location for traversing mySpace
    int block = size + MINIMUM_ALLOC;//variable to store selected buffer for allocation
    int checkBit = 0;//variable to store the left-most bit for comparison
    unsigned char value;//variable to store value from index location of mySpace
    unsigned char *ptr;//variable to store pointer and return for call to myFree
    
    ptr = &mySpace[i];//pointer set to address of index 0 of mySpace
    
    /*
     * While loop starts at beginning of mySpace and looks for available buffer to 
     * fit space requested from incoming parameter. reads beginning block and 
     * checks if it is free by performing a bit check of left most bit. If bit
     * is equal to 1 then the size requested is allocated and the next byte after
     * the last allocated byte is set to the remaining non allocated space. If
     * left most bit is not set to 1 then it moves to the next block per the
     * number of the block it just read to check if that left most bit is 1 and so on.  
     */
    while(continueWhile == 1)//continue until set to 0
    {
        value = mySpace[i];//value stored from index location from mySpace
        //left most value stored from value variable to do bit check
        checkBit = value >> 7;
        //printf("value of value = %x\n", value);
        //printf("value of value = %x\n", checkBit);
        if(checkBit == '\x1')//if left most bit equals 1
        {
            //size requested plus 1 is saved to current index position
            mySpace[i] = block;
            //pointer value to be returned for myFree function
            ptr = &mySpace[i];
            /*
             * allocation is finished and the first available byte of unallocated space
             * is set to i to then set the total remaining unallocated space
             */  
            i = i + block;
            mySpace[i] = 255 - i;//this is where the total remaining amount is written too
            continueWhile = 0;//allocation complete exit while loop
        }
        else //if check bit doesn't equal 1 continue through mySpace
        {
            /*
             * As each block is read the value from the block is used to set 
             * the next index position in mySpace to read and see if the next 
             * location read is free or used per the check bit
             */
             i = i + (int)value;
            //printf("value of i = %i\n", i);
        }
    }
    
    return ptr;//pointer return for local variables in main for use with myFree
   
}

/*
 * declaration of function myFree to deallocate memory from variable mySpace
 */
void myFree(unsigned char *buffer)
{
    //printf("Value of *buffer variable: %d\n", *buffer );
    unsigned char value; //variable to store actual value the pointer points to
    
    value = *buffer; //set variable to value the pointer points to 
    
    /* 
     * for loop sets 4 left most bits to 1000 binary to mark allocated
     * space as unallocated or free 
     */
    for(int i = 7; i > 3; i--)
    {
        if(i == 7)
        {
            /* 
             * symbol ^ bitwise XOR used to toggle left most bit i to 1
             * using the right shift to get to the proper bit to flip
             */
            value ^= (-1 ^ value) & (1 << i); //left most bit set to 1
        }
        else
        {
            /* 
             * symbol ^ bitwise XOR used to toggle left most bit i to 0
             * using the right shift to get to the proper bit to flip
             */
            value ^= (-0 ^ value) & (1 << i); //remaining 3 left most bits set to 0
        }
    }
    
    //printf("Value of value variable: %i\n", value );
    *buffer = value;//new value is saved to location pointer points to
}

/* space is a pointer to space you have allocated 

Example to allocate an array of space, assuming size is how big your buffers are and count is how many buffers:

int size = 1;
int count = 32000;
unsigned char space[size * count];
*/
/*
 * init initializes mySpace by crating a pointer to it and setting the 
 * initial values 
 */
void init(unsigned char *space, int size, int count)
{
    printf("Initializing %i memory\n", count);//print memory size to allocate
    space[size * count];//creating array of size * count
    //loop through new array and set default values
    for (int i = 0; i < size * count; i++ ) 
    {
        if(i == 0)//for index position 0 set to 255 decimal
        {
            space[i] = '\xff';
        }
        else//for all other index positions set to 170 decimal
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
    unsigned char value;//variable to store values from mySpace
    int allocatedBytes = 0;//variable to sum all allocated space
    
    //traverse mySpace and get sum of allocated space
    for(int i = 0; i < MINIMUM_ALLOC * NUM_ALLOCS; i++)
    {
        value = mySpace[i];//set value to value of index location in mySpace
        int k = value >> 7;//k is a check bit to test left most bit equal to 1
        //printf("Value of k: %x\n", k );
        /*
         * if true read value from index position and sum.
         * allocated space is assumed to be less then 255
         * so left most bit should not be equal to 1
         */
        if(k != '\x1')
        {
           allocatedBytes = allocatedBytes + value; 
        }
    }
    
    return allocatedBytes;//return sum
}

/* this should return how much space is free, in bytes not blocks */
int  totalFree() 
{
    unsigned char value; //variable to store values from mySpace
    int freeBytes = 0;//variable to sum all free space
    
    for(int i = 0; i < MINIMUM_ALLOC * NUM_ALLOCS; i++)
    {
        value = mySpace[i];//set value to value of index location in mySpace
        int k = value >> 7;//k is a check bit to test left most bit equal to 1
        /*
         * if true read value from index position and sum.
         * allocated space is assumed to be less then 255
         * so left most bit should not be equal to 1
         */
        if(k != '\x1')
        {
           freeBytes = freeBytes + value; 
        }
    }
    
    return NUM_ALLOCS - freeBytes;//return sum
}

/* this routine should return the largest buffer available */
int largestAvailable() 
{
    unsigned char value;//variable to store values from mySpace
    unsigned char check = 0;//variable compare previous and next value
    
    for(int i = 0; i < MINIMUM_ALLOC * NUM_ALLOCS; i++)
    {
        value = mySpace[i];//get current value at index
        int k = value >> 7;//check left most bit
        if(k == '\x1')//if left most bit is 1 then it is free space
        {
            if(value > check)//if value is larger then previous value set new value
            {
                check = value;
            } 
        }
    }
    
    return check;//return value
}


/* this routine should return the size in bytes of the smallest buffer available */
/* this function works the opposite of function largestAvaiable*/
int smallestAvailable() 
{
    unsigned char value;
    unsigned char check = 255;
    
    for(int i = 0; i < MINIMUM_ALLOC * NUM_ALLOCS; i++)
    {
        value = mySpace[i];
        int k = value >> 7;
        if(k == '\x1' || k == '\x8')
        {
            if(value < check)
            {
                check = value;
            } 
        }
    }
    
    return check;
}


int main(int argc, char * argv[])
{
    //pointers used to store address of allocated blocks from myMalloc
    unsigned char *ptr, *ptr2, *ptr3;
    
    printf("My main is working \n");
    
    printf("Init \n");

    //initialize mySpace with MINIMUM_ALLOC and NUM_ALLOCS to get array size
    init(mySpace, MINIMUM_ALLOC, NUM_ALLOCS);
    //printf("Address stored in mySpace variable: %x\n", mySpace );
    //printf("Value of *mySpace variable: %d\n", *mySpace );

    hexDump ("my buf",mySpace, 0x40 );
  
    //call to myMalloc passing size requested as parameter and return address to pointer
    ptr = myMalloc(16);

    hexDump ("my buf",mySpace, 0x40 );

    //call to myMalloc passing size requested as parameter and return address to pointer
    ptr2 = myMalloc(1);

    hexDump ("my buf",mySpace, 0x40 );

    //call to myMalloc passing size requested as parameter and return address to pointer
    ptr3= myMalloc(4);
    
    //calls to larget and smallest available and print results 
    printf("Largest Available: %i\n", largestAvailable());
    printf("Smallest Available: %i\n", smallestAvailable());

    hexDump ("my buf",mySpace, 0x40 );

    //get total allocated and print
    printf("Total allocated %d \n", totalAllocated() * MINIMUM_ALLOC);

    //get total free and print
    printf("Total free %d \n", totalFree() * MINIMUM_ALLOC);

    //call to myFree passing parameter of pointer 
    myFree(ptr);

    //call to myFree passing parameter of pointer
    myFree(ptr2);

    //call to myFree passing parameter of pointer
    myFree(ptr3);

    hexDump ("my buf",mySpace, 0x40 );

    //get total allocated and print
    printf("Total allocated %d \n", totalAllocated() * MINIMUM_ALLOC);
    
    //get total free and print
    printf("Total free %d \n", totalFree() * MINIMUM_ALLOC);

    hexDump ("my buf",mySpace, 0x40 );
    
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

