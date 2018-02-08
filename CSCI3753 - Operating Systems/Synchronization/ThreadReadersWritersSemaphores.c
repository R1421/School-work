// This is the starvation-free solution to 2nd R/W on slide 26 of the synchronization
// 	problems powerpoint
// Semaphore tutorial: http://www.amparo.net/ce155/sem-ex.html

/*
 *
 * Includes
 *
 */
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>
#include <sys/stat.h>
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
char _szFileBuffer[LEN_FILE + 1];
int _nBufferPointer;
sem_t _semWrite;
sem_t _semRead;
sem_t _semMutex;
int _nReadCount;



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

	// init threading variables
	sem_init(&_semWrite, 0, 1);
	sem_init(&_semRead, 0, 1);
	sem_init(&_semMutex, 0, 1);
	_nReadCount = 0;

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

	// destroy semaphores
	sem_destroy(&_semWrite);
	sem_destroy(&_semRead);
	sem_destroy(&_semMutex);

	return 0;
}



/*
 *
 * Threading function implementations
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

		// mutex around write
		sem_wait(&_semRead);
		sem_wait(&_semWrite);

		// write!
		WriteFile((const char *)&szData, pszNumber);

		// end mutex
		sem_post(&_semWrite);
		sem_post(&_semRead);

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

		// mutex around read
		sem_wait(&_semRead);
		sem_wait(&_semMutex);
		_nReadCount++;
		if (_nReadCount == 1)
		{
			sem_wait(&_semWrite);
		}
		sem_post(&_semMutex);
		sem_post(&_semRead);

		// clear buffer and read!
		memset(&szData, '\0', LEN_FILE + 1);
		ReadFile((char *)&szData, pszNumber);

		// end mutex
		sem_wait(&_semMutex);
		_nReadCount--;
		if (_nReadCount == 0)
		{
			sem_post(&_semWrite);
		}
		sem_post(&_semMutex);

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
}

void ReadFile(char * pszBuffer, char * pszNumber)
{

	// var init
	int i;
	int nLenBuffer = strlen(_szFileBuffer);

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
}