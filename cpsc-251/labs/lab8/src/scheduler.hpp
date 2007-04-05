/*
 * VOS - Virtual OS / Sumllen's cpsc-251
 *  Sumit Khanna
 */
#ifndef SCHEDULER_HPP
#define SCHEDULER_HPP
#include "process.hpp"

#define LIST_SIZE 10

/* 
 * Abstract class which holds a process list
 * and can be used to derive different schedulers 
 * with the scheduling algrothim stored in the
 * virtual function startScheduler().
 */
class Scheduler {
	public:
	 Scheduler();
	 ~Scheduler();
	 void addProcess(Process *p);
     virtual void startScheduler() = 0; 
	private:
	 void resizeList(int n);
	protected:
     Process **procs; 
     int tasksize;
     int numtasks;

};

/*
 * The Real Time Scheduler will run one process
 * at a time, allowing each process to complete
 * before loading a new process.
 */
class RealTimeScheduler : public Scheduler {
	public:
	 virtual void startScheduler();
};

/*
 * The Round Robin Scheduler will allot each process
 * the same amount of time to run until all are complete
 */
class RoundRobinScheduler : public Scheduler {
	public:
	 virtual void startScheduler();
};


#endif