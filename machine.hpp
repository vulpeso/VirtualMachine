#ifndef _VIRTUAL_
#define _VIRTUAL_

#include <cstdio>
#include "thread.hpp"

extern bool DEBUG;

/* 

	Implementacja wirtualnej maszyny pozwalajacej na uruchomienie kilku watkow, 
	ktore realizuja proste instrukcje komunikacji z innymi watkami 
	z mozliwoscia zmiany mechanizmu szeregowania kolejnosci wykonywania watkow. 
	
	Mechanizm zarzadzania pamiecia oparty na rejestrach. 
	Architektura docelowa: x86/x64.
 
*/

class Machine{
	private: 
		ThreadMonitor* tm;
		
		/* gdy zmieni sie 0, maszyna przestaje dzialac */
		int running;
		
		/* prywatny konstruktor - to jest singleton */
		Machine();
		
	public: 
		static Machine* getInstance();
		void readProgram(std::vector<int>& code);
		void run();
		void halt();
};

#endif
