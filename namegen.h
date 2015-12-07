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