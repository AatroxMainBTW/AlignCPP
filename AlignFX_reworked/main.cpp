#include <iostream>
#include "ClassInstanceMapping.hpp"
#include "PreProcessing.hpp"
#include "AlgebricOperations.hpp"
#include "Mapping.hpp"
#include "SimilarityMethods.hpp"


int main() {
	std::vector<std::string> A { "BMW","Merco","Willy","idk" };
	std::vector<std::string> B { "BMW","Alpha","Willy","idk","Delta" };
	std::string clA = "car";
	std::string clB = "wat";

	ClassInstanceMapping cl1;
	cl1.setConcept(clA);
	cl1.setInstances(A);
	//ClassInstanceMapping cl2(clB, B);
	std::vector<ClassInstanceMapping> cls1{cl1};
	//std::vector<ClassInstanceMapping> cls2{cl2};
	//std::vector<Mapping> mps = jaccardSimilarity(cls1, cls2);

	return 0;
}
