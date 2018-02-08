// This is the a very simple synchronized R/W implementation

/*
 *
 * Includes
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>



/*
 *
 * Definitions
 *
 */
#define LEN_FILE 100
#define TRUE 1
#define FALSE 0



/*
 *
 * Global variables
 *
 */
static char _szFileBuffer[LEN_FILE + 1];
static int _nBufferPointer;
pthread_mutex_t _muxLock;



/*
 *
 * Prototypes
 *
 */
void* WriterFunction(void* pvData);
void* ReaderFunction(void* pvData);
void WriteFile(const char * psz, char * pszNumber);
void ReadFile(char * pszBuffer, char * pszNumber);



/*
 *
 * Main function implementation
 *
 */
int main (int argc, char *argv[])
{

	// var init
	pthread_t tWriter1, tWriter2, tWriter3, tReader1, tReader2, tReader3;
	char szFirst[10] = "[1st]";
	char szSecond[10] = "[2nd]";
	char szThird[10] = "[3rd]";
	char cInput;

	// init basic global variables
	memset(&_szFileBuffer, '\0', LEN_FILE + 1);
	_nBufferPointer = 0;

	// init mutex
	pthread_mutex_init(&_muxLock, NULL);

	// create threads
	pthread_create(&tWriter1, NULL, WriterFunction, (void*)&szFirst);
	pthread_create(&tWriter2, NULL, WriterFunction, (void*)&szSecond);
	pthread_create(&tWriter3, NULL, WriterFunction, (void*)&szThird);
	pthread_create(&tReader1, NULL, ReaderFunction, (void*)&szFirst);
	pthread_create(&tReader2, NULL, ReaderFunction, (void*)&szSecond);
	pthread_create(&tReader3, NULL, ReaderFunction, (void*)&szThird);

	// wait for input
	printf("\r\nPress any key to exit...");
	cInput = getchar();

	// destroy mutex
	pthread_mutex_destroy(&_muxLock);

	return 0;
}



/*
 *
 * Threading function definitions
 *
 */
void* WriterFunction(void* pvData)
{

	// var init
	char* pszNumber = (char *)pvData;
	char szData[50] = "|abcdefghijklmnopqrstuvwxyz-";

	// build write string
	strcat((char *)&szData, pszNumber);

	// write repeatedly
	while(TRUE)
	{

		// write!
		WriteFile((const char *)&szData, pszNumber);

		// sleep this thread a tick
		usleep(0);
	}

	return NULL;
}

void* ReaderFunction(void* pvData)
{

	// var init
	char* pszNumber = (char *)pvData;
	char szData[LEN_FILE + 1];

	// read repeatedly
	while(TRUE)
	{

		// clear buffer and read!
		memset(&szData, '\0', LEN_FILE + 1);
		ReadFile((char *)&szData, pszNumber);

		// sleep this thread a tick
		usleep(0);
	}

	return NULL;
}



/*
 *
 * Supporting function implementations
 *
 */
void WriteFile(const char * pszBuffer, char * pszNumber)
{

	// var init
	int i;
	int nLenPsz = strlen(pszBuffer);

	// lock the write
	pthread_mutex_lock(&_muxLock);

	// append to buffer and print
	printf("\r\n\r\n-------------------------------\r\nSTART WRITING: %s\r\n-------------------------------\r\n", pszNumber);
	printf("\r\n\r\n%s File buffer before write:\r\n%s\r\n\r\nWriting:\r\n", pszNumber, _szFileBuffer);
	for (i = 0; i < nLenPsz; i++)
	{

		// print a character and sleep a tick
		printf("%c", pszBuffer[i]);
		usleep(0);

		// append to buffer
		_nBufferPointer = (_nBufferPointer >= LEN_FILE) ? 0 : _nBufferPointer;
		_szFileBuffer[_nBufferPointer] = pszBuffer[i];
		if ((_nBufferPointer + 1) < LEN_FILE)
		{
			_szFileBuffer[_nBufferPointer + 1] = '@';
		}
		else
		{
			_szFileBuffer[0] = '@';
		}
		_nBufferPointer++;
	}
	printf("\r\n\r\n%s File buffer after write:\r\n%s", pszNumber, _szFileBuffer);
	printf("\r\n\r\n-------------------------------\r\nSTOP WRITING: %s\r\n-------------------------------\r\n", pszNumber);

	// unlock the write
	pthread_mutex_unlock(&_muxLock);
}

void ReadFile(char * pszBuffer, char * pszNumber)
{

	// var init
	int i;
	int nLenBuffer = strlen(_szFileBuffer);

	// lock the read
	pthread_mutex_lock(&_muxLock);

	// read data back into buffer
	printf("\r\n\r\n-------------------------------\r\nSTART READING: %s\r\n-------------------------------\r\n", pszNumber);
	for (i = 0; i < nLenBuffer; i++)
	{

		// sleep a tick
		usleep(0);

		// write to read budder
		pszBuffer[i] = _szFileBuffer[i];
	}
	printf("\r\n\r\n%s File buffer read:\r\n%s", pszNumber, _szFileBuffer);
	printf("\r\n\r\n%s Returned buffer after read:\r\n%s", pszNumber, pszBuffer);
	printf("\r\n\r\n-------------------------------\r\nSTOP READING: %s\r\n-------------------------------\r\n", pszNumber);

	// unlock the read
	pthread_mutex_unlock(&_muxLock);
}