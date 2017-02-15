#ifndef _VIRTUAL_
#define _VIRTUAL_

#include <cstdio>
#include "thread.hpp"

extern bool DEBUG;

/* 

	Implementacja wirtualnej maszyny pozwalaj¹cej na uruchomienie kilku w¹tków, 
	które realizuj¹ proste instrukcje komunikacji z innymi w¹tkami 
	z mo¿liwoœci¹ zmiany mechanizmu szeregowania kolejnoœci wykonywania w¹tków. 
	
	Mechanizm zarz¹dzania pamiêci¹ oparty na rejestrach. 
	Architektura docelowa: x86/x64.
 
*/

class Machine{
	private: 
		ThreadMonitor* tm;
		
		/* gdy zmieni siê 0, maszyna przestaje dzia³aæ */
		int isRunning;
		
		/* prywatny konstruktor - to jest singleton */
		Machine();
		
	public: 
		static Machine* getInstance();
		void readProgram(std::vector<int>& code);
		void run();
		void halt();
};

#endif
