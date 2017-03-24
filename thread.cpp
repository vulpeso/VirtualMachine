#include "thread.hpp"


	void Thread::showRegs(){
		int i;
		printf( "regs of thread %d = ", PID );
		for( i=0; i<NUM_REGS; i++ ){
			if(i%4==0) printf("\n\t");
			printf( "%04d ", vreg.get( i ) );
		}
		printf( "\n" );
	}
	
	Thread::Thread(){
		state = st_unused;
	}
	
	void Thread::init(int ID, ProgramMemory* pm, int startnum){
		PID = ID;
		pmem = pm;
		state = st_ready;
		pc = startnum;
		if(DEBUG) printf("Thread %d initialized\n", PID);
	}
	
	void Thread::setRegister(Register r){
		vreg.copy(r);
	}
	
	int Thread::getPID(){ 
		return PID;
	}
	
	void Thread::exit(){
		state = st_unused;
		if(DEBUG) printf("Thread %d finished\n", PID);
		ThreadMonitor::getInstance()->switchThread();
	}
	
	void Thread::run()
	{
		if(state != st_unused){
			pmem->setTasknum(pc);
			if(DEBUG) showRegs();
			if(DEBUG) printf("--------------------------\n");
			pmem->fetch()->execute(vreg, *pmem);
			pc = pmem->getCurrent();
		}else{
			ThreadMonitor::getInstance()->switchThread();
		}
	}

	bool Thread::inboxEmpty(){
		return inbox.empty();
	}
	
	int Thread::checkInbox(){
		int msg = inbox.front();
		inbox.pop();
		return msg;
	}
	
	void Thread::receiveMessage(int msg){
		inbox.push(msg);
	}

/******************************************/
/*            Thread Monitor              */
/******************************************/

	ThreadMonitor::ThreadMonitor(){
		currentT = 0;
	}
	
	ThreadMonitor* ThreadMonitor::getInstance(){
		static ThreadMonitor tm;
		return &tm;
	}
	void ThreadMonitor::initialize(std::vector<int>& code){
		pmem.read(code);
		pool[currentT].init(currentT, &pmem, pmem.getCurrent());
	}
	int ThreadMonitor::create(int PIDdest, int label){
		int it = find(st_unused);
		int tasknum;
		if(it>=0){
			tasknum = pmem.getTaskByLabel(label);
			pool[it].init(it, &pmem, tasknum);
			pool[currentT].getRegister().set(PIDdest, it);
			pool[it].setRegister(pool[currentT].getRegister());
			currentT = it;
			return currentT;
		}else{
			if(DEBUG) printf("WARNING: Unable to spawn a thread\n");
			return -1;
		}
	}
	int ThreadMonitor::find(ThreadState state){
		for(int i = 0; i<NUMTHREADS; i++){
			if(pool[i].state == state)
				return i;
		}
		return -1;
	}
	ThreadState ThreadMonitor::getStateOf(int n){
		return pool[n].state;
	}
	Thread& ThreadMonitor::getThread(int n){
		return pool[n];
	}
	Thread& ThreadMonitor::getCurrentThread(){
		return pool[currentT];
	}
	int ThreadMonitor::getRunningThreadID(){
		return currentT;
	}
	void ThreadMonitor::proceed(){
		if(DEBUG) printStates();
		switchThread();
		pool[currentT].run();		
	}
	void ThreadMonitor::printStates(){
		printf("\nthreads: ");
		for(int i = 0; i<NUMTHREADS; i++){
			switch(pool[i].state){
				case st_unused:
					printf(" %d-unused;", i);
					break;
				case st_ready:
					printf(" %d-ready;", i);
					break;
			}
		}
		printf("\n");
	}
	void ThreadMonitor::dispatchMsg(int msg, int to){
		pool[to].receiveMessage(msg);
	}
	int ThreadMonitor::findNextReady(){
		int j;
		for(int i = 1; i<NUMTHREADS+1; i++){
			j=(currentT+i)%NUMTHREADS;
			if(pool[j].state == st_ready)
				return j;
		}
		return -1;
	}
	bool ThreadMonitor::switchThread(){
		int r = findNextReady();
		if(r>=0){
			currentT = r;
			if(DEBUG) printf("Thread %d is now running\n", r);
			return true;
		}
		return false;
	}
