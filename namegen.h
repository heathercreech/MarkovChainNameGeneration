#pragma once


#include "markov.h"

#include <string>
#include <vector>



//generates a name from a vector of Markov chains
class NameGenerator {
public:
	NameGenerator() = delete;
	NameGenerator(std::vector<markov::Chain<std::string>>); //initializes the chain vector
	NameGenerator(std::vector<markov::Chain<std::string>>, std::string); //initializes the chain vector, and sets the starting characters

	
	std::string generate(); //returns a name generated with the current collection of Markov chains
	void setStartingCharacters(std::string); //sets the starting characters

private:

	//helper methods
	void calculateStartChars(); //randomly selects a set of starting characters if some are not provided


	int order; //order of the Markov chains
	std::string starting_characters;
	std::vector<markov::Chain<std::string>> chains;
};