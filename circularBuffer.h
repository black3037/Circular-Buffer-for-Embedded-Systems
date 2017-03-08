#ifndef CIRCULAR_BUFFER_H
#define CIRCULAR_BUFFER_H

/* Includes */
#include "USART.h"
#include <string.h>
/* -------- */

/* Global Variables */
#define MAXCOMMBUFFER 2048
#define MAX_STRLEN 2048
/* ---------------- */

typedef struct _commBuffer_t {
	uint32_t head;
	uint32_t tail;
	char buffer[MAXCOMMBUFFER + 1];
} commBuffer_t;


//Initializes the struct commBuffer_t to zero
void InitBuffer(commBuffer_t* comm);
//Test if a complete string is in buffer delimiter is \n
uint8_t haveStr(commBuffer_t* comm);
//Put character in buffer and update head
void putChar(commBuffer_t* comm, char ch);
//Get character from buffer and update tail;
char getChar(commBuffer_t* comm);
//put C string into buffer
void putStr(commBuffer_t* comm, char* str, uint8_t length);
//get C string from buffer
void getStr(commBuffer_t* comm, char* str);
// Check if buffer has exceeded max size
void checkBufferOverflowStatus(commBuffer_t* comm);
// Get buffer's current size
uint32_t bufferSize(commBuffer_t* comm);

#endif

