#include "namegen.h"


//copy chs into the classes Markov chain vector
NameGenerator::NameGenerator(std::vector<markov::Chain<std::string>> cns) : chains(cns){
	calculateStartChars();
}


//takes a set of starting characters from the user
NameGenerator::NameGenerator(std::vector<markov::Chain<std::string>> cns, std::string strt_chars) : chains(cns){
	setStartingCharacters(strt_chars);
}


//generates a name from the current list of Markov chains
std::string NameGenerator::generate() {
	return "";
}


//
void NameGenerator::setStartingCharacters(std::string strt_chars) {
	starting_characters = strt_chars;
}


//determines a valid set of starting characters 
void NameGenerator::calculateStartChars() {
	setStartingCharacters("");
}