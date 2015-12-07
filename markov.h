/*
	markov.h is an attempt at a generic implementation of Markov chains for C++
	Copyright (C) 2015  Seth Creech
		This program is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.
		This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.
		You should have received a copy of the GNU General Public License
	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

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

		std::vector<boost::property_tree::ptree> chain_array = ba_ptree::getChildren(ba_ptree::getChildren(ba_ptree::getChildren(pt)[0])[0]);

		for (unsigned int i = 0; i < chain_array.size(); i++) {
			Chain<T> current_chain;
			
			current_chain.src = chain_array[i].get<T>("src");
			current_chain.dest = chain_array[i].get<T>("dest");
			current_chain.probability = chain_array[i].get<double>("probability");

			chains.push_back(current_chain);
		}

		return chains;
	}

}