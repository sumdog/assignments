/*
 * VOS - Virtual OS / Sumllen's cpsc-251
 *  Sumit Khanna
 *
 * Main driver / entry point. Creates the Scheduler,
 * starts three processes and starts the OS. In future
 * versions of this, the first process will actually
 * bootstrap the other processes by using the InitProcess
 * class. 
 */
#include "process.hpp"
#include "scheduler.hpp"
#include "vos.hpp"

int main(int argc, char **argv) {
	
	Scheduler *s = new RealTimeScheduler();
	Process *p1 = new Process("processes/1.proc");
	Process *p2 = new Process("processes/2.proc");
	Process *p3 = new Process("processes/3.proc");
	s->addProcess(p1);
	s->addProcess(p2);
	s->addProcess(p3);
	
	VOS *v = new VOS(p1,s);
}
