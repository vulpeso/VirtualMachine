#ifndef _TASKFACTORY_
#define _TASKFACTORY_
#include "task.hpp"
/* abstrakcyjna klasa definiuj¹ca zachowanie zadañ */

class TaskFactory{

private:
	TaskFactory(){}
	
public:
	/* rozpoznanie bie¿¹cej instrukcji */
	static void decode(ProgramMemory& pmem, std::vector<int>& code)
	{
		int arg1;
		int arg2;
		int arg3;
		std::vector<Task*>& program = pmem.getProgramRef();
		std::vector<int>& labels = pmem.getLabelsRef();
		Task* task;
		for(int i=0; i<code.size(); i++)
	    {
	    	switch(code[i]){
	    		case 0:
	    			//halt
	    			task = new TaskHalt();
	    			break;
	    		case 1:
	    			//start
	    			pmem.setStart(program.size());
	    			task = new TaskNOP();
	    			break;
	    		case 2:
	    			//add
	    			arg1 = code[++i];
	    			arg2 = code[++i];
	    			arg3 = code[++i];
	    			task = new TaskAdd(arg1, arg2, arg3);
	    			break;
	    		case 3:
	    			//sub
	    			arg1 = code[++i];
	    			arg2 = code[++i];
	    			arg3 = code[++i];
	    			task = new TaskSub(arg1, arg2, arg3);
	    			break;
	    		case 4:
	    			//loadi
	    			arg1 = code[++i];
	    			arg2 = code[++i];
	    			task = new TaskLoadInt(arg1, arg2);
	    			break;
	    		case 5:
	    			//mv
	    			arg1 = code[++i];
	    			arg2 = code[++i];
	    			task = new TaskMove(arg1, arg2);
	    			break;
	    		case 6:
	    			//label
	    			arg1 = code[++i];
	    			labels[arg1] = program.size();
	    			task = new TaskNOP();
	    			break;
	    		case 7:
	    			//jmp
	    			arg1 = code[++i];
	    			task = new TaskJump(arg1);
	    			break;
	    		case 8:
	    			//jmpz
	    			arg1 = code[++i];
	    			arg2 = code[++i];
	    			task = new TaskJumpIfZero(arg1, arg2);
	    			break;
	    		case 9:
	    			//jmpf
	    			arg1 = code[++i];
	    			arg2 = code[++i];
	    			task = new TaskJumpIf(arg1, arg2);
	    			break;
	    		case 10:
	    			//rcv
	    			arg1 = code[++i];
	    			task = new TaskNOP();//fixme
	    			break;
	    		case 11:
	    			//snd
	    			arg1 = code[++i];
	    			arg2 = code[++i];
	    			task = new TaskNOP();//fixme
	    			break;
	    		case 12:
	    			//spawn
	    			arg1 = code[++i];
	    			arg2 = code[++i];
	    			task = new TaskNOP();//fixme
	    			break;
	    		case 13:
	    			//exit
	    			task = new TaskNOP();//fixme
	    			break;
	    		case 14:
	    			//abort
	    			arg1 = code[++i];
	    			task = new TaskNOP();//fixme
	    			break;
	    		case 15:
	    			//print
	    			arg1 = code[++i];
	    			task = new TaskNOP();//fixme
	    			break;
	    		default:
	    			task = new TaskNOP();
	    	}
	    	program.push_back(task);
	    }
	}
};


#endif
