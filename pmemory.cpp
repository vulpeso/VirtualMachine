#include "pmemory.hpp"

/*

	Pamiêæ programu

*/
		// wczytanie programu do pamiêci
		
		ProgramMemory::ProgramMemory(){
			pc = 0;
		}
		int ProgramMemory::read(std::vector<int>& code){
			TaskFactory::decode(*this, code);
			
			return 0;
		}
		void ProgramMemory::jump(int num){
			pc = labels[num];
		}
		void ProgramMemory::setTasknum(int num){
			pc = num;
		}
		void ProgramMemory::setStart(){
			pc = program.size();
		}
		void ProgramMemory::setLabel(int label){
			labels[label] = program.size();
		}
		int ProgramMemory::getTaskByLabel(int label){
			return labels[label];
		}
		int ProgramMemory::getCurrent(){
			return pc;
		}
		std::vector<Task*>& ProgramMemory::getProgramRef(){
			return program;
		}
		// zwraca kolejn¹ instrukcjê
		Task* ProgramMemory::fetch()
		{
			if(pc<program.size()){
				if(DEBUG)
					printf("\npmemory.fetch: task number: %d \t",pc);
				return program[ pc++ ];
			}
			else{
				if(DEBUG)
					printf("\npmemory.fetch: no tasks to fetch \n",pc);
				return new TaskNOP(0,0,0);
			}
		}
		
		
		
		/* Task Factory */
		
		
	void TaskFactory::decode(ProgramMemory& pmem, std::vector<int>& code)
	{
		int arg1;
		int arg2;
		int arg3;
		std::vector<Task*>& program = pmem.getProgramRef();
		Task* task;
		for(int i=0; i<code.size(); i++)
	    {
	    	switch(code[i]){
	    		case 0:
	    			//halt
	    			task = new TaskHalt(0,0,0);
	    			break;
	    		case 1:
	    			//start
	    			task = new TaskNOP(0,0,0);
	    			pmem.setStart();
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
	    			task = new TaskLoadInt(arg1, arg2,0);
	    			break;
	    		case 5:
	    			//mv
	    			arg1 = code[++i];
	    			arg2 = code[++i];
	    			task = new TaskMove(arg1, arg2,0);
	    			break;
	    		case 6:
	    			//label
	    			arg1 = code[++i];
	    			pmem.setLabel(arg1);
	    			task = new TaskNOP(0,0,0);
	    			break;
	    		case 7:
	    			//jmp
	    			arg1 = code[++i];
	    			task = new TaskJump(arg1,0,0);
	    			break;
	    		case 8:
	    			//jmpz
	    			arg1 = code[++i];
	    			arg2 = code[++i];
	    			task = new TaskJumpIfZero(arg1, arg2,0);
	    			break;
	    		case 9:
	    			//jmpf
	    			arg1 = code[++i];
	    			arg2 = code[++i];
	    			task = new TaskJumpIf(arg1, arg2,0);
	    			break;
	    		case 10:
	    			//rcv
	    			arg1 = code[++i];
	    			task = new TaskReceive(arg1,0,0);
	    			break;
	    		case 11:
	    			//snd
	    			arg1 = code[++i];
	    			arg2 = code[++i];
	    			task = new TaskSend(arg1,arg2,0);
	    			break;
	    		case 12:
	    			//spawn
	    			arg1 = code[++i];
	    			arg2 = code[++i];
	    			task = new TaskSpawn(arg1,arg2,0);
	    			break;
	    		case 13:
	    			//exit
	    			task = new TaskExit(0,0,0);
	    			break;
	    		case 14:
	    			//abort
	    			arg1 = code[++i];
	    			task = new TaskAbort(arg1,0,0);
	    			break;
	    		case 15:
	    			//print
	    			arg1 = code[++i];
	    			task = new TaskPrint(arg1,0,0);
	    			break;
	    		case 16:
	    			//join
	    			arg1 = code[++i];
	    			task = new TaskJoin(arg1,0,0);
	    			break;
	    		default:
	    			task = new TaskNOP(0,0,0);
	    	}
	    	
	    	program.push_back(task);
	    }
	}
