#ifndef _PARSER_
#define _PARSER_

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <cstdlib> 


extern bool DEBUG;


/* abstrakcyjna klasa definiuj�ca zachowanie zada� */

class Parser{

private:
	Parser(){}
	
public:
	/* rozpoznanie bie��cej instrukcji */
	
	static void readFile( std::vector<int>& code, std::string filename)
	{
		
	    std::ifstream file;
	    file.open(filename.c_str());
	    if (!file.is_open()) return;
		if(DEBUG) printf("Parsing\n");
	    std::string word;
	    static int commands_count=17;
		std::string commands[commands_count] = {
			"halt",
			"start",
			"add",
			"sub",
			"loadi",
			"mv",
			"label",
			"jmp",
			"jmpz",
			"jmpf",
			"rcv",
			"snd",
			"spawn",
			"exit",
			"abort",
			"print",
			"join"
		};
	    while (file >> word)
	    {
	    		if(DEBUG)
	    			printf("\tno. %2d \t word: %s ", code.size(), word.c_str());
	    		int index;
	    		for(index = 0; index < commands_count && commands[index] != word; index++);
	    		if(index<commands_count)
					code.push_back(index);
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
