#pragma once
#include <boost\property_tree\ptree.hpp>
#include <boost\property_tree\json_parser.hpp>

#include <string>
#include <iostream>


//contains functions that assist in the use of boost


//contains functions for use with ptree objects
namespace ba_ptree {
	//prints the entirety of a ptree, for debugging
	inline void printPtree(boost::property_tree::ptree const pt) {
		for (boost::property_tree::ptree::const_iterator it = pt.begin(); it != pt.end(); it++) {
			std::cout << it->first << ": " << it->second.get_value<std::string>() << std::endl;
			printPtree(it->second);
		}
	}


	//get the children of a ptree in ptree form
	inline std::vector<boost::property_tree::ptree> getChildren(boost::property_tree::ptree const pt) {
		std::vector<boost::property_tree::ptree> children;
		for (boost::property_tree::ptree::const_iterator it = pt.begin(); it != pt.end(); it++) {
			children.push_back(it->second);
		}
		return children;
	}
}