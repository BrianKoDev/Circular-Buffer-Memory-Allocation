/*
* File: Q3.c
* Title: Memory Allocation
* Version: 2.13
* Created: 30/10/2019
*
*/

// A program to implement a specific memory allocation solution for an embedded
// system
//
// General description
// This program implements memory allocated for two specific structures, named
// structA and structB. The program does not need to allocate memory for any 
// other any other data.

// The memory available for allocation is fixed at 2048 bytes. 

// A function my_alloc() can be called to request memory for a structure or array of 
// structures. The function should return the address of the memory allocated and
// function should indicate when memory cannot be allocated by returning 0.
//
// A function my_free() releases memory previously allocated using my_alloc().
// It does not check whether it is passed a valid address as this should be the 
// responsibility of the user of the function. 

#include <stdio.h>
#include <stdbool.h>

// portable types
#define uint8_t unsigned char
#define uint16_t unsigned short
#define uint32_t unsigned int
#define int32_t int


// the memory available for allocation
uint8_t memory[2048];
int32_t memory_avaliable = 2048; //Integer value of bytes avaliable for memory allocation

//define metadata structure to be store before allocated memory 
//contain address of top memory location and bottom memory location
typedef struct{  
  int32_t top_location;  
  int32_t bottom_location;      
} block;  

	
// the format of the two structures that can be allocated memory
typedef struct {
  uint32_t index;  // some index
  uint32_t value;  // some value
} structA;

typedef struct {
  uint32_t index;  // some index
  uint32_t red;  // some red value
  uint32_t green;  // some green value
  uint32_t blue;  // some blue value
} structB;

// prototypes of allocation functions
void* my_alloc(uint32_t);
void my_free(void*);

// Try some memory allocation tests
// Arguments: None
// Returns: 0 on completion
int main()
{
  structA *A1, *A10, *A40;
  structB *B1, *B80;
  A1 = (structA *)my_alloc(sizeof(structA));
  A10 = (structA *)my_alloc(10*sizeof(structA));
  A40 = (structA *)my_alloc(40*sizeof(structA));
  my_free((void *)A10);
  B1 = (structB *)my_alloc(sizeof(structB));
  B80 = (structB *)my_alloc(8990*sizeof(structB));
  my_free((void *)A1);
  my_free((void *)A40);
  my_free((void *)B1);
  my_free((void *)B80);

  return 0;
}

// Allocate memory in the 'memory' array
// Arguments:
//   (1) the number of bytes required
// Returns: the first address allocated
void* my_alloc(uint32_t bytes)
{ 
	if (memory_avaliable < (bytes + sizeof(block))) //check if there is enough memory
	{
		return 0;
	}
	else
	{
  block *current_block =(block *)&memory[0];  //set as first block in avaliable memory
	block *max_block = (block *)&memory[2048];	//set as last block in avaliable memory
		
		while (current_block < max_block) //loop through avaliable blocks
		{			
			//check if the current chuck of memory is big enough and check if current block is metadata
			if ((((bytes + sizeof (block) ) < ((current_block -> bottom_location) - (int32_t)current_block)) && (current_block->top_location==0))) 
			{
				current_block->bottom_location= (int32_t)current_block + sizeof(block)+bytes; //set bottom location to store the end address of this chunk of memory
				current_block->top_location = (int32_t)current_block + sizeof(block); //set top location to store the start address of this chunk of memory
				memory_avaliable = memory_avaliable - (bytes + sizeof(block)); //subtract memory avaliable
				return (int32_t *)current_block -> top_location;  //return pointer to main
			}		
			current_block = (block *)current_block -> bottom_location;  //jump to next block if this chunk does not have sufficient memory	
		}
	}
	return 0;
}


// Release memory allocated in the 'memory' array
// Arguments:
//   (1) the address of the first memory location to be freed
// Returns: nothing
void my_free(void* start)
{
  block *current_block = (block *) start;  //set block containing this memory chunk's location
  current_block--;  //decrement to access metadata
	int32_t memory_freed = (current_block -> bottom_location) - (current_block -> top_location);//Find size of memory that was allocated
	memory_avaliable = memory_freed + memory_avaliable + sizeof(block); 	//Add freed memory to variable
	current_block -> top_location = 0; //set block to be avaliable 
}
