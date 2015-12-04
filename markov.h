#pragma once

#include "boost_assist.h"

#include <boost\lexical_cast.hpp>
#include <boost\tokenizer.hpp>
#include <boost\property_tree\ptree.hpp>
#include <boost\property_tree\json_parser.hpp>

#include <fstream>
#include <vector>


//all the classes and functions required for a markov chain implementation
namespace markov {

	//the actual representation of the chain
	template<typename T>
	struct Chain {
		T src; //the beginning state. using a vector allows easy determination of the order of the chain
		T dest; //what the src leads to
		double probability = 0; //probability that src leads to dest
		
		
		//default constructor
		Chain() : src(), dest(){
		};


		//intialization constructor
		Chain(T s, T d, double p){
			src = s;
			dest = d;
			probability = p;
		};


		//returns the order (the size of src)
		int getOrder() {
			return src.size();
		};
	};


	template<typename T>
	using ChainVector = std::vector<Chain<T>>;


	/*	generates a vector of chains from a file (each line is a chain)
		uses json, required variables:
		"chains" - an array of the chains ("chains": [{}, ...]
		
		each element of a chain array must have the following values:
		"src" - the state that is started with
		"dest" - the state that is transitioned to
		"probability" - the probability that state src will transfer to state dest
	*/
	template<typename T>
	ChainVector<T> getChainsFromFile(std::string file_path) {
		ChainVector<T> chains;
		std::ifstream json_file(file_path);
		
		if (json_file.bad()) {
			printf("Error: unable to open file \"%s\"\n", file_path.c_str());
			return chains;
		}
		
		std::stringstream ss;
		ss.str(std::string((std::istreambuf_iterator<char>(json_file)), std::istreambuf_iterator<char>()));

		boost::property_tree::ptree pt;
		boost::property_tree::read_json(ss, pt);

		boost::property_tree::ptree chain_nodes = pt.get_child("chains"); //go into the array
		std::vector<boost::property_tree::ptree> children = ba_ptree::getChildren(chain_nodes); //get vector the elements of the array

		for (unsigned int i = 0; i < children.size(); i++) {
			Chain<T> current_chain;
			
			current_chain.src = children[i].get<T>("src");
			current_chain.dest = children[i].get<T>("dest");
			current_chain.probability = children[i].get<double>("probability");

			chains.push_back(current_chain);
		}

		return chains;
	}

}