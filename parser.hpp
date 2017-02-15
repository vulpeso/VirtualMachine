#ifndef _PARSER_
#define _PARSER_

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <cstdlib> 


extern bool DEBUG;


/* abstrakcyjna klasa definiuj¹ca zachowanie zadañ */

class Parser{

private:
	Parser(){}
	
public:
	/* rozpoznanie bie¿¹cej instrukcji */
	
	static void readFile( std::vector<int>& code, std::string filename)
	{
		
	    std::ifstream file;
	    file.open(filename.c_str());
	    if (!file.is_open()) return;
		if(DEBUG) printf("Parsing\n");
	    std::string word;
	    while (file >> word)
	    {
	    		if(DEBUG)
	    			printf("\tno. %2d \t word: %s ", code.size(), word.c_str());
	    		if(word == "halt")
	    			code.push_back(0);
	    		else if(word == "start")
	    			code.push_back(1);
	    		else if(word == "add")
	    			code.push_back(2);
	    		else if(word == "sub")
	    			code.push_back(3);
	    		else if(word == "loadi")
	    			code.push_back(4);
	    		else if(word == "mv")
	    			code.push_back(5);
	    		else if(word == "label")
	    			code.push_back(6);
	    		else if(word == "jmp")
	    			code.push_back(7);
	    		else if(word == "jmpz")
	    			code.push_back(8);
	    		else if(word == "jmpf")
	    			code.push_back(9);
	    		else if(word == "rcv")
	    			code.push_back(10);
	    		else if(word == "snd")
	    			code.push_back(11);
	    		else if(word == "spawn")
	    			code.push_back(12);
	    		else if(word == "exit")
	    			code.push_back(13);
	    		else if(word == "abort")
	    			code.push_back(14);
	    		else if(word == "print")
	    			code.push_back(15);
	    		else if(word == "join")
	    			code.push_back(16);
	    		else 
	    			code.push_back(strtol(word.c_str(), NULL, 0));
	    		if(DEBUG)
	    			printf("\t code: %d\n", code.back());
	    }
	    if(DEBUG) printf("Success! Code parsed\n\n");
	    file.close();
	}	
};


#endif
