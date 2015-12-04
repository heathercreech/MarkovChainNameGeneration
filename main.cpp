#include "namegen.h"

#include <vector>
#include <iostream>

int main(int argc, char* argv[]) {

	markov::ChainVector<std::string> chains = markov::getChainsFromFile<std::string>("test.json");
	printf("<Returned Chain>\nSrc:\t%s\nDest:\t%s\nProb:\t%f\n", chains[1].src.c_str(), chains[1].dest.c_str(), chains[1].probability);
}