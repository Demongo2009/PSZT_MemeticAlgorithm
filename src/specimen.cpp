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

void Specimen::changeValue(int num, float change, bool add){ // probably a method to remove
	if(add){
		this->valuesArray.at(num) += change;
	}
	else
		this->valuesArray.at(num) -= change;
}

void Specimen::setValuesArray(std::vector<float> values) {
    this->valuesArray = values;
}