//
// Created by demongo on 05.11.2020.
//

#ifndef PSZT_MEMETICALGORITHM_MEMETIC_H
#define PSZT_MEMETICALGORITHM_MEMETIC_H

#include <vector>
#include <queue>
#include <functional>
#include <iostream>
#include "specimen.h"
#include "population.h"


typedef std::function<float(std::vector<float>)> EvaluationFunction;

class MemeticAlgorithm{
	// algorithm parameters
	int seed;
	int populationSize;
	int specimenSize;
	float minValue;
	float maxValue;
	float rangeOfValue;
	int floatPrecision;
	int numberOfGenerations;

	float mutationProbability;
	float mutationStrength;

	EvaluationFunction evaluationFunction;


	Specimen generateSpecimen();


	Population generatePopulation();



	void evaluatePopulation(Population& population);


	void mutatePopulation(Population& population);


	Population tournamentSelection(Population population);


	Population localSearch(Population population);


public:

	MemeticAlgorithm(int seed, int populationSize, int specimenSize,
			float minValue, float maxValue, int precision, int numberOfGenerations, float mutationProbability,
			float mutationStrength, EvaluationFunction evaluationFunction):
			seed(seed),
			populationSize(populationSize), specimenSize(specimenSize),
			minValue(minValue), maxValue(maxValue), floatPrecision(precision),
			numberOfGenerations(numberOfGenerations),mutationProbability(mutationProbability),
			mutationStrength(mutationStrength),evaluationFunction(evaluationFunction){
		srand(seed);
		this->rangeOfValue = maxValue - minValue;
		if(rangeOfValue<=0) {
			std::cout << "max is not larger than min\n";
		};
	}


	// main algorithm
	void run();


};



#endif //PSZT_MEMETICALGORITHM_MEMETIC_H
