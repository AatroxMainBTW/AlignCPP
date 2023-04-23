#include <vector>
#include <iostream>
#include "PreProcessing.hpp"


std::vector<std::string> union_Of(std::vector<std::string> arrA, std::vector<std::string> arrB) {
	
	std::vector<std::string> result(arrA.size()+ arrB.size());
	std::vector<std::string>::iterator it = std::set_union(arrA.begin(), arrA.end(), arrB.begin(), arrB.end(), result.begin());
	result.resize(it - result.begin());
	removeDuplicates(result);
	return result;
}



std::vector<std::string> intersection_Of(std::vector<std::string> arrA, std::vector<std::string> arrB) {
	std::vector<std::string> result(arrA.size() + arrB.size());

	std::vector<std::string>::iterator it = std::set_intersection(arrA.begin(), arrA.end(), arrB.begin(), arrB.end(), result.begin());
	result.resize(it - result.begin());


	return result;
}