#ifndef _PMEM_
#define _PMEM_


#include <cstdio>
#include <vector>
#include <map>
#include "task.hpp"



extern bool DEBUG;


/*

	Pamiêæ programu

*/

class ProgramMemory{
	
	private:
		std::vector<Task*> program;
		std::map<int, int> labels;
		
		/* program counter - iterator po zadaniach w pamiêci programu */
		int pc;

	public:
		// wczytanie programu do pamiêci
		ProgramMemory();
		//wczytuje ci¹g liczb/bytecode
		int read(std::vector<int>& code);
		//skok do etykiety
		void jump(int num);
		void setTasknum(int num);
		//ustawia pocz¹tkow¹ instrukcjê
		void setStart();
		void setLabel(int label);
		void idle(){
			pc--;
		}
		int getTaskByLabel(int label);
		//zwraca obecny nr zadania
		int getCurrent();
		std::vector<Task*>& getProgramRef();
		// zwraca kolejn¹ instrukcjê
		Task* fetch();
		~ProgramMemory(){
			labels.clear();
			for (std::vector< Task* >::iterator it = program.begin() ; it != program.end(); ++it)
		    {
		      delete (*it);
		    } 
		    program.clear();
		}
};


class TaskFactory{

private:
	TaskFactory(){}
	
public:
	/* rozpoznanie bie¿¹cej instrukcji */
	static void decode(ProgramMemory& pmem, std::vector<int>& code);
};



#endif
