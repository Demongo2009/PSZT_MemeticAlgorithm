//
// Created by demongo on 05.11.2020.
//

#include "../include/memetic.h"





Specimen MemeticAlgorithm::generateSpecimen(){
	std::vector<float> valuesVector;
	std::uniform_real_distribution<> dis(minValue, maxValue);

	for(int i=0; i<specimenSize ; i++){

		valuesVector.push_back( dis(gen) );
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


	std::uniform_int_distribution<> intDist (0, populationSize-1);

	for(int i=0; i<populationSize; i++){
		// choose 2 random specimens
		firstIndex = intDist(gen);
		secondIndex = intDist(gen);

		// choose the winner by comparing the fitness value
		// copy the winner to the vectorOfWinners
		if(population.getSpecimen(firstIndex).getFitness() < population.getSpecimen(secondIndex).getFitness())
			vectorOfWinners.push_back(population.getSpecimen(firstIndex));
		else
			vectorOfWinners.push_back(population.getSpecimen(secondIndex));
	}

	Population nextGeneration = Population(vectorOfWinners);    // create new population using vector of winners
	return nextGeneration;
}




void MemeticAlgorithm::localSearch(Population population){
	std::uniform_real_distribution<> dis(0, 1);

	Eigen::VectorXd x;
	double fx=0;
	int niter=0;

	LBFGSpp::LBFGSSolver<double> solver(param);


	for(int i=0; i<populationSize; i++){
		Specimen specimen = population.getSpecimen(i);
		Specimen copy = specimen;
		//copy.getValuesArray().data()
		x = Eigen::Map<Eigen::VectorXd, Eigen::Unaligned>(reinterpret_cast<double *>(copy.getValuesArray().data()), specimenSize);


		float useLocalSearchThreshold = dis(gen);

		if( useLocalSearchThreshold <= localSearchProbability ) {
			// it may come to changing evaluationFunction or splitting it into one for solver and one for fitness because solver requires
			// signature fun(x, grad)
			niter = solver.minimize(fun, x, fx);

			copy.setFitness(fx);
			std::vector<float> values(x.data(), x.data() + x.rows() * x.cols());
			copy.setValuesArray(values);

			bestSpecimensFound.push_back(copy);
		}

	}

	Specimen best;
	best.setFitness(MAXFLOAT);
	int size = bestSpecimensFound.size();
	for(int i=0; i<size; i++){
		Specimen s = *bestSpecimensFound.begin();
		if(best.getFitness() > s.getFitness()){
			best = s;
		}
		bestSpecimensFound.erase(bestSpecimensFound.begin());
	}

	bestSpecimensFound.push_back(best);
}


Specimen MemeticAlgorithm::run() {

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
		localSearch(population);

	}

	Specimen best;
	best.setFitness(MAXFLOAT);
	for(auto s: bestSpecimensFound){
		if(best.getFitness() > s.getFitness()){
			best = s;
		}
	}

	return best;
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
