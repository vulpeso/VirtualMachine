#ifndef _REGISTER_
#define _REGISTER_
#define NUM_REGS 16

#include <algorithm>
#include <iterator>
/*

	Normal Register

*/

class Register{
	
	private:
		int registerTab [NUM_REGS]; //zaleznie od architektury
	
	public:
		Register(){
			for(int i=0; i<NUM_REGS; i++)
				registerTab[i]=0;
		}
		// doda� wyrzucanie wyj�tk�w
		int set(int numreg, int value){
			if(numreg<NUM_REGS)
			{
				registerTab[numreg] = value;
				return value;
			}
			return 0;
		}
		void copy(Register& r){
			for(int i=0; i<NUM_REGS; i++)
				registerTab[i] = r.registerTab[i];
		}
		// doda� wyrzucanie wyj�tk�w
		int get(int numreg){
			if(numreg<NUM_REGS)
			{
				return registerTab[numreg];
			}
			return 0;
		}
		
};

#endif
