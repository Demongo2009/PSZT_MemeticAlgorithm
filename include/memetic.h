//
// Created by demongo on 05.11.2020.
//

#ifndef PSZT_MEMETICALGORITHM_MEMETIC_H
#define PSZT_MEMETICALGORITHM_MEMETIC_H

#include <vector>
#include <queue>
#include <functional>

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

	std::vector<float> getValuesArray(){
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

class SpecimenComparison{
	bool reverse;
public:
	SpecimenComparison(const bool& revparam=false)
	{reverse=revparam;}
	bool operator() (const Specimen& lhs, const Specimen&rhs) const
	{
		if (reverse) return (lhs.getFitness() > rhs.getFitness());
		else return (lhs.getFitness() < rhs.getFitness());
	}
};

typedef std::priority_queue<Specimen,std::vector<Specimen>, SpecimenComparison> SpecimenQueue;

class Population{
	int populationSize;

	SpecimenQueue specimenQueue;    // std::vector<Specimen> specimenArray;

public:
	Population(std::vector<Specimen> vectorOfSpecimen):
	populationSize(vectorOfSpecimen.size())
	{
		for(auto s: vectorOfSpecimen){
			specimenQueue.push(s);
		}
	}

	void setSpecimenQueue(SpecimenQueue specimenQueue){
		this->specimenQueue = specimenQueue;
	}

	Specimen popSpecimen(){
		Specimen s = specimenQueue.top();
		specimenQueue.pop();
		return s;
	}

	Specimen getSpecimen(int index){
	    return specimenArray.at(index);
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



	void evaluatePopulation(Population population){
		SpecimenQueue specimenQueue;

		for(int i=0; i<populationSize; i++){
			Specimen specimen = population.popSpecimen();

			float fitness = evaluationFunction(specimen.getValuesArray());
			specimen.setFitness(fitness);
		}

	}


	void mutatePopulation(Population population){
	    for(int i=0; i<populationSize; i++){
	        Specimen specimen = population.popSpecimen();

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


		}


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


//void memeticAlgorithm(int seed, int populationSize){
//
//
//
//}

#endif //PSZT_MEMETICALGORITHM_MEMETIC_H
