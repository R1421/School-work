/*
 * File: pager-lru.c
 * Author:       Andy Sayler
 *               http://www.andysayler.com
 * Adopted From: Dr. Alva Couch
 *               http://www.cs.tufts.edu/~couch/
 *
 * Project: CSCI 3753 Programming Assignment 4
 * Create Date: Unknown
 * Modify Date: 2012/04/03
 * Description:
 * 	This file contains an lru pageit
 *      implmentation.
 */

#include <stdio.h> 
#include <stdlib.h>

#include "simulator.h"

void pageit(Pentry q[MAXPROCESSES]) { 
    
    /* This file contains the stub for an LRU pager */
    /* You may need to add/remove/modify any part of this file */

    /* Static vars */
    static int initialized = 0;
    static int tick = 1; // artificial time
    static int timestamps[MAXPROCESSES][MAXPROCPAGES];

    /* Local vars */
    int proctmp;
    int pagetmp;
    int pageinret;
    int pageoutret;
    int proc;
    int page;
    int evictProc;
    int evictPage;
    int minTimeStamp;

    /* initialize static vars on first run */
    if(!initialized){
	for(proctmp=0; proctmp < MAXPROCESSES; proctmp++){
	    for(pagetmp=0; pagetmp < MAXPROCPAGES; pagetmp++){
		timestamps[proctmp][pagetmp] = 0; 
	    }
	}
	initialized = 1;
    }


    //First select a process. We should select by using active processes
    for(proctmp = 0; proctmp < MAXPROCESSES; proctmp++){
        if(q[proctmp].active == 1){
//            fprintf(stdout, "Process %d is active\n", proctmp);

            //Since the process is active, determine which page it is currently using
            pagetmp = q[proctmp].pc/PAGESIZE;

            //Is the page currently in physical memory?
            if(q[proctmp].pages[pagetmp] == 1){
//                fprintf(stdout, "Page %d of process %d is currently in physical memmory\n", pagetmp, proctmp);
            }
            else{
//                fprintf(stdout, "Page %d of process %d is not currently in physical memmory. Attempting to page it in\n", pagetmp, proctmp);
                pageinret = pagein(proctmp, pagetmp);

                if(pageinret == 1){
                  //Pagein shouldve been successful?
//                    fprintf(stdout, "Pagein successful\n");
                    timestamps[proctmp][pagetmp] = tick;
//                    fprintf(stdout, "Proc: %d, Page: %d timestamp updated to %d\n", proctmp, pagetmp, tick);
                }
                else{
//                    fprintf(stdout, "Pagein unsuccessful :( Lets evict a process\n");
                    
                    //Deterimine the LRU page and evict it
                    minTimeStamp = ~0U >> 1;
                    proc = proctmp;
                    for(page = 0; page < MAXPROCPAGES; page++){
                        //Check only the pages in that locality
                        if(q[proc].pages[page] == 1){
                            if(q[proc].active == 0){
                                //Found an inactive process's page. Page it out!!!
                                evictProc = proc;
                                evictPage = page;
                                break;
                            }
                            if(timestamps[proc][page] < minTimeStamp){
                                minTimeStamp = timestamps[proc][page];
                                evictProc = proc;
                                evictPage = page;
                            }
                        }
                    }
                    
                    pageoutret = pageout(evictProc, evictPage);
                    if(pageoutret == 1){
//                        fprintf(stdout, "Proc: %d Page: %d paged out successfully. Time = %d\n", evictProc, evictPage, tick);
                        pageinret = pagein(proctmp, pagetmp);
                        if(pageinret == 1){
//                            fprintf(stdout, "Success");
                        }
                    }

                }
            }
        }
    }
    
    /* TODO: Implement LRU Paging *//*
    fprintf(stderr, "pager-lru not yet implemented. Exiting...\n");
    exit(EXIT_FAILURE);*/

    /* advance time for next pageit iteration */
    tick++;
} 
