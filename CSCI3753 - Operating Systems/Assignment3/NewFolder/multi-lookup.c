//Multi lookup file: uses multiple threads of execution to read domain names from files and prints the 

#include <stdlib.h>
#include "multi-lookup.h"

//Global Variables
//FILE *fileQueue[MAX_INPUT_FILES];
queue fileQueue;
queue resolvedDomainsQueue;
char *outputFileName;
FILE *outputFile;
int active;
pthread_mutex_t files;			//Lock for fileQueue
pthread_mutex_t resolvedQueue;		//Lock for resolvedQueue
pthread_mutex_t output;			//Lock for outputFile


//Function definitions
void* requestFile(void *threadid)
{
	long *tid = threadid;
	char *filename;
	int rc;
	while(1 == 1){

		printf("|\tRequester thread %ld requesting file to process\n", *tid);

		//Acquire lock
		while((rc = pthread_mutex_trylock(&files)) != 0){
			printf("|\tRequester thread %ld couldn't acquire fileQueue lock. pthread_mutex_trylock returned: %d\n", *tid, rc);
			usleep(rand()%100);
		}
		
		//Critical Section
		if((filename = (char *)queue_pop(&fileQueue)) == NULL){
			//Queue is empty. No more files to process
			pthread_mutex_unlock(&files);
			printf("Requester thread %ld ending execution\n", *tid);
			break;
		}
		printf("|\tRequester thread %ld acquired file %s\n", *tid, filename);
		
		//Release lock
		pthread_mutex_unlock(&files);

		processFile(tid,filename);
	}

	return NULL;
}

void processFile(void *threadid, char *filename)
{  
	long *tid = threadid;
	FILE *file;
	file = fopen(filename,"r");
	printf("|\t|\tRequester thread %ld opened file %s\n", *tid, filename);
	char domain[MAX_NAME_LENGTH];
	char domainIP[MAX_IP_LENGTH];
	char domainPlusIP[MAX_NAME_LENGTH + MAX_IP_LENGTH];
	int rc;

	//Read domains from file;
	while(fgets(domain, MAX_NAME_LENGTH, file) != NULL){
		domain[strlen(domain)-1] = '\0';
		*domainIP = '\0';
//		printf("|\t|\tFrom thread %ld: %s\n", *tid, domain);
		if(dnslookup((char *)domain, (char *)domainIP, MAX_IP_LENGTH) == UTIL_FAILURE){
			printf("|\t|\tRequester thread %ld encountered an error for domain %s, %s\n", *tid, domain, domainIP);
		}
		printf("|\t|\tRequester thread %ld found %s at IP %s\n", *tid, domain, domainIP);
		
		//Build message to push onto stack
		strcpy(domainPlusIP, domain);
		strcat(domainPlusIP, ",");
		strcat(domainPlusIP, domainIP);
		printf("|\t|\tString to be pushed to resolvedStack: %s\n", domainPlusIP);
		
		while(1 == 1){
			//Wait to push to queue

			//Acquire lock
			while((rc = pthread_mutex_trylock(&resolvedQueue)) != 0){
				printf("|\tRequester thread %ld couldn't acquire resolvedDomainsQueue lock. pthread_mutex_trylock returned: %d\n", *tid, rc);
				usleep(rand()%100);
			}
			
			//Critical Section
			rc = queue_push(&resolvedDomainsQueue, domainPlusIP);
			pthread_mutex_unlock(&resolvedQueue);
			if(rc == -1){
				//Queue is full. Wait, and try again
				printf("|\t|\t|    resolvedQueue is full. Requester thread %ld waiting...\n", *tid);
				usleep(rand()%100);
			}
			else{
				//Pushed successfully
				break;
			}
		}
		printf("|\t|\t|    Requester thread %ld pushed %s to resolvedQueue\n", *tid, domainPlusIP);
	}

	fclose(file);
}

void* requestResolvedString(void *threadid)
{
	long *tid = threadid;
	char *resolvedString;
	int rc;

	while(1 == 1){

//              printf("|\tResolver thread %ld pulling resolved string from resolvedQueue\n", *tid);

                //Acquire resolvedQueue lock
                while((rc = pthread_mutex_trylock(&resolvedQueue)) != 0){
                        printf("|\tResolver thread %ld couldn't acquire resolvedQueue lock. pthread_mutex_trylock returned: %d\n", *tid, rc);
                        usleep(rand()%100);
                }
                //Critical Section
		if(!queue_is_empty(&resolvedDomainsQueue)){
			resolvedString = (char *)queue_pop(&resolvedDomainsQueue);
		}
		pthread_mutex_unlock(&resolvedQueue);
                if(resolvedString == NULL){
			//Queue is empty
			if(active == 0){
				//Requester threads are finished, end the program
				printf("Resolver thread %ld ending execution\n", *tid);
				break;
			}
                }
                else{
			printf("|\tResolver thread %ld acquired  %s from resolvedQueue\n", *tid, resolvedString);
			writeToFile(tid,resolvedString);
			resolvedString = NULL;
		}
		usleep(rand()%100);

        }

	return NULL;
}

