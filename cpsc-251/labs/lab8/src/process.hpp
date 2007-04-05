/*
 * VOS - Virtual OS / Sumllen's cpsc-251
 *  Sumit Khanna
 */
#ifndef PROCESS_HPP
#define PROCESS_HPP
#include <string>
#include <queue>

using std::string; 

enum InsOpCode { NOOP, ALLOC, FREE, IOREAD, IOWRITE };

class Instruction {
  public:
    Instruction();
    Instruction(InsOpCode o, string ins);
    Instruction(string s);
    ~Instruction();
    InsOpCode getOp();
    string getArgs();
  private:
    InsOpCode opcode;
    string instruction;
};

class Process {
	public:
		Process(string file);
		~Process();
		bool startProcess();
		bool isRunning();
		bool isWaiting();
		bool isFinished();
		bool interruptProcess();
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
		std::queue<Instruction> instructions;
};

class InitProcess : public Process {
	public:
		InitProcess();
	protected:
		virtual void pThreadAction(void *x);
};

#endif