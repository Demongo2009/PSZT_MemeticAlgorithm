//
// Created by demongo on 13.11.2020.
//

#ifndef PSZT_MEMETICALGORITHM_POPULATION_H
#define PSZT_MEMETICALGORITHM_POPULATION_H

#include "specimen.h"
#include <vector>

class Population{
	int populationSize;

	std::vector<Specimen> specimenArray;

public:
	Population(std::vector<Specimen> vectorOfSpecimen):
			populationSize(vectorOfSpecimen.size())
	{
		for(auto s: vectorOfSpecimen){
			specimenArray.push_back(s);
		}
	}

	void setSpecimenArray(std::vector<Specimen> specimenArray);

	Specimen& getSpecimen(int index);

	void setSpecimen(int index, Specimen specimen);

};



#endif //PSZT_MEMETICALGORITHM_POPULATION_H
