# Project Description
This project consists of various C code implementation of different applications and a report of system enginnering process in software enginnering.


[System Enginnering Process in Software](https://github.com/BrianKoDev/Electronic-Speed-Controller-for-BLDC/blob/main/Dissertation.pdf)

## Task 1
The program implements a circular buffer in C.


## Task 2

In an embedded system, use of the heap can cause unpredictable run-time performance and so memory is allocated from a fixed region in the global (uninitialized) memory region. 
The function my_alloc() that can be called to request memory for a structure or for an array of structures. The function returns the address of the memory allocated and function should indicate when memory cannot be allocated by returning the value 0. 
The function my_free() that releases memory previously allocated using my_alloc(). It does not check whether it is passed a valid address as this should be the responsibility of the user of the function. 
TAll memory allocated by the functions is obtained from the global array memory. The number of bytes available (in memory) is fixed at 2048. 