/*
 * VOS - Virtual OS / Sumllen's cpsc-251
 *  Sumit Khanna
 */

#ifndef VOS_H
#define VOS_H
#include "scheduler.hpp"
#include "process.hpp"

class VOS {
	public:
		VOS(Process *i, Scheduler *s);
		~VOS();
	private:
		Process *init;
		Scheduler *sch;
};

#endif /* VOS_H */