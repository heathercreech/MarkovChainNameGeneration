/*
	boost_assist.h is a utility for use with boost::property_tree::ptree
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