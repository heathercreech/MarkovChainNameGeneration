/*
	namegen is a utility that procedurally generates names using Markov chains
	Copyright(C) 2015  Seth Creech
		This program is free software : you can redistribute it and / or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.
		This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
	GNU General Public License for more details.
		You should have received a copy of the GNU General Public License
	along with this program.If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#include "markov.h"

#include <string>
#include <vector>
#include <random>


//generates a name from a vector of Markov chains
class NameGenerator {
public:
	NameGenerator() = delete; //disable default constructor
	NameGenerator(markov::ChainVector<std::string>); //initializes the chain vector
	NameGenerator(markov::ChainVector<std::string>, unsigned int, unsigned int);
	NameGenerator(markov::ChainVector<std::string>, std::string); //initializes the chain vector, and sets the starting characters
	NameGenerator(markov::ChainVector<std::string>, unsigned int, unsigned int, std::string);
	
	std::string generate(); //returns a name generated with the current collection of Markov chains
	std::string generateRandom(); //runs calculateStartChars, then generates a name
	bool setStartingChars(std::string); //sets the starting characters, returns true if chars were set
	void calculateStartChars(); //randomly selects a set of starting characters if some are not provided

	std::string operator[](std::string); //set the starting characters and then returns a name
	
	bool isGood() { return good; };

private:

	//helper methods
	bool checkStartingChars(); //make sure that the starting characters can be used


	bool good = true;
	int order; //order of the Markov chains
	
	unsigned int min_iter;
	unsigned int max_iter;
	
	std::string starting_characters;
	markov::ChainVector<std::string> chains;
};