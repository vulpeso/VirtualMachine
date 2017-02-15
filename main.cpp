#include <cstdio>
#include "machine.hpp"
#include "parser.hpp"

bool DEBUG = false;

int main(int argc, char *argv[]){
	if(argc!=2) {
		printf("Usage: VM.exe filename\n");
		return 0;
	}
	std::vector<int> code;
	Parser::readFile(code, std::string(argv[1]));
	Machine* m = Machine::getInstance();
	m->readProgram(code);
	m->run();
	
	return 0;
}
