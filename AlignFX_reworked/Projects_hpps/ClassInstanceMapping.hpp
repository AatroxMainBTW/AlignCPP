#include<iostream>
#include<vector>


class ClassInstanceMapping {
	std::string concept;
	std::vector<std::string> instances;

public:
	void setConcept(std::string conceptIn);
	void setInstances(std::vector<std::string> instancesIn);
	std::string getConcept();
	std::vector<std::string> getInstances();
	//ClassInstanceMapping(std::string conceptIn, std::vector<std::string> instancesIn);

};

/*ClassInstanceMapping::ClassInstanceMapping(std::string conceptIn, std::vector<std::string> instancesIn) {
	concept = conceptIn;
	instances = instancesIn;
}*/

void ClassInstanceMapping::setConcept(std::string conceptIn) {
	concept = conceptIn;
}

void ClassInstanceMapping::setInstances(std::vector<std::string> instancesIn) {
	instances = instancesIn;
}

std::string ClassInstanceMapping::getConcept() {
	return concept;
}

std::vector<std::string> ClassInstanceMapping::getInstances() {
	return instances;
}