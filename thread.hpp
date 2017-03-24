#ifndef _THREAD_
#define _THREAD_

#define NUMTHREADS 4

#include "pmemory.hpp"
#include <queue>
#include <algorithm>


extern bool DEBUG;



enum ThreadState{
	st_unused,
	st_ready
};


class ThreadMonitor;


class Thread{
private:
	Register vreg;
	ProgramMemory* pmem;
	int pc;
	int PID;
	std::queue<int> inbox;
	
	void showRegs();
public:
	ThreadState state;
	
	Thread();
	void init(int ID, ProgramMemory* pm, int startnum);
	void setRegister(Register r);
	Register& getRegister(){
		return vreg;
	}
	int getPID();
	void exit();
	void run();
	bool inboxEmpty();
	int checkInbox();
	void receiveMessage(int msg);
};

class ThreadMonitor{
private:
	ProgramMemory pmem;
	Thread pool[NUMTHREADS];
	int currentT;
	//ThreadSwitchStrategy tss;
	ThreadMonitor();
public:
	static ThreadMonitor* getInstance();
	void initialize(std::vector<int>& code);
	int create(int PIDdest, int label);
	int find(ThreadState st);
	ThreadState getStateOf(int n);
	Thread& getThread(int n);
	Thread& getCurrentThread();
	int getRunningThreadID();
	void proceed();
	bool switchThread();
	void printStates();
	int findNextReady();
	void dispatchMsg(int msg, int to);
};

#endif
