#include "namegen.h"

#include <vector>
#include <iostream>
#include <ctime>

unsigned int count = 100;
unsigned int min_iter = 3;
unsigned int max_iter = 5;

int main(int argc, char* argv[]) {
	srand(time(NULL));

	markov::ChainVector<std::string> chains = markov::getChainsFromFile<std::string>("data.json");
	NameGenerator name_gen(chains, 2, 8);
	
	std::ofstream output_file("out.txt");
	for (unsigned int i = 0; i < 100; i++) {
		output_file << name_gen.generate() << "\n";
		name_gen.calculateStartChars();
	}
	output_file.close();
}