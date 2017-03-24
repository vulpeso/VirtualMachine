#ifndef _PMEM_
#define _PMEM_


#include <cstdio>
#include <vector>
#include <map>
#include "task.hpp"



extern bool DEBUG;


/*

	Pami�� programu

*/

class ProgramMemory{
	
	private:
		std::vector<Task*> program;
		std::map<int, int> labels;
		
		/* program counter - iterator po zadaniach w pami�ci programu */
		int pc;

	public:
		// wczytanie programu do pami�ci
		ProgramMemory();
		//wczytuje ci�g liczb/bytecode
		int read(std::vector<int>& code);
		//skok do etykiety
		void jump(int num);
		void setTasknum(int num);
		//ustawia pocz�tkow� instrukcj�
		void setStart();
		void setLabel(int label);
		void idle(){
			pc--;
		}
		int getTaskByLabel(int label);
		//zwraca obecny nr zadania
		int getCurrent();
		std::vector<Task*>& getProgramRef();
		// zwraca kolejn� instrukcj�
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
	/* rozpoznanie bie��cej instrukcji */
	static void decode(ProgramMemory& pmem, std::vector<int>& code);
};



#endif
