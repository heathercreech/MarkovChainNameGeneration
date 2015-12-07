#include "namegen.h"

#include <vector>
#include <iostream>


int main(int argc, char* argv[]) {

	markov::ChainVector<std::string> chains = markov::getChainsFromFile<std::string>("data.json");
	printf("<Returned Chain>\nSrc:\t%s\nDest:\t%s\nProb:\t%f\n", chains[0].src.c_str(), chains[0].dest.c_str(), chains[0].probability);
}