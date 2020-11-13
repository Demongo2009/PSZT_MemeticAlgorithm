//
// Created by demongo on 05.11.2020.
//

#ifndef PSZT_MEMETICALGORITHM_MEMETIC_H
#define PSZT_MEMETICALGORITHM_MEMETIC_H

#include <vector>
#include <queue>
#include <functional>
#include <iostream>

class Specimen{
	int specimenSize;
	float fitness;

	std::vector<float> valuesArray;

public:
	Specimen():specimenSize(1),fitness(0){
		valuesArray.reserve(1);
	};

	Specimen(std::vector<float> valuesArray):fitness(0){
		this->valuesArray = valuesArray;
		this->specimenSize = valuesArray.size();
	}

	void setFitness(float fitness){
		this->fitness = fitness;
	}

	float getFitness() const{
		return fitness;
	}

	std::vector<float>& getValuesArray(){
		return valuesArray;
	}

	void changeValue(int num, float change, bool add){
	    if(add){
            this->valuesArray.at(num) += change;
	    }
	    else
	        this->valuesArray.at(num) -= change;
	}
};

//class SpecimenComparison{
//	bool reverse;
//public:
//	SpecimenComparison(const bool& revparam=false)
//	{reverse=revparam;}
//	bool operator() (const Specimen& lhs, const Specimen&rhs) const
//	{
//		if (reverse) return (lhs.getFitness() > rhs.getFitness());
//		else return (lhs.getFitness() < rhs.getFitness());
//	}
//};

//typedef std::priority_queue<Specimen,std::vector<Specimen>, SpecimenComparison> SpecimenQueue;

class Population{
	int populationSize;

//	SpecimenQueue specimenQueue;  changed to std::vector<Specimen> specimenArray;
	std::vector<Specimen> specimenArray;

public:
	Population(std::vector<Specimen> vectorOfSpecimen):
	populationSize(vectorOfSpecimen.size())
	{
		for(auto s: vectorOfSpecimen){
			specimenArray.push_back(s);
		}
	}

	void setSpecimenArray(std::vector<Specimen> specimenArray){
		this->specimenArray = specimenArray;
	}

//	Specimen popSpecimen(){
//		Specimen s = *specimenArray.begin();
//		specimenArray.erase(specimenArray.begin());
//		return s;
//	}

	Specimen& getSpecimen(int index){
	    return specimenArray.at(index);
	}

	void setSpecimen(int index, Specimen specimen){
		if(index >= populationSize){
			std::cout << index << " - index out of range\n";
		}

		specimenArray[index] = specimen;
	}

};



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


	Specimen generateSpecimen(){
		std::vector<float> valuesVector;

		for(int i=0; i<specimenSize ; i++){
			int randomInt = rand() % ( (int)rangeOfValue * 10^(floatPrecision) );
			valuesVector.push_back( (float)randomInt / (float)( 10^(floatPrecision) ) );
		}

		return Specimen(valuesVector);
	}


	Population generatePopulation(){

		std::vector<Specimen> specimenVector;

		for(int i=0; i<populationSize; i++){

			specimenVector.push_back(generateSpecimen());

		}

		return Population(specimenVector);
	}



	void evaluatePopulation(Population& population){

		for(int i=0; i<populationSize; i++){
			Specimen specimen = population.getSpecimen(i);

			float fitness = evaluationFunction(specimen.getValuesArray());
			specimen.setFitness(fitness);
		}

	}


	void mutatePopulation(Population& population){
	    for(int i=0; i<populationSize; i++){
	        Specimen specimen = population.getSpecimen(i);

	        std::vector<float> valuesArray = specimen.getValuesArray();

	        for(int j=0; j<specimenSize; j++){
	            float mutationThreshold = (float)rand() / RAND_MAX;

	            if(mutationThreshold <= mutationProbability){
	                float value = valuesArray.at(j);

	                if(value + mutationStrength <= maxValue){
	                    specimen.changeValue(j, mutationStrength, true);
	                }
	                else
	                    specimen.changeValue(j, mutationStrength, false);
	            }
	        }
	    }
	}


	Population tournamentSelection(Population population){
	    std::vector<Specimen> vectorOfWinners;  // vector for the tournament winners
	    int firstIndex, secondIndex;

	    for(int i=0; i<populationSize; i++){
	        // choose 2 random specimens
	        firstIndex = rand() % populationSize;
	        secondIndex = rand() % populationSize;

            // choose the winner by comparing the fitness value
            // copy the winner to the vectorOfWinners
	        if(population.getSpecimen(firstIndex).getFitness() > population.getSpecimen(secondIndex).getFitness())
	            vectorOfWinners.push_back(population.getSpecimen(firstIndex));
	        else
	            vectorOfWinners.push_back(population.getSpecimen(secondIndex));
	    }

        Population nextGeneration = Population(vectorOfWinners);    // create new population using vector of winners
	    return nextGeneration;
	}


	Population localSearch(Population population){
		for(int i=0; i<populationSize; i++){
			Specimen specimen = population.getSpecimen(i);
			Specimen copy = specimen;


			for(int j=0; j<specimenSize; j++){
				float addDeleteThreshold = (float)rand() / RAND_MAX;


				if( addDeleteThreshold <= (float)1/2 ) {
					copy.changeValue(j, mutationStrength, true);
				}else{
					copy.changeValue(j, mutationStrength, false);
				}
			}

			float copyFittnes = evaluationFunction(copy.getValuesArray());

			if(copyFittnes > specimen.getFitness()){
				population.setSpecimen(i, copy);
			}
		}

		return population;
	}


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
	void run(){

		// generate an initial population
		Population population = generatePopulation();

		for(int i=0; i < numberOfGenerations; i++){
			// evaluate
			evaluatePopulation(population);

			// evolve (mutate only)
			mutatePopulation(population);

			// select (tournament selection)
			population = tournamentSelection(population);

			// local memetics
			population = localSearch(population);

		}



//		//Is that more accurate approach?
//
//		// generate an initial population
//		Population population = generatePopulation();
//		// evaluate
//		evaluatePopulation(population);
//
//		for(int i=0; i < numberOfGenerations; i++){
//			// select
//
//			// evolve
//
//			// evaluate
//
//			// local evolve?
//
//		}

	}

};



#endif //PSZT_MEMETICALGORITHM_MEMETIC_H
