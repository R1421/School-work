#ifndef MULTI_LOOKUP_H
#define MULTI_LOOKUP_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <pthread.h>
#include <unistd.h>

#include "util.h"
#include "queue.h"

/* Global Variables */
#define MIN_ARGS 2
#define MAX_INPUT_FILES 10
#define MAX_REQUESTER_THREADS 10
#define MAX_RESOLVER_THREADS 10
#define MIN_RESOLVER_THREADS 2
#define MAX_NAME_LENGTH 1025
#define RESOLVED_DOMAINS_QUEUE_LENGTH 10
#define MAX_IP_LENGTH INET6_ADDRSTRLEN
#define USAGE "Usage: multi-lookup <infile1> <infile2> ... <infileN> <output file>  Max input files: 10"


/* The following are function prototypes for the multi-lookup.c file */
void* requestFile(void *threadid);
void processFile(void *threadid, char *filename);
void* requestResolvedString(void *threadid);
void writeToFile(void *threadid, char *str);



#endif
