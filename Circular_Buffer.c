#include <stm32f4xx.h>
#include "circularBuffer.h"

void InitBuffer(commBuffer_t* comm)
{
	comm->tail = 0;
	comm->head = 0;
}

uint32_t bufferSize(commBuffer_t* comm)
{
	return (comm->head - comm->tail + (MAXCOMMBUFFER)) % (MAXCOMMBUFFER);
}

void checkBufferOverflowStatus(commBuffer_t* comm)
{
	if (comm->head > MAXCOMMBUFFER)
	{
		comm->head = 0;
	}
	if (comm->tail > MAXCOMMBUFFER)
	{
		comm->tail = 0;
	}
}

uint8_t haveStr(commBuffer_t* comm)
{
	uint32_t buffer_status = 0;
	uint32_t buffer_length = bufferSize(comm);

	for (uint32_t i = comm->tail; i < buffer_length; i++)
	{
		if (comm->buffer[i] == '\n')
		{
			buffer_status = 1;
		}
		else
		{
			buffer_status = 0;
		}
	}
	return buffer_status;
}

void putChar(commBuffer_t* comm, char ch)
{
	checkBufferOverflowStatus(comm);
	comm->head = (comm->head) + 1;
	comm->buffer[comm->head - 1] = ch;
}

char getChar(commBuffer_t* comm)
{
	checkBufferOverflowStatus(comm);
	comm->tail = (comm->tail) + 1;
	
	return comm->buffer[comm->tail];
}

void putStr(commBuffer_t* comm, char* str, uint8_t length)
{
	for (uint32_t i = 0; i <= length; i++)
	{
		putChar(comm, str[i]);
	}
}

void getStr(commBuffer_t* comm, char* str)
{
	uint32_t buffer_length = bufferSize(comm);
	memcpy(str, &(comm->buffer[comm->tail]), buffer_length - 1);
	comm->tail = comm->head;
}
