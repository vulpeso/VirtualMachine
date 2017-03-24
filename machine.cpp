#include "machine.hpp"
				
		/* prywatny konstruktor - to jest singleton */
		Machine::Machine(){
			running = 1;
			tm = ThreadMonitor::getInstance();
		}
		
		Machine* Machine::getInstance(){
			static Machine instance;
			return &instance;
		}
		
		void Machine::readProgram(std::vector<int>& code){
			tm->initialize(code);
		}
		void Machine::run(){
			if(DEBUG) printf("Running Virtual Machine...\n");
			while(running)
			//for(int i = 0; i<20; i++)
				tm->proceed();
		}
		void Machine::halt(){
			running = 0;
		}
		
		
		
