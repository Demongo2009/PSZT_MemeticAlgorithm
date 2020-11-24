//
// Created by demongo on 05.11.2020.
//

#ifndef PSZT_MEMETICALGORITHM_MEMETIC_H
#define PSZT_MEMETICALGORITHM_MEMETIC_H

#include <vector>
#include <queue>
#include <functional>
#include <iostream>
#include <random>
#include "specimen.h"
#include "population.h"
#include "../lib/Eigen/Core"
#include "../lib/LBFGS.h"



typedef std::function<float(std::vector<float>)> EvaluationFunction;
typedef std::function<double(Eigen::Matrix<double, Eigen::Dynamic, 1>&, Eigen::Matrix<double, Eigen::Dynamic, 1>&)> LocalSearchFunToMin;

class MemeticAlgorithm{
	// algorithm parameters
	std::mt19937 gen;
	int seed;

	int populationSize;
	int specimenSize;
	float minValue;
	float maxValue;
	float rangeOfValue;
	int numberOfGenerations;

	float mutationProbability;
	float mutationStrength;

	EvaluationFunction evaluationFunction;
	LocalSearchFunToMin fun;

	float localSearchProbability;
	int localSearchNumOfIterations;
	double localSearchEpsilon;

	LBFGSpp::LBFGSParam<double> param;
	std::vector<Specimen> bestSpecimensFound;

	//---------------------------------------

	Specimen generateSpecimen();


	Population generatePopulation();



	void evaluatePopulation(Population& population);


	void mutatePopulation(Population& population);


	Population tournamentSelection(Population population);


	void localSearch(Population population);


public:

	MemeticAlgorithm(int seed, int populationSize, int specimenSize,
			float minValue, float maxValue,
			int numberOfGenerations, float mutationProbability,
			float mutationStrength, float localSearchProbability,
			int localSearchNumOfIterations, double localSearchEpsilon,
			EvaluationFunction evaluationFunction, LocalSearchFunToMin fun):
			seed(seed),
			populationSize(populationSize), specimenSize(specimenSize),
			minValue(minValue), maxValue(maxValue),
			numberOfGenerations(numberOfGenerations),mutationProbability(mutationProbability),
			mutationStrength(mutationStrength),evaluationFunction(evaluationFunction), localSearchProbability(localSearchProbability),
			localSearchNumOfIterations(localSearchNumOfIterations), localSearchEpsilon(localSearchEpsilon), fun(fun){

		gen.seed(seed);
		param.epsilon = localSearchEpsilon;
		param.max_iterations = localSearchNumOfIterations;

		this->rangeOfValue = maxValue - minValue;
		if(rangeOfValue<=0) {
			std::cout << "max is not larger than min\n";
		};

	}


	// main algorithm
	Specimen run();


};



#endif //PSZT_MEMETICALGORITHM_MEMETIC_H
