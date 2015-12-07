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

#include "namegen.h"


//copy chs into the classes Markov chain vector
NameGenerator::NameGenerator(markov::ChainVector<std::string> cns) : chains(cns) {
	calculateStartChars();
	min_iter = 3;
	max_iter = 5;
}


//sets the min and max iterations of the generate() method
NameGenerator::NameGenerator(markov::ChainVector<std::string> cns, unsigned int min, unsigned int max) : chains(cns){
	calculateStartChars();
	min_iter = min;
	max_iter = max;
}


//takes a set of starting characters from the user
NameGenerator::NameGenerator(markov::ChainVector<std::string> cns, std::string strt_chars) : chains(cns){
	setStartingChars(strt_chars);
	min_iter = 3;
	max_iter = 5;
}


//sets the starting characters and min-max iterations
NameGenerator::NameGenerator(markov::ChainVector<std::string> cns, unsigned int min, unsigned int max, std::string strt_chars) : chains(cns) {
	setStartingChars(strt_chars);
	min_iter = min;
	max_iter = max;
}


//generates a name from the current list of Markov chains
std::string NameGenerator::generate() {
	
	if (isGood()) {

		std::string generated_name = starting_characters;

		//setup random roll for length
		std::random_device rd;
		std::default_random_engine generator(rd());
		std::uniform_int_distribution<unsigned int> length_distribution(min_iter, max_iter);


		for (unsigned int j = 0; j < length_distribution(generator); j++) {
			//select valid chains from current chain list
			markov::ChainVector<std::string> valid_chains;
			for (unsigned int i = 0; i < chains.size(); i++) {
				if (starting_characters == chains[i].src) {
					valid_chains.push_back(chains[i]);
				}
			}

			//scale probabilities to 100%
			double probability_sum = 0;
			for (markov::ChainVector<std::string>::iterator it = valid_chains.begin(); it != valid_chains.end(); it++) {
				probability_sum += it->probability;
			}

			double probility_scaler = 100 / probability_sum; //we will multiply the chains probabilities by this so we can roll against 100%

			//setup and make roll
			std::uniform_real_distribution<double> chain_distribution(0.0000001, 1);

			double roll = chain_distribution(generator);

			//determine chain to use
			double current_sum = 0; //used to determine where the roll lands
			for (unsigned int i = 0; i < valid_chains.size(); i++) {
				current_sum += valid_chains[i].probability * probility_scaler;

				//found the right value
				if (roll < current_sum) {
					setStartingChars(generated_name.back() + valid_chains[i].dest);
					generated_name += valid_chains[i].dest;
					break;
				}
			}
		}
		return generated_name;
	}
	return std::string("");
}


//runs calculateStartChars and then returns the result of generate()
//removes the need for the end user to call calculateStartChars on their own after each run
std::string NameGenerator::generateRandom() {
	calculateStartChars();
	return generate();
}


std::string NameGenerator::operator[](std::string strt_chars) {
	if (setStartingChars(strt_chars)) { //don't need this check, just used as a control for returning
		return generate();
	}
	printf("Error: supplied starting characters are not valid. Returning empty string...\n");
	return std::string("");
}

//returns true if the starting characters are valid (has an end state in the Markov chain)
bool NameGenerator::checkStartingChars() {
	for (unsigned int i = 0; i < chains.size(); i++) {
		if (chains[i].src == starting_characters) {
			return true;
		}
	}
	return false;
}


//sets the starting characters
bool NameGenerator::setStartingChars(std::string strt_chars) {
	starting_characters = strt_chars;
	if (!checkStartingChars()) {
		printf("Error: starting characters \'%s\' are not in the current list of Markov chains.\n", starting_characters.c_str());
		good = false;
		return false;
	}
	return true;
}


//determines a valid set of starting characters 
void NameGenerator::calculateStartChars() {
	int roll = rand() % chains.size(); //get an integer at random that is within the size of chains
	setStartingChars(chains[roll].src);
}