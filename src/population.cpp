//
// Created by demongo on 13.11.2020.
//

#include "../include/memetic.h"

void Population::setSpecimenArray(std::vector<Specimen> specimenArray){
	this->specimenArray = specimenArray;
}


Specimen& Population::getSpecimen(int index){
	return specimenArray.at(index);
}

void Population::setSpecimen(int index, Specimen specimen){
	if(index >= populationSize){
		std::cout << index << " - index out of range\n";
	}

	specimenArray[index] = specimen;
}