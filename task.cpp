#include "task.hpp"
#include "pmemory.hpp"
#include "machine.hpp"

	Task::Task(int a1, int a2, int a3){
		arg1 = a1;
		arg2 = a2;
		arg3 = a3;
	}


/*

	implementacje zadañ

*/


/* zatrzymanie maszyny /0 */

	void TaskHalt::execute(Register &r, ProgramMemory &p){
		if(DEBUG) printf("halt %d %d %d\n", arg1, arg2, arg3);
		Machine::getInstance()->halt();
	}

	void TaskNOP::execute(Register& r, ProgramMemory& p){
		if(DEBUG) printf("NOP %d %d %d\n", arg1, arg2, arg3);
		//fixme
	}
	
/* dodawanie /3 */

	void TaskAdd::execute(Register& r, ProgramMemory& p){
		if(DEBUG) printf("add %d %d %d\n", arg1, arg2, arg3);
		r.set( arg1, r.get(arg2) + r.get(arg3) );
	}

/* odejmowanie /3 */

	void TaskSub::execute(Register& r, ProgramMemory& p){
		if(DEBUG) printf("sub %d %d %d\n", arg1, arg2, arg3);
		r.set( arg1, r.get(arg2) - r.get(arg3) );
	}

/* zapisanie liczby w rejestrze /2 */

	void TaskLoadInt::execute(Register& r, ProgramMemory& p){
		if(DEBUG) printf("loadi %d %d %d\n", arg1, arg2, arg3);
		r.set(arg1, arg2);
	}

/* przepisanie wartosci z rejestru do rejestru /2 */

	void TaskMove::execute(Register& r, ProgramMemory& p){
		if(DEBUG) printf("mv %d %d %d\n", arg1, arg2, arg3);
		r.set(arg1, r.get(arg2));
	}


/* skok bezwarunkowy /1 */

	void TaskJump::execute(Register& r, ProgramMemory& p){
		if(DEBUG) printf("jmp %d %d %d\n", arg1, arg2, arg3);
		p.jump(arg1);
	}

/* skok warunkowy - jesli wartosc w drugim podanym rejestrze jest ró¿na od zera /2 */

	void TaskJumpIf::execute(Register& r, ProgramMemory& p){
		if(DEBUG) printf("jmpf %d %d %d\n", arg1, arg2, arg3);
		if(r.get(arg2)!=0)
			p.jump(arg1);
	}

	void TaskJumpIfZero::execute(Register& r, ProgramMemory& p){
		if(DEBUG) printf("jmpz %d %d %d\n", arg1, arg2, arg3);
		if(r.get(arg2)==0)
			p.jump(arg1);
	}

	void TaskPrint::execute(Register& r, ProgramMemory& p){
		if(DEBUG) printf("print %d %d %d\n\n---------------------------\n\tPRINT RESULT:\n", arg1, arg2, arg3);
		printf("\t\t%d\n", r.get(arg1));
		if(DEBUG) printf("\n---------------------------\n");
	}
	
	/* do wielow¹tkowoœci */
	
	void TaskSpawn::execute(Register& r, ProgramMemory& p){
		if(DEBUG) printf("spawn %d %d %d\n", arg1, arg2, arg3);
		int PID = ThreadMonitor::getInstance()->create(arg1, arg2);
	}
	
	void TaskReceive::execute(Register& r, ProgramMemory& p){
		if(DEBUG) printf("receive %d %d %d\n", arg1, arg2, arg3);
		Thread& t = ThreadMonitor::getInstance()->getCurrentThread();
		int msg;
		if(t.inboxEmpty()){
			if(DEBUG) printf("Inbox empty\n");
			p.idle();
		}
		else{
			msg = t.checkInbox();
			if(DEBUG) printf("Inbox has: %d\n", msg);
			r.set(arg1, msg);
		}
	}

	void TaskSend::execute(Register& r, ProgramMemory& p){
		if(DEBUG) printf("send %d %d %d\n", arg1, arg2, arg3);
		ThreadMonitor::getInstance()->dispatchMsg(r.get(arg2), r.get(arg1));
	}
	
	void TaskExit::execute(Register& r, ProgramMemory& p){
		if(DEBUG) printf("exit %d %d %d\n", arg1, arg2, arg3);
		ThreadMonitor::getInstance()->getCurrentThread().exit();
	}
	
	void TaskAbort::execute(Register& r, ProgramMemory& p){
		if(DEBUG) printf("abort %d %d %d\n", arg1, arg2, arg3);
		ThreadMonitor::getInstance()->getThread(r.get(arg1)).exit();
	}
	
	void TaskJoin::execute(Register& r, ProgramMemory& p){
		if(DEBUG) printf("join %d %d %d\n", arg1, arg2, arg3);
		if(ThreadMonitor::getInstance()->getStateOf(r.get(arg1)) != st_unused)
			p.idle();
	}
