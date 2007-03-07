/*
 * VOS - Virtual OS / Sumllen's cpsc-251
 *  Implementation of base class for abstract Scheduler
 *  as well as the RealTime Scheduler and RoundRobin Scheduler. 
 *  Sumit Khanna
 */
#include "scheduler.hpp"

Scheduler::Scheduler() {
	tasksize = LIST_SIZE;
	numtasks = 0;
	procs = new Process*[LIST_SIZE];
}
Scheduler::~Scheduler() {
	for(int i=0; i < numtasks; i++) {
		delete procs[i];
	}
	delete[] procs;
	
}

void Scheduler::addProcess(Process *p) {
	if(numtasks == tasksize - 1) {
		resizeList(tasksize+LIST_SIZE);
	}
	procs[numtasks++] = p;
}
void Scheduler::resizeList(int j) {
	Process **n = new Process*[j];
	for(int i=0; i < tasksize; i++) {
		n[i] = procs[i];
	}
	delete[] procs;
	procs = n;
}

void RealTimeScheduler::startScheduler() {
	while(true) {
		for(int i=0; i < tasksize; i++) {
			if(procs[i] != NULL) {
				procs[i]->startProcess();
				while(!procs[i]->isFinished()) {
					/* wait until finished */
				}
			}
		}
	}
}

void RoundRobinScheduler::startScheduler() {
	while(true) {
		for(int i=0; i < tasksize; i++) {
			if(procs[i] != NULL) {
				procs[i]->startProcess();
				
				/* let all processes run for same time */
				struct timespec interval,remainder;
				interval.tv_sec = 0;
				interval.tv_nsec = 100;
				nanosleep(&interval, &remainder);
				
				/* stop process and remove if finished */
				procs[i]->interruptProcess();
				if(procs[i]->isFinished()) {
					delete procs[i];
					procs[i] = NULL;
				}
				
			}
		}
	}	
}