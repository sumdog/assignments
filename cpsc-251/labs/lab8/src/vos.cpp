/*
 * VOS - Virtual OS / Sumllen's cpsc-251
 *  Sumit Khanna
 * 
 * This is the main driver. Starts scheduler 
 * and the init process which bootstraps the rest
 */
#include "vos.hpp"


VOS::VOS(Process *i, Scheduler *s) {
	sch = s;
	init = i;
	//s->addProcess(i); 
	s->startScheduler();
}

VOS::~VOS() {
	
}