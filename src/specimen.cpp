//
// Created by demongo on 13.11.2020.
//

#include "../include/memetic.h"

void Specimen::setFitness(float fitness){
	this->fitness = fitness;
}

float Specimen::getFitness() const{
	return fitness;
}

std::vector<float>& Specimen::getValuesArray(){
	return valuesArray;
}

void Specimen::changeValue(int num, float change, bool add){
	if(add){
		this->valuesArray.at(num) += change;
	}
	else
		this->valuesArray.at(num) -= change;
}