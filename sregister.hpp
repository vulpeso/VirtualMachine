#ifndef _SREGISTER_
#define _SREGISTER_
#define NUM_REGS 4

/*

	Singleton Register

*/

class SRegister{
	
	private:
		unsigned registerTab [NUM_REGS];
	
		SRegister(){
			for(int i=0; i<NUM_REGS; i++)
				register[i]=0;
		}
		//Register(Register const&);              // Don't Implement
        //void operator=(Register const&);         // Don't implement
	
	public:
		static &SRegister getInstance(){
			static SRegister instance;
			return instance;
		}
		// dodaæ wyrzucanie wyj¹tków
		unsigned set(int numreg, unsigned value){
			if(numreg<NUM_REGS)
			{
				registerTab[numreg] = value;
				return value;
			}
			return 0;
		}
		// dodaæ wyrzucanie wyj¹tków
		unsigned get(int numreg){
			if(numreg<NUM_REGS)
			{
				return registerTab[numreg];
			}
			return 0;
		}
	
	//zapobiega tworzeniu kopii:
        SRegister(SRegister const&) 			= delete;
        void operator=(SRegister const&)  	= delete;
}

#endif
