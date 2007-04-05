/*
 * VOS - Virtual OS / Sumllen's cpsc-251
 *  Sumit Khanna
 */ 
#include <iostream>
#include <fstream>
#include <pthread.h>
#include <string>
#include <cstring>
#include <time.h>
using std::ifstream;
using std::cout;
using std::endl;
#include "process.hpp"

Instruction::Instruction() {
  opcode = NOOP;
  instruction = "";
}

Instruction::Instruction(InsOpCode o, string ins) {
  opcode = o;
  instruction = ins;
}

Instruction::~Instruction() {
  
}

Instruction::Instruction(string s) {
  char *x = new char[strlen(s.c_str())+1];
  char *sep = " ";
  strcpy(x,s.c_str());
  char *word;
  int pos = 0;
  for(word = strtok(x,sep);word;word=strtok(NULL,sep)) {
    switch(pos) {
      //op code
      case 0:
        if(strcmp(word,"alloc") == 0) {
          opcode = ALLOC;
        }
        else if(strcmp(word,"free") == 0) {
          opcode = FREE;
        }
      break;
      //operands 
      case 1:
        instruction = word;
      break;
    }
  }
  delete x;
}

InsOpCode Instruction::getOp() {
  return opcode;
}

string Instruction::getArgs() {
  return instruction;
}

Process::Process(string s) {
	name = new string(s);
	running = false;
	interrupt = false;
	finished = false;
	operations = 0;
	
	ifstream pfile;
	string line;
	bool firstline = true;
	
	if(s != "") {
	
		pfile.open(s.c_str());
		if(pfile.is_open()) {
			while(! pfile.eof()) {
				getline(pfile,line);
				if(firstline) {
					char *sep = ",";
					char *t = new char[strlen(line.c_str())+1];
					strcpy(t,line.c_str());
					char *word;
					int i = 0;
					for(word = strtok(t,sep);word;word=strtok(NULL,sep)) {
						switch(i++) {
							case 0:
							  arch = new string(line);
							  break;
							  stack = atol(line.c_str());
							case 1:
							  heap = atol(line.c_str());
							  break;
							case 2:
							  registers = new string(line);
							  break;
						}
					}
					delete t;
					firstline = false;
				}
				else {
				  //instructions.push(Instruction(line));
					this->operations++;
				}
			}
			pfile.close();
		}
	}
}

bool Process::isFinished() {
	return finished;
}

void* Process::pThread(void* x) {
	while(true) {
		Process *t = (Process*)x;
		if(t->interrupt) {
			t->running = false;
			t->interrupt = false;
			pthread_exit(0);
		}
		if(t->operations == 0) {
			t->running = false;
			t->interrupt = false;
			t->finished = true;
			//cout << "the proc is finished" << std::endl;
			pthread_exit(0);
		}
		cout << "Executing 1 Cycle of Process \"" << *(t->name) << "\" -- " << t->operations-- << " Operations Left" << endl;
		((Process*) x)->pThreadAction(x); 
			
	}
}

void Process::pThreadAction(void *x) {
	struct timespec interval,remainder;
	interval.tv_sec = 1;
	interval.tv_nsec = 0;
	nanosleep(&interval, &remainder);
}

Process::~Process() {
	delete arch;
	delete registers;
	delete name;
}

bool Process::startProcess() {
	interrupt = false;
	running = true; 
	pthread_t p_thread;
	int res = pthread_create(&p_thread,NULL,static_cast<void*(*)(void*)>(pThread),(void*)this);
	return true;
}
bool Process::isRunning() {
	return running;
}
bool Process::isWaiting() {
	return !running;
}
bool Process::interruptProcess() {
	interrupt = true;
	return true;
}

InitProcess::InitProcess() : Process("") {
	//vos = v;
}

void InitProcess::pThreadAction(void *x) {
	//((InitProcess*) x)->launchProcess( new Process("processes/1.proc") );
}
