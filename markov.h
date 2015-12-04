#pragma once

#include <boost\lexical_cast.hpp>
#include <boost\tokenizer.hpp>

#include <fstream>
#include <vector>

//all the classes and functions required for a markov chain implementation
namespace markov {
	
	//
	template<typename T>
	class LexicalVector : public std::vector<T> {
	public:
		//constructors (just pass throughs into the base vector constructors
		LexicalVector() : std::vector<T>() {};
		LexicalVector(std::initializer_list<T> init_list) : std::vector<T>(init_list) {};


		//for use with boost's lexical_cast
		friend std::istream& operator>>(std::istream& is, const LexicalVector<T>& lv) {
			return is;
		};
	private:
	};



	//the actual representation of the chain
	template<typename T>
	struct Chain {
		LexicalVector<T> src; //the beginning state. using a vector allows easy determination of the order of the chain
		T dest = 0; //what the src leads to
		double probability = 0; //probability that src leads to dest
		
		
		//default constructor
		Chain() : src(){
		};


		//intialization constructor
		Chain(LexicalVector<T> s, T d, double p) : src(s) {
			dest = d;
			probability = p;
		};


		//returns the order (the size of src)
		int getOrder() {
			return src.size();
		};
	};



	//generates a vector of chains from a file (each line is a chain)
	//line format: "stateA:probability:stateB" (will probably change to a json format)
	template<typename T>
	std::vector<Chain<T>> getChainsFromFile(std::string file_path) {
		std::vector<Chain<T>> chains;

		std::ifstream input_file(file_path);

		if (input_file.bad()) {
			printf("Error: unable to read file \"%s\", returning empty vector.\n", file_path.c_str());
			return chains;
		}

		boost::char_separator<char> sep(":");
		std::string line = "";

		int line_count = 1; //for debuging
		while (std::getline(input_file, line)) {
			Chain<T> current_chain;
			boost::tokenizer<boost::char_separator<char>> tok(line, sep);

			int element_count = 0;
			for (boost::tokenizer<boost::char_separator<char>>::iterator it = tok.begin(); it != tok.end(); it++) {
				switch (element_count) {
				case 0:
					current_chain.src = boost::lexical_cast<LexicalVector<T>>(*it);
					break;
				case 1:
					current_chain.probability = boost::lexical_cast<double>(*it);
					break;
				case 2:
					current_chain.dest = boost::lexical_cast<T>(*it);
					break;
				default:
					printf("Error: too many entries for a markov chain on line %i\n", line_count);
				}

				element_count++;
			}

			chains.push_back(current_chain);
			line_count++;
		}

		return chains;
	}

}
