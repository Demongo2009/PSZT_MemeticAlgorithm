//
// Created by demongo on 05.11.2020.
//

#include "../include/memetic.h"





Specimen MemeticAlgorithm::generateSpecimen(){
	std::vector<float> valuesVector;

	for(int i=0; i<specimenSize ; i++){
		int randomInt = rand() % ( (int)rangeOfValue * 10^(floatPrecision) );
		valuesVector.push_back( (float)randomInt / (float)( 10^(floatPrecision) ) );
	}

	return Specimen(valuesVector);
}


Population MemeticAlgorithm::generatePopulation(){

	std::vector<Specimen> specimenVector;

	for(int i=0; i<populationSize; i++){

		specimenVector.push_back(generateSpecimen());

	}

	return Population(specimenVector);
}



void MemeticAlgorithm::evaluatePopulation(Population& population){

	for(int i=0; i<populationSize; i++){
		Specimen specimen = population.getSpecimen(i);

		float fitness = evaluationFunction(specimen.getValuesArray());
		specimen.setFitness(fitness);
	}

}


void MemeticAlgorithm::mutatePopulation(Population& population){

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> uniDist(0, 1);
    std::normal_distribution<> normalDist(0, mutationStrength);

	for(int i=0; i<populationSize; i++){

	    if(uniDist(gen) < mutationProbability){
            Specimen specimen = population.getSpecimen(i);
            std::vector<float> valuesArray = specimen.getValuesArray();

            for(int j=0; j<specimenSize; j++){
                float new_value = valuesArray.at(j) + normalDist(gen);

                if(new_value > maxValue) new_value = maxValue;
                else if(new_value < minValue) new_value = minValue;

                valuesArray.at(j) = new_value;
            }
            specimen.setValuesArray(valuesArray);
        }
	}
}


Population MemeticAlgorithm::tournamentSelection(Population population){
	std::vector<Specimen> vectorOfWinners;  // vector for the tournament winners
	int firstIndex, secondIndex;

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> intDist (0, populationSize-1);

	for(int i=0; i<populationSize; i++){
		// choose 2 random specimens
		firstIndex = intDist(gen);
		secondIndex = intDist(gen);

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


Population MemeticAlgorithm::localSearch(Population population){
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

		float copyFitness = evaluationFunction(copy.getValuesArray());

		if(copyFitness > specimen.getFitness()){
			population.setSpecimen(i, copy);
		}
	}

	return population;
}


void MemeticAlgorithm::run() {

	// generate an initial population
	Population population = generatePopulation();

	for (int i = 0; i < numberOfGenerations; i++) {
		// evaluate
		evaluatePopulation(population);

		// evolve (mutate only)
		mutatePopulation(population);

		// select (tournament selection)
		population = tournamentSelection(population);

		// local memetics
		population = localSearch(population);

	}
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

/*
 * I would suggest such an order:
 *
 * 0.1  generate an initial population
 * 0.2  evaluate
 *
 * for(int i=0; i < numberOfGenerations; i++)
 * {
 *      1.  evolve (mutate)
 *      2.  evaluate
 *      3.  local memetics (with built in evaluating - updating fitness values)
 *      4.  tournament selection - it seems logical to do it at the end of the loop
 *          because by selection we get next generation
 * }
 *
 */
