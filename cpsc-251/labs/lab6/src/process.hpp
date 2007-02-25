/*
 * VOS - Virtual OS / Sumllen's cpsc-251
 *  Sumit Khanna
 */
#ifndef PROCESS_HPP
#define PROCESS_HPP
#include <string>
using std::string; 

class Process {
	public:
		Process(string file);
		~Process();
		bool startProcess();
		bool isRunning();
		bool isWaiting();
		bool isFinished();
		bool interruptProcess();
		//enum state = {  };
	private:
		static void* pThread(void* x);
		bool running;

	protected:
		virtual void pThreadAction(void *x);
		string *arch;
		int stack;
		int heap;
		string *registers;
		int operations; 
		bool interrupt; 
		string *name;
		bool finished;
};

class InitProcess : public Process{
	public:
		InitProcess();
	private:
	protected:
		virtual void pThreadAction(void *x);
};

#endif