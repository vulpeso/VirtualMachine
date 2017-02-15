#ifndef _TASK_
#define _TASK_

#include "register.hpp"


extern bool DEBUG;



class ProgramMemory;
/* abstrakcyjna klasa definiuj¹ca zachowanie zadañ */
class Task{
protected:
	int arg1;
	int arg2;
	int arg3;
	
public:
	Task(int a1, int a2, int a3);
	virtual void execute(Register& r, ProgramMemory& p) = 0;
};



/*

	implementacje zadañ

*/


/* zatrzymanie maszyny /0 */
class TaskHalt : public Task{
	
public:
	TaskHalt(int a, int b, int c):Task(a,b,c){}
	void execute(Register &r, ProgramMemory &p);
};

/* NOP */
class TaskNOP : public Task{
public:
	TaskNOP(int a, int b, int c):Task(a,b,c){}
	void execute(Register& r, ProgramMemory& p);
};

/* dodawanie /3 */
class TaskAdd : public Task{	
public:
	TaskAdd(int a, int b, int c):Task(a,b,c){}
	void execute(Register& r, ProgramMemory& p);
};

/* odejmowanie /3 */
class TaskSub : public Task{	
public:
	TaskSub(int a, int b, int c):Task(a,b,c){}
	void execute(Register& r, ProgramMemory& p);
};

/* zapisanie liczby w rejestrze /2 */
class TaskLoadInt : public Task{	
public:
	TaskLoadInt(int a, int b, int c):Task(a,b,c){}
	void execute(Register& r, ProgramMemory& p);
};

/* przepisanie wartosci z rejestru do rejestru /2 */
class TaskMove : public Task{
public:
	TaskMove(int a, int b, int c):Task(a,b,c){}
	void execute(Register& r, ProgramMemory& p);
};

/* skok bezwarunkowy /1 */
class TaskJump : public Task{
public:
	TaskJump(int a, int b, int c):Task(a,b,c){}
	void execute(Register& r, ProgramMemory& p);
};

/* skok warunkowy - jesli wartosc w drugim podanym rejestrze jest ró¿na od zera /2 */
class TaskJumpIf : public Task{
public:
	TaskJumpIf(int a, int b, int c):Task(a,b,c){}
	void execute(Register& r, ProgramMemory& p);
};

class TaskJumpIfZero : public Task{
public:
	TaskJumpIfZero(int a, int b, int c):Task(a,b,c){}
	void execute(Register& r, ProgramMemory& p);
};

class TaskPrint : public Task{
public:
	TaskPrint(int a, int b, int c):Task(a,b,c){}
	void execute(Register& r, ProgramMemory& p);
};

/* do wielow¹tkowoœci */
class TaskSpawn : public Task{
public:
	TaskSpawn(int a, int b, int c):Task(a,b,c){}
	void execute(Register& r, ProgramMemory& p);
};

class TaskReceive : public Task{
public:
	TaskReceive(int a, int b, int c):Task(a,b,c){}
	void execute(Register& r, ProgramMemory& p);
};

class TaskSend : public Task{
public:
	TaskSend(int a, int b, int c):Task(a,b,c){}
	void execute(Register& r, ProgramMemory& p);
};

class TaskExit : public Task{
public:
	TaskExit(int a, int b, int c):Task(a,b,c){}
	void execute(Register& r, ProgramMemory& p);
};

class TaskAbort : public Task{
public:
	TaskAbort(int a, int b, int c):Task(a,b,c){}
	void execute(Register& r, ProgramMemory& p);
};

class TaskJoin : public Task{
public:
	TaskJoin(int a, int b, int c):Task(a,b,c){}
	void execute(Register& r, ProgramMemory& p);
};

#endif
