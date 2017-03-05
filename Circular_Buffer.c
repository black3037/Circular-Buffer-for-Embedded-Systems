#include <stdio.h>
#include <string.h>

#define MAXCOMMBUFFER 2048

typedef struct commBuffer_t {
	int tail;
	int head;
	char buffer[MAXCOMMBUFFER + 1];
}commBuffer_t;

void writingLED(void)
{
	// Enter code for your hardware here.
}

void readingLED(void)
{
	// Enter code for your hardware here.
}

void InitBuffer(commBuffer_t* comm)
{
	comm->tail = 0;
	comm->head = 0;
}

int bufferSize(commBuffer_t* comm)
{
	return (comm->head - comm->tail + (MAXCOMMBUFFER)) % (MAXCOMMBUFFER);
}

void checkBufferOverflowStatus(commBuffer_t* comm)
{
	/* Check Head Position & Reset */
	if (comm->head > MAXCOMMBUFFER)
	{
		comm->head = 0;
	}

	/* Check Tail Position & Reset */
	if (comm->tail > MAXCOMMBUFFER)
	{
		comm->tail = 0;
	}
}

int haveStr(commBuffer_t* comm)
{
	int buffer_status;
	int buffer_length = bufferSize(comm);

	int i;
	for (i = comm->tail; i <= buffer_length; i++)
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
	comm->buffer[comm->head] = ch;
}

char getChar(commBuffer_t* comm)
{
	checkBufferOverflowStatus(comm);
	comm->tail = (comm->tail) + 1;

	return comm->buffer[comm->tail];
}

void putStr(commBuffer_t* comm, char* str, int length)
{
	int i;
	for (i = 0; i <= length; i++)
	{
		putChar(comm, str[i]);
	}
}

void getStr(commBuffer_t* comm, char* str)
{
	int buffer_length = bufferSize(comm);

	int i;
	for (i = 0; i <= buffer_length - 1; i++)
	{
		str[i] = getChar(comm);
	}
}

int main(void)
{
	commBuffer_t comm;
	InitBuffer(&comm);
	printf("tail position = %i head position = %i (Initalized) \n", comm.tail, comm.head);

	char* startText = "{\"Action\":\"Debug\",\"Info\":\"Testing UART6\"}";
	putStr(&comm, startText, strlen(startText));
	printf("tail position = %i head position = %i (Put String) \n", comm.tail, comm.head);

	char* output_string;
	getStr(&comm, output_string);
	printf("tail position = %i head position = %i (Get String) \n", comm.tail, comm.head);
	printf("%s \n", output_string);

}
