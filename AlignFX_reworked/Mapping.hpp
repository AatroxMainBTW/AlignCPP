#include <iostream>
#include "MappingRelationship.hpp"

class Mapping {
	std::string conceptA;
	std::string conceptB;
	float similarity;
	MappingRelationship mappingRs;

public:
	void setConceptA(std::string conceptAIn);
	void setConceptB(std::string conceptBIn);
	void setSimilarity(float similarityIn);
	void setMappingRelation(MappingRelationship mappingRsIn);

	std::string getConceptA();
	std::string getConceptB();
	float getSimilarity();
	MappingRelationship getMappingRelation();

	Mapping(std::string conceptAIn, std::string conceptBIn, float similarityIn, MappingRelationship mappingRsIn);
	Mapping();
	void toString();
};

Mapping::Mapping() {
	conceptA = "Unknown";
	conceptB = "Unknown";
	similarity = 0.0;

};
Mapping::Mapping(std::string conceptAIn, std::string conceptBIn, float similarityIn, MappingRelationship mappingRsIn) {
	conceptA = conceptAIn;
	conceptB = conceptBIn;
	similarity = similarityIn;
	mappingRs = mappingRsIn;
}


void Mapping::setConceptA(std::string conceptAIn) {
	conceptA = conceptAIn;

}

void Mapping::setConceptB(std::string conceptBIn) {
	conceptB = conceptBIn;
}


void Mapping::setSimilarity(float similarityIn) {
	similarity = similarityIn;
}

void Mapping::setMappingRelation(MappingRelationship mappingRsIn) {
	mappingRs = mappingRs;
}


std::string Mapping::getConceptA() {
	return conceptA;
}

std::string Mapping::getConceptB() {
	return conceptB;
}

float Mapping::getSimilarity() {
	return similarity;
}

MappingRelationship Mapping::getMappingRelation() {
	return mappingRs;
}

void Mapping::toString() {
	std::cout<<conceptA<<" "<<(char)mappingRs<<" "<<conceptB<<" : "<<similarity;
}