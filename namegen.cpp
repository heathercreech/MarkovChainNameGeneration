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