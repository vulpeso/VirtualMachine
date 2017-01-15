#ifndef _REGISTER_
#define _REGISTER_
#define NUM_REGS 4

/*

	Normal Register

*/

class Register{
	
	private:
		unsigned registerTab [NUM_REGS];
	
	public:
		Register(){
			for(int i=0; i<NUM_REGS; i++)
				registerTab[i]=0;
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
		
};

#endif
