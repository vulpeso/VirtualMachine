#ifndef _VIRTUAL_
#define _VIRTUAL_

#include <cstdio>
#include "register.h"
#include "pmemory.h"


/* 

	Implementacja wirtualnej maszyny pozwalaj¹cej na uruchomienie kilku w¹tków, 
	które realizuj¹ proste instrukcje komunikacji z innymi w¹tkami 
	z mo¿liwoœci¹ zmiany mechanizmu szeregowania kolejnoœci wykonywania w¹tków. 
	
	Mechanizm zarz¹dzania pamiêci¹ oparty na rejestrach. 
	Architektura docelowa: x86/x64.
 
*/

class Machine{
	private: 
		Register vreg;
		ProgramMemory pmem;
		/* the VM runs until this flag becomes 0 */
		int running = 1;
		
		/* instruction fields */
		int instrNum = 0;
		int reg1     = 0;
		int reg2     = 0;
		int reg3     = 0;
		int imm      = 0;
		
		/* decode a word */
		void decode( int instr )
		{
			instrNum = (instr & 0xF000) >> 12;
			reg1     = (instr & 0xF00 ) >>  8;
			reg2     = (instr & 0xF0  ) >>  4;
			reg3     = (instr & 0xF   );
			imm      = (instr & 0xFF  );
		}
		
		/* evaluate the last decoded instruction */
		void eval()
		{
			switch( instrNum )
			{
				case 0:
					/* halt */
					printf( "halt\n" );
					running = 0;
					break;
				case 1:
					/* loadi */
					printf( "loadi r%d #%d\n", reg1, imm );
					vreg.set(reg1,imm);
					break;
				case 2:
					/* add */
					printf( "add r%d r%d r%d\n", reg1, reg2, reg3 );
					vreg.set( reg1, vreg.get(reg2) + vreg.get(reg2) );
					break;
			}
		}
		
		/* display all registers as 4-digit hexadecimal words */
		void showRegs()
		{
			int i;
			printf( "regs = " );
			for( i=0; i<NUM_REGS; i++ )
				printf( "%04X ", vreg.get( i ) );
			printf( "\n" );
		}
	public: 
		Machine(){
			
		}
		void readProgram(){
			pmem.read();
		}
		void run()
		{
			while(running)
			{
				showRegs();
				decode(pmem.fetch());
				eval();
			}
			showRegs();
		}
};

#endif
