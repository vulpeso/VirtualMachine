#include <cstdio>
#include "machine.hpp"
#include "parser.hpp"

bool DEBUG = false;

int main(int argc, char *argv[]){
	if(argc!=2 && argc!=3) {
		printf("Usage: VM.exe filename\n");
		return 0;
	}
	if(argc==3){ // third argument turns debugging on
		DEBUG = true;
	}
	std::vector<int> code;
	Parser::readFile(code, std::string(argv[1]));
	Machine* machine = Machine::getInstance();
	machine->readProgram(code);
	machine->run();
	
	return 0;
}