void writeToFile(void *threadid, char *str)
{
	long *tid = threadid;
        char *resolvedString = str;
        int rc;

	//Acquire outputFile lock
	while((rc = pthread_mutex_trylock(&output)) != 0){
		printf("|\tResolver thread %ld couldn't acquire resolvedQueue lock. pthread_mutex_trylock returned: %d\n", *tid, rc);
		usleep(rand()%100);
	}
	
	//Critical Section
	fputs(resolvedString, outputFile);
	fputs("\n", outputFile);

	//Release outputFile lock
	pthread_mutex_unlock(&output);
	
	printf("|\t    Resolver thread %ld wrote %s to %s\n", *tid, resolvedString, outputFileName);
	
}

int main(int argc, char *argv[])
{
        /*(void) argc;
        (void) argv;*/
        if(argc - 1 < MIN_ARGS){
                printf("%s", USAGE);
                return -1;
        }
        else if(argc - 1 > MAX_INPUT_FILES){
                printf("%s", USAGE);
		return -1;
        }
	
	//Local Variables
        pthread_t requesterThreads[MAX_REQUESTER_THREADS];
        pthread_t resolverThreads[MIN_RESOLVER_THREADS];
        long requesterTID[MAX_REQUESTER_THREADS];
        long resolverTID[MIN_RESOLVER_THREADS];
        int rc;
	int i;
	
	//Initialize queues
	if(queue_init(&fileQueue, (int)argc-1) == -1){
		printf("Error initializing fileQueue\n");
		return -2;
	}
	if(queue_init(&resolvedDomainsQueue, RESOLVED_DOMAINS_QUEUE_LENGTH) == -1){
                printf("Error initializing resolvedDomainsQueue\n");
                return -2;
        }
	
	outputFileName = (char *)argv[argc-1];
	outputFile = fopen(outputFileName, "w");
	for(i = 1; i < argc-1; i++){
		if(queue_push(&fileQueue, (void *)argv[i]) == -1){
			printf("Error pushing to fileQueue\n");
			return -3;
		}
	}

	//Initilize mutex locks
	pthread_mutex_init(&files,NULL);
	pthread_mutex_init(&resolvedQueue,NULL);
	pthread_mutex_init(&output,NULL);


	//Create requester threads
	for(i = 0; i < MAX_REQUESTER_THREADS; i++){
		printf("In main creating requesterThread %d\n", i + 1);
		requesterTID[i] = i + 1;
		rc = pthread_create(&(requesterThreads[i]), NULL, requestFile, &(requesterTID[i]));
		if(rc){
			printf("Error: pthread_create() returned: %d\n", rc);
		}
	}
	active = 1;

	//Create resolver threads
	for(i = 0; i < MIN_RESOLVER_THREADS; i++){
                printf("In main creating resolverThread %d\n", i + 1);
                resolverTID[i] = i + 1;
                rc = pthread_create(&(resolverThreads[i]), NULL, requestResolvedString, &(resolverTID[i]));
                if(rc){
                        printf("Error: pthread_create() returned: %d\n", rc);
                }
        }

	//Wait for requester threads to finish
	for(i = 0 ; i < MAX_REQUESTER_THREADS; i++){
		printf("Deleting requster thread %d\n", i + 1);
		pthread_join(requesterThreads[i],NULL);
	}
	active = 0;

	//Wait for resolver threads to finish
	for(i = 0 ; i < MIN_RESOLVER_THREADS; i++){
		printf("Deleting resolver thread %d\n", i + 1);
		while(pthread_join(resolverThreads[i],NULL) != 0){
			usleep(rand()%100);
		}
        }

	//Close outputFile
	fclose(outputFile);

	//Deallocate queue memory
	queue_cleanup(&fileQueue);
	queue_cleanup(&resolvedDomainsQueue);
	
	//Destroying mutex locks
	pthread_mutex_destroy(&files);
        pthread_mutex_destroy(&resolvedQueue);
        pthread_mutex_destroy(&output);

	printf("All of the threads were completed!\n");
	
	return 0;
}
