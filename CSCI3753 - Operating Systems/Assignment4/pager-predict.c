/*
 * File: pager-predict.c
 * Author:       Andy Sayler
 *               http://www.andysayler.com
 * Adopted From: Dr. Alva Couch
 *               http://www.cs.tufts.edu/~couch/
 *
 * Project: CSCI 3753 Programming Assignment 4
 * Create Date: Unknown
 * Modify Date: 2012/04/03
 * Description:
 * 	This file contains a predictive pageit
 *      implmentation.
 */

#include <stdio.h> 
#include <stdlib.h>

#include "simulator.h"

int predict(int nextPage[MAXPROCESSES][MAXPROCPAGES][MAXPROCPAGES], int swapCounter[MAXPROCESSES][MAXPROCPAGES], int proctmp, int pagetmp)
{
    int next;
    int spinner;
    int stop;
    int success = 0;

    if(swapCounter[proctmp][pagetmp] != 0){
        spinner = rand() % swapCounter[proctmp][pagetmp];
        stop = 0;
        for(next = 0; next < MAXPROCPAGES; next++){
            if(nextPage[proctmp][pagetmp][next] != 0){
                stop += nextPage[proctmp][pagetmp][next];
                if(spinner < stop){
                    if(pagein(proctmp, next) == 1){
                        success++;
                        break;
                    }
                }
            }
        }
    }
    return success;
}

int LRUout(Pentry q[MAXPROCESSES], int timestamps[MAXPROCESSES][MAXPROCPAGES], int proctmp)
{
    int proc; 
    int page; 
    int evictPage; 
    int evictProc;
    int minTimeStamp;
    
    minTimeStamp = ~0U >> 1;
    proc = proctmp;
    for(page = 0; page < MAXPROCPAGES; page++){
        if(q[proc].pages[page] == 1){
            if(timestamps[proc][page] < minTimeStamp){
                minTimeStamp = timestamps[proc][page];
                evictProc = proc;
                evictPage = page;
            }
        }
    }
    if(pageout(evictProc, evictPage) == 1){
        return 1;
    }
    return 0;
}


void pageit(Pentry q[MAXPROCESSES]) { 
    
    /* This file contains the stub for a predictive pager */
    /* You may need to add/remove/modify any part of this file */

    /* Static vars */
    static int initialized = 0;
    static int tick = 1; // artificial time
    static int timestamps[MAXPROCESSES][MAXPROCPAGES];
    static int prevPage[MAXPROCESSES];
    static int nextPage[MAXPROCESSES][MAXPROCPAGES][MAXPROCPAGES];
    static int swapCounter[MAXPROCESSES][MAXPROCPAGES];
    
    /* Local vars */
    int proctmp;
    int pagetmp;
    int pageinret;
    int pageoutret;
    int next;
   

    /* initialize static vars on first run */
    if(!initialized){
	/* Init complex static vars here */
        for(proctmp=0; proctmp < MAXPROCESSES; proctmp++){
            prevPage[proctmp]= -1;
            for(pagetmp=0; pagetmp < MAXPROCPAGES; pagetmp++){
                swapCounter[proctmp][pagetmp] = 0;
                timestamps[proctmp][pagetmp] = 0;
                for(next = 0; next < MAXPROCPAGES; next++){
                    nextPage[proctmp][pagetmp][next] = 0;   
                }
            }
        }
	initialized = 1;
    }

    for(proctmp = 0; proctmp < MAXPROCESSES; proctmp++){
        if(q[proctmp].active == 1){
            pagetmp = q[proctmp].pc/PAGESIZE;

            if(q[proctmp].pages[pagetmp] == 1){
                timestamps[proctmp][pagetmp] = tick;
                if(tick >= 20000){
                    pageinret = predict(nextPage, swapCounter, proctmp, pagetmp);
                }
                else{
                    pagein(proctmp, pagetmp+1);
                }
            }
            else{
                pageinret = pagein(proctmp, pagetmp);

                if(pageinret == 1){
//                    timestamps[proctmp][pagetmp] = tick;
                    pageinret = predict(nextPage, swapCounter, proctmp, pagetmp);
                }
                else{
                    pageoutret = LRUout(q,timestamps, proctmp);
                    if(pageoutret == 1){
                    }
                }
            }
            if(pagetmp != prevPage[proctmp]){
                swapCounter[proctmp][prevPage[proctmp]]++;
                nextPage[proctmp][prevPage[proctmp]][pagetmp]++;
                prevPage[proctmp] = pagetmp;
            }
            pageinret = predict(nextPage, swapCounter, proctmp, pagetmp);
        }
        else{
            for(pagetmp = 0; pagetmp < MAXPROCPAGES; pagetmp++){
                if(q[proctmp].pages[pagetmp] == 1){
                    pageout(proctmp, pagetmp);
                }
            }
        }
    }

    // Used to check nextPage and swapCounter values
/*    if(tick == 10000){
        for(proctmp = 0; proctmp < MAXPROCESSES; proctmp++){
            fprintf(stdout, "Process %d\n", proctmp);
            for(pagetmp = 0; pagetmp < MAXPROCPAGES; pagetmp++){
                fprintf(stdout, "    Page %d:\t[", pagetmp);
                for(next = 0; next < MAXPROCPAGES; next++){
                    if(next != 0){
                        fprintf(stdout, ",");
                    }
                    fprintf(stdout, "\t%d", nextPage[proctmp][pagetmp][next]);
                }
                fprintf(stdout, "\t]  swapCount = %d\n", swapCounter[proctmp][pagetmp]);
            }
        }
    }
    if(tick >= 20000){
        for(proctmp = 0; proctmp < MAXPROCESSES; proctmp++){
            pagetmp = q[proctmp].pc/PAGESIZE;
            if(swapCounter[proctmp][pagetmp] != 0){
                spinner = rand() % swapCounter[proctmp][pagetmp];
                stop = 0;
                for(next = 0; next < MAXPROCPAGES; next++){
                    stop += nextPage[proctmp][pagetmp][next];
                    if(spinner < stop){
                        if(pagein(proctmp, next) == 0){
                            timestamps[proctmp][next] = tick;
                        }
                        break;
                    }
                }
            }
        }
    }
*/
    /* advance time for next pageit iteration */
    tick++;
} 
