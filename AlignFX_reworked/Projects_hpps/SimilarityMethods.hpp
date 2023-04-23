#include "Mapping.hpp"
#include "ClassInstanceMapping.hpp"
#include "PreProcessing.hpp"
#include "AlgebricOperations.hpp"

std::vector<Mapping> jaccardSimilarity(std::vector<ClassInstanceMapping> cim1, std::vector<ClassInstanceMapping> cim2) {
	int total, inter;
	float distance;
	std::vector<Mapping> result;

	for (int i = 0; i < cim1.size(); i++) {
		Mapping map;
		std::string in = cim1[i].getConcept();

		preProcessString(in);
		
		map.setConceptA(in);

		for (int j = 0; j < cim2.size(); j++)
		{
				std::string in2 = cim2[j].getConcept();
				
				inter = intersection_Of(cim1[i].getInstances(), cim2[j].getInstances()).size();
				total = union_Of(cim1[i].getInstances(), cim2[j].getInstances()).size();
				distance = (float)inter / total;


				map.setConceptB(in2);
				map.setMappingRelation(MappingRelationship::EQUIVALENCE);
				map.setSimilarity(distance);
			
		}

		result.insert(result.end(), map);

	}
}