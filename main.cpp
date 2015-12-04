#include "markov.h"
#include "namegen.h"

#include <vector>


int main(int argc, char* argv[]) {
	std::vector<markov::Chain<std::string>> chains = markov::getChainsFromFile<std::string>("chain_database.txt");

	NameGenerator name_gen(chains);
}