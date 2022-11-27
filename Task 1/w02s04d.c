/*
* File: Q2.c
* Title: Demonstrate the operation of a circular buffer.
* Version: 1.02
* Created: 20/10/2019
*
* Author: Brian 
*
* Copyright Brian 
*/

// A program to demonstrate the operation of a circular buffer.
//
// General description
// A circular buffer is a type of first-in first-out queue, normally fixed in length
// and is used as a temporary store of information that needs to be transmitted 
// asynchronously from one process to another.
//
// Implementation details
// The circular buffer holds messages entered by the user which are to be sent to
// the screen. The operation of the buffer is controlled by a menu from which the
// user can choose one of the following: enter a new message, send (consume) a 
// message from the buffer or display the contents of the buffer.
//
// The buffer is implemented as a fixed length array. Once all the elements in the 
// array have been filled, the first element will need to be used again. As an 
// example of the operation of the circular buffer, assume that there are 10 
// elements in the array, 9 messages have been entered by the producer, 6 have
// been consumed and then a further 5 are produced. The next message to be
// consumed (tail of the buffer) would be the 7th element in the array and the next 
// message entered (head of the buffer) would become the 5th element in the array.
//
// If the number of messages in the buffer is equal to the length of the array and
// a new message is entered, this simply overwrites the last message at the tail of
// the buffer. This is termed an overflow.
                                                             
#include <stdio.h>
 
// the format of the messages in the buffer
typedef struct {
  unsigned long index;  // index number of the data item
  unsigned char data;  // single byte of information to be sent
} Message;

// the length of the fixed array to be used for the FIFO buffer - must be at
// least one and no greater than half the maximum value allowed in an unsigned
// long (see the file limits.h)
#define BUFFER_LENGTH 10
 
// function prototypes
void Produce(Message buffer[], unsigned long *, unsigned long *);
void Consume(Message buffer[], unsigned long *, unsigned long *);
void Show(Message buffer[], unsigned long, unsigned long);

// Control the entering, sending and displaying of messages in the buffer.
// Arguments: None
// Returns: 0 on completion
int main()
{
  Message buffer[BUFFER_LENGTH];  // the message buffer
  unsigned long buffer_tail = 0;  // position of the tail in the message buffer -
                                  // the next message will be consumed from here
  unsigned long buffer_length = 0;  // number of messages in the buffer
  unsigned char UserInput;
                      
  // loop until the user wishes to exit
  while (1) {
    
    // show the menu of options
    printf("\n");
    printf("Buffer Management Menu\n");
    printf("----------------------\n");
    printf("1. Produce a new message for the buffer\n");
    printf("2. Consume a message from the buffer\n");
    printf("3. View the contents of the buffer\n");
    printf("4. Exit from the program\n\n");
    
    // get the user's choice
    printf("Enter your option: ");
    scanf("%hhu", &UserInput);
    printf("\n\n");
    
    // act on the user's input
    switch(UserInput) {
      case 1:
        Produce(buffer, &buffer_tail, &buffer_length);
        break;
      
      case 2:
        Consume(buffer, &buffer_tail, &buffer_length);
        break;
      
      case 3:
        Show(buffer, buffer_tail, buffer_length);
        break;

      case 4:
        return 0;

      default:
        printf("Invalid entry\n\n");
        break;
    }
  }
}

 
// Create a new message and add it to the head of the buffer.
// The data for the message is obtained from the user and the index from the
// static variable 'index' defined in this function. The variable 'index' is
// simply a count of the number of messages produced.
// Arguments:
//   (1) start of the buffer
//   (2) position of the tail of the buffer
//   (3) number of messages in the buffer
// Returns: void
void Produce(Message buffer[], unsigned long *buffer_tail, unsigned long *buffer_length)
{  
  static unsigned long index = 0; 

  // find the element of the buffer in which to store the message
  unsigned long buffer_head;
	//Find buffer head using buffer_length + buffer_tail,
	//Modulus operator is used to reset buffer_head if it exceeds size of buffer
	buffer_head = (*buffer_length + *buffer_tail) % BUFFER_LENGTH; 

  // get the value of the data for the message from the user
  printf("\nPlease input a Message to be stored: ");
	scanf("%hhu", &buffer[buffer_head].data);//write message to buffer with location buffer_head
 
	
  // get the value of the index for the message
	buffer[buffer_head].index = index; //write index to buffer with location buffer_head
	index++;
	
  // if no buffer overflow has occurred, adjust the buffer length
  if (*buffer_length < BUFFER_LENGTH ) //check if buffer overflow occurs
		{
		*buffer_length = *buffer_length + 1; //increment buffer
		printf("\n\n\n\nMessage stored in buffer successfully!\n");
		}

  // if a buffer overflow has occurred, display an error statement
  else
		{
		printf("\nError, Buffer Overflow Occured. Old data has been replaced with new data.\n");
		*buffer_tail = *buffer_tail + 1; //increment tail as buffer overflow has occured, head is automatically incremented in line 127
		}
}


// Pop the message at the head of the buffer and display it.
// Arguments:
//   (1) start of the buffer
//   (2) position of the tail of the buffer
//   (3) number of messages in the buffer
// Returns: void
void Consume(Message buffer[], unsigned long *buffer_tail, unsigned long *buffer_length)
{
  // if the buffer is empty, display an error statement
  if (*buffer_length == 0) //check if buffer is empty
		{
		printf("\nError, There is no data in buffer.\n");
		}
  
  // if the buffer is not empty, display the message at the tail, remove the
  // message by advancing the tail of buffer offset in a circular manner and
  // adjust the buffer length
  else
	{
		printf("\nMessage at tail : %hhu\n",buffer[*buffer_tail].data); //print message at tail
		*buffer_length = *buffer_length - 1; //decrement buffer length
		*buffer_tail = (*buffer_tail + 1) % BUFFER_LENGTH; //increment buffer tail and reset if it is larger than size of buffer
	}
	
	
}

 
// Display all of the messages in the buffer.
// Arguments:
//   (1) start of the buffer
//   (2) position of the tail of the buffer
//   (3) number of messages in the buffer
// Returns: void
void Show(Message buffer[], unsigned long buffer_tail, unsigned long buffer_length)
{
  unsigned long count; // count through the messages being displayed
  unsigned long buffer_head;  // the position the next message would be pushed
  
  // if the buffer is empty, display an error statement
  if (buffer_length == 0) //check if buffer is empty
		{
		printf("\nError, There is no data in buffer.\n");
		}  

  // if the buffer is not empty, display all the messages in the buffer
   else
	 {
		 count = buffer_tail;
		while (count<(buffer_length + buffer_tail))//keep pushing message until entire buffer is displayed
			{
				buffer_head = count % BUFFER_LENGTH;// Reset buffer_head if it exceeds buffer size
				printf("\nData %lu : %hhu",buffer_head,buffer[buffer_head].data); //print buffer index and data
				count++;//increment count
			}
	 }		 
}
