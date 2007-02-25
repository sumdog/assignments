/*
 * VOS - Virtual OS / Sumllen's cpsc-251
 *  Implementation of base class for abstract Scheduler
 *  as well as the RealTime Scheduler. 
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

